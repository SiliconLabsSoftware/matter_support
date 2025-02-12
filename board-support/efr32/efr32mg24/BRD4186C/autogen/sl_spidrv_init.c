#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include "sl_assert.h"

// EUSART is used in MG24 + RS9116 combination
#if defined(RS911X_WIFI) && !defined(EXP_BOARD)
#include "sl_spidrv_eusart_exp_config.h"

SPIDRV_HandleData_t sl_spidrv_eusart_exp_handle_data;
SPIDRV_Handle_t sl_spidrv_eusart_exp_handle = &sl_spidrv_eusart_exp_handle_data;

SPIDRV_Init_t sl_spidrv_eusart_init_exp = {
  .port    = SL_SPIDRV_EUSART_EXP_PERIPHERAL,
  .portTx  = SL_SPIDRV_EUSART_EXP_TX_PORT,
  .portRx  = SL_SPIDRV_EUSART_EXP_RX_PORT,
  .portClk = SL_SPIDRV_EUSART_EXP_SCLK_PORT,
#if defined(SL_SPIDRV_EUSART_EXP_CS_PORT)
  .portCs = SL_SPIDRV_EUSART_EXP_CS_PORT,
#endif
  .pinTx  = SL_SPIDRV_EUSART_EXP_TX_PIN,
  .pinRx  = SL_SPIDRV_EUSART_EXP_RX_PIN,
  .pinClk = SL_SPIDRV_EUSART_EXP_SCLK_PIN,
#if defined(SL_SPIDRV_EUSART_EXP_CS_PIN)
  .pinCs = SL_SPIDRV_EUSART_EXP_CS_PIN,
#endif
  .bitRate        = SL_SPIDRV_EUSART_EXP_BITRATE,
  .frameLength    = SL_SPIDRV_EUSART_EXP_FRAME_LENGTH,
  .dummyTxValue   = 0,
  .type           = SL_SPIDRV_EUSART_EXP_TYPE,
  .bitOrder       = SL_SPIDRV_EUSART_EXP_BIT_ORDER,
  .clockMode      = SL_SPIDRV_EUSART_EXP_CLOCK_MODE,
  .csControl      = SL_SPIDRV_EUSART_EXP_CS_CONTROL,
  .slaveStartMode = SL_SPIDRV_EUSART_EXP_SLAVE_START_MODE,
};

void sl_spidrv_init_instances(void)
{
#if !defined(SL_SPIDRV_USART_EXP_CS_PIN)
  EFM_ASSERT(sl_spidrv_eusart_init_exp.csControl == spidrvCsControlAuto);
#endif
  SPIDRV_Init(sl_spidrv_eusart_exp_handle, &sl_spidrv_eusart_init_exp);
}
#endif //defined(RS911X_WIFI) && !defined(EXP_BOARD)

#if defined(WF200_WIFI) || defined(EXP_BOARD) // USART is used in MG24 + WF200 and MG24 + 917 NCP combination
#include "sl_spidrv_exp_config.h"

SPIDRV_HandleData_t sl_spidrv_exp_handle_data;
SPIDRV_Handle_t sl_spidrv_exp_handle = &sl_spidrv_exp_handle_data;

SPIDRV_Init_t sl_spidrv_init_exp = {
  .port = SL_SPIDRV_EXP_PERIPHERAL,
#if defined(_USART_ROUTELOC0_MASK)
  .portLocationTx  = SL_SPIDRV_EXP_TX_LOC,
  .portLocationRx  = SL_SPIDRV_EXP_RX_LOC,
  .portLocationClk = SL_SPIDRV_EXP_CLK_LOC,
#if defined(SL_SPIDRV_EXP_CS_LOC)
  .portLocationCs = SL_SPIDRV_EXP_CS_LOC,
#endif
#elif defined(_GPIO_USART_ROUTEEN_MASK)
  .portTx  = SL_SPIDRV_EXP_TX_PORT,
  .portRx  = SL_SPIDRV_EXP_RX_PORT,
  .portClk = SL_SPIDRV_EXP_CLK_PORT,
#if defined(SL_SPIDRV_EXP_CS_PORT)
  .portCs  = SL_SPIDRV_EXP_CS_PORT,
#endif
  .pinTx   = SL_SPIDRV_EXP_TX_PIN,
  .pinRx   = SL_SPIDRV_EXP_RX_PIN,
  .pinClk  = SL_SPIDRV_EXP_CLK_PIN,
#if defined(SL_SPIDRV_EXP_CS_PIN)
  .pinCs   = SL_SPIDRV_EXP_CS_PIN,
#endif
#else
  .portLocation = SL_SPIDRV_EXP_ROUTE_LOC,
#endif
  .bitRate        = SL_SPIDRV_EXP_BITRATE,
  .frameLength    = SL_SPIDRV_EXP_FRAME_LENGTH,
  .dummyTxValue   = 0,
  .type           = SL_SPIDRV_EXP_TYPE,
  .bitOrder       = SL_SPIDRV_EXP_BIT_ORDER,
  .clockMode      = SL_SPIDRV_EXP_CLOCK_MODE,
  .csControl      = SL_SPIDRV_EXP_CS_CONTROL,
  .slaveStartMode = SL_SPIDRV_EXP_SLAVE_START_MODE,
};

void sl_spidrv_init_instances(void)
{
  SPIDRV_Init(sl_spidrv_exp_handle, &sl_spidrv_init_exp);
}

#endif //defined(WF200_WIFI) || defined(EXP_BOARD)