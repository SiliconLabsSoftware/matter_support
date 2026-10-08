/*
 *    Copyright (c) 2024 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <lib/core/CHIPError.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/Span.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

namespace chip {
namespace DeviceLayer {
namespace Silabs {
namespace Provision {

static constexpr uint32_t kCreds_KeyId_Default = 2; //(PSA_KEY_ID_USER_MIN + 1);

// Size of the buffer holding the CSR subject name. Worst case is the Zephyr
// form, which embeds VID/PID as hex-DER UTF8String values:
//   "CN=<cn>, 1.3.6.1.4.1.37244.2.1=#0C04XXXXXXXX, 1.3.6.1.4.1.37244.2.2=#0C04XXXXXXXX\0"
//
//  "CN="   3 chars
//  <cn>    64 chars (variable length)
//  ", 1.3.6.1.4.1.37244.2.1=#0C04XXXXXXXX"   37 chars
//  ", 1.3.6.1.4.1.37244.2.2=#0C04XXXXXXXX"   37 chars
//  "\0"    1 char

// Worst case: 3 + 64 + 37 + 37 + 1 = 142, rounded up to 160.
static constexpr size_t kSubjectNameLengthMax = 160;

// Encode a Matter VID/PID as a hex-DER attribute value.
// "#0C04" + 8 hex digits: ASN.1 UTF8String (0x0C), length 4, then the ASCII
// of "%04X" (e.g. FFF1 -> #0C0446464631).
inline CHIP_ERROR FormatMatterOidUtf8DerHex(char * dest, size_t destSize, uint16_t value)
{
    VerifyOrReturnError(dest != nullptr, CHIP_ERROR_INVALID_ARGUMENT);
    char hex[5];
    snprintf(hex, sizeof(hex), "%04X", value);

    int written =
        snprintf(dest, destSize, "#0C04%02X%02X%02X%02X", static_cast<unsigned char>(hex[0]), static_cast<unsigned char>(hex[1]),
                 static_cast<unsigned char>(hex[2]), static_cast<unsigned char>(hex[3]));
    return (written == 13) ? CHIP_NO_ERROR : CHIP_ERROR_INTERNAL;
}

class AttestationKey
{
public:
    AttestationKey(uint32_t id = 0) { mId = (id > 0) ? id : kCreds_KeyId_Default; }
    ~AttestationKey() = default;

    uint32_t GetId() { return mId; }
    CHIP_ERROR Import(const uint8_t * asn1, size_t size);
    CHIP_ERROR Export(uint8_t * asn1, size_t max, size_t & size);
    CHIP_ERROR GenerateCSR(uint16_t vid, uint16_t pid, const CharSpan & cn, MutableCharSpan & csr);
    CHIP_ERROR SignMessage(const ByteSpan & message, MutableByteSpan & out_span);

#if (defined(SLI_SI91X_MCU_INTERFACE) && SLI_SI91X_MCU_INTERFACE)
    static CHIP_ERROR Unwrap(const uint8_t * asn1, size_t size, MutableByteSpan & private_key);
    static CHIP_ERROR SignMessageWithKey(const uint8_t * private_key, const ByteSpan & message, MutableByteSpan & out_span);
#endif // SLI_SI91X_MCU_INTERFACE

protected:
    uint32_t mId = 0;
};

} // namespace Provision
} // namespace Silabs
} // namespace DeviceLayer
} // namespace chip
