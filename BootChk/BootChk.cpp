// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss & Ne.app (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app-open/snippet-efi-driver-bootchk

#include "FirmwareKit/Config.h"
#include "FirmwareKit/Efi.h"

Int32 BootChkModule(EfiHandlePtr ImageHandle, EfiSystemTable* ST) {
	/// Write your boot check driver here!
	ST->ConOut->OutputString(ST->ConOut, L"Hello, World!\r\n");
	return kEfiOk;
}
