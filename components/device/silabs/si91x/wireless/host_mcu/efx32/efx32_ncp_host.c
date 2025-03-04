/*******************************************************************************
* @file  efx32_ncp_host.c
* @brief 
*******************************************************************************
* # License
* <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
*******************************************************************************
*
* The licensor of this software is Silicon Laboratories Inc. Your use of this
* software is governed by the terms of Silicon Labs Master Software License
* Agreement (MSLA) available at
* www.silabs.com/about-us/legal/master-software-license-agreement. This
* software is distributed to you in Source Code format and is governed by the
* sections of the MSLA applicable to Source Code.
*
******************************************************************************/

#include "sl_wifi_constants.h"
#include "sl_si91x_host_interface.h"
#include "sl_board_configuration.h"
#include "sl_status.h"
#include "em_usart.h"
#include "em_cmu.h"
#include "em_core.h"
#include "em_gpio.h"
#include "cmsis_os2.h"
#include "dmadrv.h"
#include "gpiointerrupt.h"
#include "sl_si91x_status.h"
#include "sl_rsi_utility.h"
#include "sl_constants.h"
#include <stdbool.h>
#include <string.h>

#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include "sl_spidrv_exp_config.h"
#include "si91x_ncp_spi_config.h"

// use SPI handle for EXP header (configured in project settings)
extern SPIDRV_Handle_t sl_spidrv_exp_handle;
#define SPI_HANDLE sl_spidrv_exp_handle
static uint8_t dummy_buffer[1800] = { 0 };

static osSemaphoreId_t transfer_done_semaphore      = NULL;
static osMutexId_t ncp_transfer_mutex               = NULL;
static sl_si91x_host_init_configuration init_config = { 0 };

static void gpio_interrupt(uint8_t interrupt_number)
{
  UNUSED_PARAMETER(interrupt_number);

  if (NULL != init_config.rx_irq) {
    init_config.rx_irq();
  }

  return;
}

static void spi_dma_callback(struct SPIDRV_HandleData *handle, Ecode_t transferStatus, int itemsTransferred)
{
  UNUSED_PARAMETER(handle);
  UNUSED_PARAMETER(transferStatus);
  UNUSED_PARAMETER(itemsTransferred);
  osSemaphoreRelease(transfer_done_semaphore);
  return;
}

