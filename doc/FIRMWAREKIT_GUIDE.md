# FirmwareKit Developer Guide

FirmwareKit is the Ne.app EFI SDK used by BootChk. It provides C++20 type aliases,
EFI protocol definitions, and utility macros for writing UEFI applications without
depending on EDK II or any third-party firmware library.

## Headers

| Header | Purpose |
|---|---|
| `FirmwareKit/Config.h` | Scalar type aliases (`Int32`, `UInt64`, `WideChar`, …) |
| `FirmwareKit/Efi.h` | UEFI structs, protocol typedefs, GUIDs, and status codes |
| `FirmwareKit/Macros.h` | Utility macros for sizes, alignment, attributes, and debug |

Every translation unit should include only what it needs. `Efi.h` pulls in `Config.h`
automatically; `Config.h` pulls in `Macros.h`.

## Entry point

UEFI applications use `extern "C"` linkage and `__stdcall` (the linker entry is
`BootChkModule`):

```cpp
#include "FirmwareKit/Efi.h"

extern "C" Int32 BootChkModule(EfiHandlePtr ImageHandle, EfiSystemTable* ST) {
    if (!ST || !ImageHandle)
        return kEfiFail;

    ST->ConOut->OutputString(ST->ConOut, L"Hello, World!\r\n");
    return kEfiOk;
}
```

Always validate `ST` and `ImageHandle` before dereferencing, firmware may pass null
on malformed handoffs.

## Type system

`FirmwareKit/Config.h` defines platform-width aliases over MSVC intrinsics:

| Alias | Underlying type | Width |
|---|---|---|
| `Int32` / `Int` | `int` | 32-bit |
| `UInt32` / `UInt` | `unsigned int` | 32-bit |
| `Int64` / `Long` | `__int64` | 64-bit |
| `UInt64` / `ULong` | `unsigned __int64` | 64-bit |
| `IntPtr` | `__int64` | pointer-sized signed |
| `UIntPtr` | `unsigned __int64` | pointer-sized unsigned |
| `WideChar` | `wchar_t` | 16-bit (UEFI wide char) |
| `Char16` | `char16_t` | 16-bit UTF-16 |
| `SizeT` / `Size` | `unsigned __int64` | 64-bit unsigned |

Use `WideChar` / `EfiCharType` for all strings passed to EFI protocols (UEFI is
UTF-16LE throughout).

## Status codes

| Macro | Value | Meaning |
|---|---|---|
| `kEfiOk` | `0` | Success |
| `kEfiFail` | `-1` | Generic failure |
| `kBufferTooSmall` | `5` | Output buffer too small |

Return `kEfiOk` or `kEfiFail` from `BootChkModule`. Protocol function pointers
return `EfiStatusType` (`UInt64`); check against `kEfiOk` before using output
parameters.

## Key EFI structures

### `EfiSystemTable`

The root structure passed to every EFI application.

```
EfiSystemTable
├── ConIn   → EfiSimpleTextInputProtocol   (keyboard)
├── ConOut  → EfiSimpleTextOutputProtocol  (text output)
├── StdErr  → void* (raw)
├── RuntimeServices → EfiRuntimeServices
└── BootServices    → EfiBootServices
```

### `EfiBootServices`

Provides memory management, image loading, and protocol location:

| Field | Type | Use |
|---|---|---|
| `AllocatePool` | `EfiAllocatePool` | Allocate heap memory |
| `FreePool` | `EfiFreePool` | Release heap memory |
| `AllocatePages` | `EfiAllocatePages` | Page-granularity allocation |
| `GetMemoryMap` | `EfiGetMemoryMap` | Enumerate physical memory |
| `LoadImage` | `EfiLoadImage` | Load a child EFI image |
| `StartImage` | `EfiStartImage` | Execute a loaded image |
| `ExitBootServices` | `EfiExitBootServices` | Hand control to OS loader |
| `LocateProtocol` | `EfiLocateProtocol` | Find a protocol by GUID |
| `OpenProtocol` | `EfiOpenProtocol` | Open a protocol on a handle |

### `EfiSimpleTextOutputProtocol`

```cpp
ST->ConOut->OutputString(ST->ConOut, L"text\r\n");
ST->ConOut->ClearScreen(ST->ConOut);
ST->ConOut->SetAttribute(ST->ConOut, kEFIYellow);
```

`SetAttribute` accepts a combined foreground/background bitmask. `kEFIYellow`
(`0x0F`) selects bright white text on black.

### `EfiFileProtocol`

Obtained by calling `OpenVolume` on `EfiSimpleFilesystemProtocol`:

