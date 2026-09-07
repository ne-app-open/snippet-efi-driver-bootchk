// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss & Ne.app (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app-open/sample-bootchk

#ifndef FIRMWAREKIT_CONFIG_H
#define FIRMWAREKIT_CONFIG_H

#include "FirmwareKit/Macros.h"

/***********************************************************************************/
/// @file FirmwareKit/Config.h
/// @brief Core Types and Macros.
/***********************************************************************************/

using voidPtr = void *;
using VoidPtr = void *;
using nullPtr = decltype(nullptr);
using NullPtr = decltype(nullptr);

using Int = int;
using Int32 = int;
using UShort = unsigned short;
using UInt16 = UShort;
using Short = short;
using Int16 = __int16;
using UInt = unsigned;
using UInt32 = UInt;
using Long = __int64;
using Int64 = __int64;
using ULong = unsigned __int64;
using UInt64 = ULong;
using Boolean = bool;
using Bool = bool;
using Char = char;
using Int8 = char;
using Char8 = char8_t;
using UChar = unsigned char;
using UInt8 = UChar;

using SSize = long long;
using SSizeT = long long;
using Size = unsigned long long;
using SizeT = Size;
using IntPtr = __int64;
using UIntPtr = unsigned __int64;
using IntFast = Int;
using IntFast64 = IntPtr;
using PtrDiff = __int64;

using SInt16 = Int16;
using SInt32 = Int32;
using SInt64 = Int64;

typedef UIntPtr *Ptr64;
typedef UInt32 *Ptr32;
typedef UInt8 *Ptr8;

using Utf8Char = char8_t;
using Utf16Char = char16_t;
using WideChar = wchar_t;
using Utf32Char = char32_t;

using LongDouble = long double;
using Double = double;
using Float = float;

typedef UInt32 PhysicalAddressKind;
typedef UIntPtr VirtualAddressKind;

using Void = void;
using Any = void*;

using Lba = UInt64;

using Char16 = char16_t;

#endif