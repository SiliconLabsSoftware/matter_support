#ifndef _BRD4186C_H_
#define _BRD4186C_H_
#ifndef LOGGING_STATS
#define WAKE_INDICATOR_PIN  PIN(D, 3)
#endif

#ifdef LOGGING_STATS
#define LOGGING_WAKE_INDICATOR_PIN  PIN(D, 3)
#define LOGGING_STATS_PORT    SL_GPIO_PORT_D
#define LOGGING_STATS_PIN     03
#endif

#ifdef RS911X_WIFI
// SPI ports and pins
#define EUS1MOSI_PORT   SL_GPIO_PORT_C
#define EUS1MOSI_PIN    1
#define EUS1MISO_PORT   SL_GPIO_PORT_C
#define EUS1MISO_PIN    2
#define EUS1SCLK_PORT   SL_GPIO_PORT_C
#define EUS1SCLK_PIN    3
#define EUS1CS_PORT     SL_GPIO_PORT_C
#define EUS1CS_PIN      0


#define MY_USART EUSART1
#define MY_USART_CLOCK cmuClock_EUSART1

#define MY_USART_TX_SIGNAL                                                     \
	  dmadrvPeripheralSignal_EUSART1_TXBL
#define MY_USART_RX_SIGNAL                                                     \
	  dmadrvPeripheralSignal_EUSART1_RXDATAV

#define WFX_RESET_PIN PIN(A, 6)
#define WFX_INTERRUPT_PIN PIN(A, 7)
#define WFX_SLEEP_CONFIRM_PIN PIN(A, 5) /* Exp hdr 7 */
#define SL_WFX_HOST_PINOUT_SPI_IRQ 5

#else /* WF200 */

#define PIN_OUT_SET	    	1
#define PIN_OUT_CLEAR		0

#define MY_USART            USART0
#define MY_USART_CLOCK      cmuClock_USART0
#define MY_USART_TX_SIGNAL  dmadrvPeripheralSignal_USART0_TXBL
#define MY_USART_RX_SIGNAL  dmadrvPeripheralSignal_USART0_RXDATAV

#define SL_WFX_HOST_PINOUT_RESET_PORT SL_GPIO_PORT_A
#define SL_WFX_HOST_PINOUT_RESET_PIN 5
#define SL_WFX_HOST_PINOUT_SPI_WIRQ_PORT SL_GPIO_PORT_A /* SPI IRQ port*/
#define SL_WFX_HOST_PINOUT_SPI_WIRQ_PIN 8          /* SPI IRQ pin */
#define SL_WFX_HOST_PINOUT_WUP_PORT SL_GPIO_PORT_B
#define SL_WFX_HOST_PINOUT_WUP_PIN 5

#define SL_WFX_HOST_PINOUT_SPI_TX_PORT SL_GPIO_PORT_C
#define SL_WFX_HOST_PINOUT_SPI_TX_PIN 1

#define SL_WFX_HOST_PINOUT_SPI_RX_PORT SL_GPIO_PORT_C
#define SL_WFX_HOST_PINOUT_SPI_RX_PIN 2

#define SL_WFX_HOST_PINOUT_SPI_CLK_PORT SL_GPIO_PORT_C
#define SL_WFX_HOST_PINOUT_SPI_CLK_PIN 3

#define SL_WFX_HOST_PINOUT_SPI_CS_PORT SL_GPIO_PORT_C
#define SL_WFX_HOST_PINOUT_SPI_CS_PIN 0

#endif /* WF200/9116 */


#ifdef RS911X_WIFI
#else /* WF200 */
#endif /* WF200/9116 */

#endif /* _BRD4186C_H_ */
