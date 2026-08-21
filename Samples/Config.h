// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss & Ne.app (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app-open/snippet-efi-driver-bootchk

#ifndef FIRMWAREKIT_CONFIG_H
#define FIRMWAREKIT_CONFIG_H

#include "Macros.h"

using voidPtr = void *;
using VoidPtr = void *;
using nullPtr = decltype(nullptr);
using NullPtr = decltype(nullptr);

using Int = int;
using Int32 = __INT32_TYPE__;
using UShort = __UINT16_TYPE__;
using UInt16 = __UINT16_TYPE__;
using Short = short;
using Int16 = __INT16_TYPE__;
using UInt = __UINT32_TYPE__;
using UInt32 = __UINT32_TYPE__;
using Long = __INT64_TYPE__;
using Int64 = __INT64_TYPE__;
using ULong = __UINT64_TYPE__;
using UInt64 = __UINT64_TYPE__;
using Boolean = bool;
using Bool = bool;
using Char = char;
using Int8 = __INT8_TYPE__;
using Char8 = char8_t;
using UChar = __UINT8_TYPE__;
using UInt8 = __UINT8_TYPE__;

using SSize = long;
using SSizeT = long;
using Size = __SIZE_TYPE__;
using SizeT = __SIZE_TYPE__;
using IntPtr = __INTPTR_TYPE__;
using UIntPtr = __UINTPTR_TYPE__;
using IntFast = __INT_FAST32_TYPE__;
using IntFast64 = __INT_FAST64_TYPE__;
using PtrDiff = __PTRDIFF_TYPE__;

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
using Any = void *;

using Lba = UInt64;

using Char16 = char16_t;

#endif