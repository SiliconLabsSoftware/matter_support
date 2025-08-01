#include "sl_event_handler.h"

#include "sl_board_init.h"
#include "sl_clock_manager.h"
#include "sl_hfxo_manager.h"
#include "pa_conversions_efr32.h"
#if !RSI_BLE_ENABLE
#include "sl_rail_util_power_manager_init.h"
#endif
#include "sl_rail_util_pti.h"
#include "sl_rail_util_rssi.h"
#include "btl_interface.h"
#include "sl_board_control.h"
#include "platform-efr32.h"
#include "sl_bt_rtos_adaptation.h"
#include "sl_bluetooth.h"
#include "sl_debug_swo.h"
#include "sl_gpio.h"
#include "gpiointerrupt.h"
#if defined(SL_MATTER_USE_SI70XX_SENSOR) && SL_MATTER_USE_SI70XX_SENSOR
#include "sl_i2cspm_instances.h"
#endif // defined(SL_MATTER_USE_SI70XX_SENSOR) && SL_MATTER_USE_SI70XX_SENSOR
#include "sl_iostream_rtt.h"
#include "sl_mbedtls.h"
#include "sl_ot_rtos_adaptation.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#if defined(CONFIG_ENABLE_UART)
#include "sl_uartdrv_instances.h"
#endif // CONFIG_ENABLE_UART
#ifdef SL_WIFI
#include "sl_spidrv_instances.h"
#endif
#include "psa/crypto.h"
#include "sl_se_manager.h"
#include "sli_protocol_crypto.h"
#include "sli_crypto.h"
#include "sl_iostream_init_instances.h"
#include "cmsis_os2.h"
#include "nvm3_default.h"
#include "sl_cos.h"
#include "sl_iostream_handles.h"

void sli_driver_permanent_allocation(void)
{
}

void sli_service_permanent_allocation(void)
{
}

void sli_stack_permanent_allocation(void)
{
#if !RSI_BLE_ENABLE
  sli_bt_stack_permanent_allocation();
#endif // RSI_BLE_ENABLE

#ifdef SL_OT_ENABLE
  sl_ot_rtos_perm_allocation();
#endif // SL_OT_ENABLE
}

void sli_internal_permanent_allocation(void)
{
}

void sl_platform_init(void)
{
  sl_board_preinit();
  sl_clock_manager_runtime_init();
  sl_hfxo_manager_init_hardware();
  sl_board_init();
  bootloader_init();
  nvm3_initDefault();
}

void sli_internal_init_early(void)
{
}

void sl_kernel_start(void)
{
#if !RSI_BLE_ENABLE
  sli_bt_rtos_adaptation_kernel_start();
#endif // !RSI_BLE_ENABLE
  osKernelStart();
}

void sl_driver_init(void)
{
  sl_gpio_init();
  GPIOINT_Init();
#ifdef SL_WIFI
  sl_spidrv_init_instances();
#endif
#if defined(SL_MATTER_USE_SI70XX_SENSOR) && SL_MATTER_USE_SI70XX_SENSOR
  sl_i2cspm_init_instances();
#endif // defined(SL_MATTER_USE_SI70XX_SENSOR) && SL_MATTER_USE_SI70XX_SENSOR
  sl_simple_button_init_instances();
  sl_simple_led_init_instances();
#if defined(CONFIG_ENABLE_UART)
  sl_uartdrv_init_instances();
#endif // CONFIG_ENABLE_UART
}

void sl_service_init(void)
{
  sl_board_configure_vcom();
  sl_hfxo_manager_init();
  sl_mbedtls_init();
  psa_crypto_init();
  sl_se_init();
  sli_protocol_crypto_init();
  sli_crypto_init();
  sli_aes_seed_mask();
  sl_iostream_init_instances();
}

void sl_stack_init(void)
{
#if !RSI_BLE_ENABLE
  sl_rail_util_pa_init();
  sl_rail_util_power_manager_init();
  sl_rail_util_pti_init();
  sl_rail_util_rssi_init();
  sli_bt_stack_functional_init();
#endif

#ifdef SL_OT_ENABLE
  sl_ot_sys_init();
#endif // SL_OT_ENABLE
}

void sl_internal_app_init(void)
{
#ifdef SL_OT_ENABLE
  sl_ot_rtos_stack_init();
  sl_ot_rtos_app_init();
#endif // SL_OT_ENABLE
}

void sl_iostream_init_instances(void)
{
  sl_iostream_rtt_init();
}
