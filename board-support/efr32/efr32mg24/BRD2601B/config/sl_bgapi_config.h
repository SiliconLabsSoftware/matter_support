/***************************************************************************//**
 * @file
 * @brief BGAPI Protocol configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in a
 *    product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_BGAPI_CONFIG_H
#define SL_BGAPI_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_BGAPI_MAX_PAYLOAD_SIZE> The maximum BGAPI payload size <256-2047>
// <i> Default: 256
// <i> Define the maximum payload size for BGAPI commands, responses, and events. The setting impacts all protocol stacks that use the BGAPI, i.e. Bluetooth host and Bluetooth mesh.
#define SL_BGAPI_MAX_PAYLOAD_SIZE     (256)

// <<< end of configuration section >>>

#endif // SL_BGAPI_CONFIG_H