```cpp
EfiFileProtocol* root = nullptr;
fs->OpenVolume(fs, &root);

EfiFileProtocol* file = nullptr;
root->Open(root, &file, L"\\EFI\\BOOT\\data.bin",
           kEFIFileRead, kEFIReadOnly);
```

File-mode flags: `kEFIFileRead`, `kEFIFileWrite`, `kEFIFileCreate`.  
Attribute flags: `kEFIReadOnly`, `kEFIHidden`, `kEFISystem`, `kEFIDirectory`, `kEFIArchive`.

### `EfiGraphicsOutputProtocol`

Located via `EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID`:

```cpp
EfiGraphicsOutputProtocol* gop = nullptr;
ST->BootServices->LocateProtocol(
    &(EFI_GUID)EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr,
    reinterpret_cast<VoidPtr*>(&gop));

UInt32 w = gop->Mode->Info->HorizontalResolution;
UInt32 h = gop->Mode->Info->VerticalResolution;
```

### `EfiMpServicesProtocol`

Located via `EFI_MP_SERVICES_PROTOCOL_GUID`. Use to enumerate processors or run
a procedure on all APs:

```cpp
UInt32 total = 0, enabled = 0;
mp->GetNumberOfProcessors(mp, &total, &enabled);
```

## Utility macros (`FirmwareKit/Macros.h`)

### Size conversions

```cpp
KIB(4096)        // 4 (bytes → KiB)
kib_cast(4)      // 4096 (KiB → bytes)
MIB(1048576)     // 1
mib_cast(1)      // 1048576
GIB(n)  gib_cast(n)
TIB(n)  tib_cast(n)
```

### Memory / addressing constants

| Macro | Value |
|---|---|
| `kInvalidAddress` | `0xFBFBFBFBFBFBFBFB` |
| `kBadAddress` | `0x0000000000000000` |
| `kMaxAddr` | `0xFFFFFFFFFFFFFFFF` |
| `kPathLen` | `0x100` (256 wide chars) |

### Common macros

| Macro | Expands to |
|---|---|
| `ALIGN(n)` | `__attribute__((aligned(n)))` |
| `PACKED` | `__attribute__((packed))` |
| `DEPRECATED` | `__attribute__((deprecated))` |
| `CANT_REACH()` | `__builtin_unreachable()` |
| `ARRAY_SIZE(a)` | compile-time element count |
| `NE_UNUSED(x)` | suppress unused-variable warning |
| `DBG_TRAP()` | `asm volatile("int $3")` on x86-64, no-op elsewhere |
| `RTL_ALLOCA(sz)` | `__builtin_alloca(sz)` |
| `RGB(r,g,b)` | pack RGB into `UInt32` with `0xFF` alpha |

## Build configuration (x64 Debug/Release)

The `.vcxproj` sets these non-default options for EFI targets:

| Setting | Value | Why |
|---|---|---|
| Entry point | `BootChkModule` | UEFI does not use `main` |
| Subsystem | `EFI Application` | PE/COFF EFI image type |
| Exception handling | Disabled | No C++ runtime in firmware |
| Buffer security check | Disabled | No CRT `/GS` cookie support |
| Default libraries | Ignored | Freestanding environment |
| Base address | `0x10000000` | Avoid conflict with firmware regions |
| ASLR / DEP | Disabled | EFI loader does not apply these |
| Output extension | `.efi` | Standard EFI image suffix |

C++ standard is `/std:c++20`. SDL checks are enabled on all configurations.

## Calling convention

All EFI protocol function pointers use `__stdcall` (aliased as `EFI_API` / `EFIAPI`).
Do not call them through a plain C++ pointer with default `__cdecl`, the stack will
be misaligned and the firmware will fault.

## Adding a new driver

1. Copy `BootChk/BootChk.cpp` to a new `.cpp` file.
2. Rename the entry point (`BootChkModule` → your driver's name).
3. Update the `<EntryPointSymbol>` element in the `.vcxproj` to match.
4. Add the new `.cpp` to the `<ItemGroup>` in the `.vcxproj`.
5. Build with the **x64 Debug** configuration; the output is `x64/Debug/<name>.efi`.

## Protocol lookup pattern

```cpp
auto locate = [&]<typename T>(EFI_GUID guid, T** out) -> bool {
    return ST->BootServices->LocateProtocol(
               &guid, nullptr, reinterpret_cast<VoidPtr*>(out)) == kEfiOk;
};

EfiGraphicsOutputProtocol* gop = nullptr;
if (!locate((EFI_GUID)EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, &gop))
    return kEfiFail;
```

---

Copyright 2024-2026 Ne.app, licensed under the Apache-2.0 License.
