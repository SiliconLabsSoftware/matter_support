/***************************************************************************//**
 * @file
 * @brief UARTDRV_EUSART Config
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_UARTDRV_EUSART_VCOM_CONFIG_H
#define SL_UARTDRV_EUSART_VCOM_CONFIG_H

#include "em_eusart.h"
// <<< Use Configuration Wizard in Context Menu >>>

// <h> EUSART settings
// <o SL_UARTDRV_EUSART_VCOM_BAUDRATE> Baud rate
// <i> Default: 115200
#define SL_UARTDRV_EUSART_VCOM_BAUDRATE        921600

// <o SL_UARTDRV_EUSART_VCOM_LF_MODE> Low frequency mode
// <true=> True
// <false=> False
#define SL_UARTDRV_EUSART_VCOM_LF_MODE         false

// <o SL_UARTDRV_EUSART_VCOM_PARITY> Parity mode to use
// <eusartNoParity=> No Parity
// <eusartEvenParity=> Even parity
// <eusartOddParity=> Odd parity
// <i> Default: eusartNoParity
#define SL_UARTDRV_EUSART_VCOM_PARITY          eusartNoParity

// <o SL_UARTDRV_EUSART_VCOM_STOP_BITS> Number of stop bits to use.
// <eusartStopbits0p5=> 0.5 stop bits
// <eusartStopbits1=> 1 stop bits
// <eusartStopbits1p5=> 1.5 stop bits
// <eusartStopbits2=> 2 stop bits
// <i> Default: eusartStopbits1
#define SL_UARTDRV_EUSART_VCOM_STOP_BITS       eusartStopbits1

// <o SL_UARTDRV_EUSART_VCOM_FLOW_CONTROL_TYPE> Flow control method
// <uartdrvFlowControlNone=> None
// <uartdrvFlowControlSw=> Software XON/XOFF
// <uartdrvFlowControlHw=> nRTS/nCTS hardware handshake
// <uartdrvFlowControlHwUart=> UART peripheral controls nRTS/nCTS
// <i> Default: uartdrvFlowControlHwUart
#define SL_UARTDRV_EUSART_VCOM_FLOW_CONTROL_TYPE uartdrvFlowControlHwUart

// <o SL_UARTDRV_EUSART_VCOM_OVERSAMPLING> Oversampling selection
// <eusartOVS16=> 16x oversampling
// <eusartOVS8=> 8x oversampling
// <eusartOVS6=> 6x oversampling
// <eusartOVS4=> 4x oversampling
// <eusartOVS0=> Oversampling disabled
// <i> Default: eusartOVS16
#define SL_UARTDRV_EUSART_VCOM_OVERSAMPLING      eusartOVS16

// <o SL_UARTDRV_EUSART_VCOM_MVDIS> Majority vote disable for 16x, 8x and 6x oversampling modes
// <eusartMajorityVoteEnable=> False
// <eusartMajorityVoteDisable=> True
// <i> Default: eusartMajorityVoteEnable
#define SL_UARTDRV_EUSART_VCOM_MVDIS             eusartMajorityVoteEnable

// <o SL_UARTDRV_EUSART_VCOM_RX_BUFFER_SIZE> Size of the receive operation queue
// <i> Default: 6
#define SL_UARTDRV_EUSART_VCOM_RX_BUFFER_SIZE  6

// <o SL_UARTDRV_EUSART_VCOM_TX_BUFFER_SIZE> Size of the transmit operation queue
// <i> Default: 6
#define SL_UARTDRV_EUSART_VCOM_TX_BUFFER_SIZE 6
// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <eusart signal=TX,RX,(CTS),(RTS)> SL_UARTDRV_EUSART_VCOM
// $[EUSART_SL_UARTDRV_EUSART_VCOM]
#define SL_UARTDRV_EUSART_VCOM_PERIPHERAL        EUSART0
#define SL_UARTDRV_EUSART_VCOM_PERIPHERAL_NO     0

// EUSART0 TX on PA05
#define SL_UARTDRV_EUSART_VCOM_TX_PORT           SL_GPIO_PORT_A
#define SL_UARTDRV_EUSART_VCOM_TX_PIN            5

// EUSART0 RX on PA06
#define SL_UARTDRV_EUSART_VCOM_RX_PORT           SL_GPIO_PORT_A
#define SL_UARTDRV_EUSART_VCOM_RX_PIN            6

// EUSART0 CTS on PA08
#define SL_UARTDRV_EUSART_VCOM_CTS_PORT          SL_GPIO_PORT_A
#define SL_UARTDRV_EUSART_VCOM_CTS_PIN           8

// EUSART0 RTS on PA07
#define SL_UARTDRV_EUSART_VCOM_RTS_PORT          SL_GPIO_PORT_A
#define SL_UARTDRV_EUSART_VCOM_RTS_PIN           7

// [EUSART_SL_UARTDRV_EUSART_VCOM]$
// <<< sl:end pin_tool >>>
#endif // SL_UARTDRV_EUSART_VCOM_CONFIG_H