static void efx32_spi_init(void)
{
  SPIDRV_SetBitrate(SPI_HANDLE, 12500000);

  // Configure SPI bus pins
  GPIO_PinModeSet(SL_SPIDRV_EXP_RX_PORT, SL_SPIDRV_EXP_RX_PIN, gpioModeInput, 0);
  GPIO_PinModeSet(SL_SPIDRV_EXP_TX_PORT, SL_SPIDRV_EXP_TX_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(SL_SPIDRV_EXP_CLK_PORT, SL_SPIDRV_EXP_CLK_PIN, gpioModePushPullAlternate, 0);
  GPIO_PinModeSet(SL_SPIDRV_EXP_CS_PORT, SL_SPIDRV_EXP_CS_PIN, gpioModePushPull, 1);

  // configure packet pending interrupt priority
  NVIC_SetPriority(NCP_RX_IRQ, PACKET_PENDING_INT_PRI);
  GPIOINT_CallbackRegister(SI91X_NCP_INTERRUPT_PIN, gpio_interrupt);
  GPIO_PinModeSet(SI91X_NCP_INTERRUPT_PORT, SI91X_NCP_INTERRUPT_PIN, gpioModeInputPullFilter, 0);

  // Check if the boot option is set to LOAD_DEFAULT_NWP_FW_ACTIVE_LOW
  if (init_config.boot_option == LOAD_DEFAULT_NWP_FW_ACTIVE_LOW)
    // Configure the GPIO external interrupt for active low configuration
    GPIO_ExtIntConfig(SI91X_NCP_INTERRUPT_PORT, SI91X_NCP_INTERRUPT_PIN, SI91X_NCP_INTERRUPT_PIN, false, true, true);
  else
    // Configure the GPIO external interrupt for active high configuration
    GPIO_ExtIntConfig(SI91X_NCP_INTERRUPT_PORT, SI91X_NCP_INTERRUPT_PIN, SI91X_NCP_INTERRUPT_PIN, true, false, true);

  return;
}

Ecode_t si91x_SPIDRV_MTransfer(SPIDRV_Handle_t handle,
                               const void *txBuffer,
                               void *rxBuffer,
                               int count,
                               SPIDRV_Callback_t callback)
{
  USART_TypeDef *usart = handle->initData.port;
  uint8_t *tx          = (txBuffer != NULL) ? (uint8_t *)txBuffer : dummy_buffer;
  uint8_t *rx          = (rxBuffer != NULL) ? (uint8_t *)rxBuffer : dummy_buffer;

  if (count < 16) {
    while (count > 0) {
      while (!(usart->STATUS & USART_STATUS_TXBL)) {
      }
      usart->TXDATA = (uint32_t)*tx;
      while (!(usart->STATUS & USART_STATUS_TXC)) {
      }
      *rx = (uint8_t)usart->RXDATA;
      if (txBuffer != NULL) {
        tx++;
      }
      if (rxBuffer != NULL) {
        rx++;
      }
      count--;
    }
    //callback(handle, ECODE_EMDRV_SPIDRV_OK, 0);
    return ECODE_EMDRV_SPIDRV_OK;
  } else {
    SPIDRV_MTransfer(handle, tx, rx, count, callback);
  }

  return ECODE_EMDRV_SPIDRV_BUSY;
}
#endif

void sl_si91x_host_set_sleep_indicator(void)
{
  GPIO_PinOutSet(SI91X_NCP_SLEEP_CONFIRM_PORT, SI91X_NCP_SLEEP_CONFIRM_PIN);
}

void sl_si91x_host_clear_sleep_indicator(void)
{
  GPIO_PinOutClear(SI91X_NCP_SLEEP_CONFIRM_PORT, SI91X_NCP_SLEEP_CONFIRM_PIN);
}

uint32_t sl_si91x_host_get_wake_indicator(void)
{
  return GPIO_PinInGet(SI91X_NCP_WAKE_INDICATOR_PORT, SI91X_NCP_WAKE_INDICATOR_PIN);
}

sl_status_t sl_si91x_host_init(const sl_si91x_host_init_configuration *config)
{
  init_config.rx_irq      = config->rx_irq;
  init_config.rx_done     = config->rx_done;
  init_config.boot_option = config->boot_option;

  // Enable clock (not needed on xG21)
  CMU_ClockEnable(cmuClock_GPIO, true);

  if (ncp_transfer_mutex == NULL) {
    ncp_transfer_mutex = osMutexNew(NULL);
  }

  if (transfer_done_semaphore == NULL) {
    transfer_done_semaphore = osSemaphoreNew(1, 0, NULL);
  }
  efx32_spi_init();

  // Start reset line low
  GPIO_PinModeSet(SI91X_NCP_RESET_PORT, SI91X_NCP_RESET_PIN, gpioModeWiredAnd, 0);

  // Configure interrupt, sleep and wake confirmation pins
  GPIO_PinModeSet(SI91X_NCP_SLEEP_CONFIRM_PORT, SI91X_NCP_SLEEP_CONFIRM_PIN, gpioModeWiredOrPullDown, 1);
  GPIO_PinModeSet(SI91X_NCP_WAKE_INDICATOR_PORT, SI91X_NCP_WAKE_INDICATOR_PIN, gpioModeWiredOrPullDown, 0);

  return SL_STATUS_OK;
}

sl_status_t sl_si91x_host_deinit(void)
{
  return SL_STATUS_OK;
}

void sl_si91x_host_enable_high_speed_bus()
{
  return;
}

/*==================================================================*/
/**
 * @fn         sl_status_t sl_si91x_host_spi_transfer(const void *tx_buffer, void *rx_buffer, uint16_t buffer_length)
 * @param[in]  uint8_t *tx_buff, pointer to the buffer with the data to be transferred
 * @param[in]  uint8_t *rx_buff, pointer to the buffer to store the data received
 * @param[in]  uint16_t transfer_length, Number of bytes to send and receive
 * @param[in]  uint8_t mode, To indicate mode 8 BIT/32 BIT mode transfers.
 * @param[out] None
 * @return     0, 0=success
 * @section description
 * This API is used to transfer/receive data to the Wi-Fi module through the SPI interface.
 */

sl_status_t sl_si91x_host_spi_transfer(const void *tx_buffer, void *rx_buffer, uint16_t buffer_length)
{
  osMutexAcquire(ncp_transfer_mutex, osWaitForever);
  }

  osMutexRelease(ncp_transfer_mutex);
  return SL_STATUS_OK;
}

void sl_si91x_host_hold_in_reset(void)
{
  GPIO_PinOutClear(SI91X_NCP_RESET_PORT, SI91X_NCP_RESET_PIN);
}

void sl_si91x_host_release_from_reset(void)
{
  GPIO_PinOutSet(SI91X_NCP_RESET_PORT, SI91X_NCP_RESET_PIN);
}

void sl_si91x_host_enable_bus_interrupt(void)
{
  NVIC_ClearPendingIRQ(NCP_RX_IRQ);
  NVIC_EnableIRQ(NCP_RX_IRQ);
}

void sl_si91x_host_disable_bus_interrupt(void)
{
  NVIC_DisableIRQ(NCP_RX_IRQ);
}

bool sl_si91x_host_is_in_irq_context(void)
{
  return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U;
}
