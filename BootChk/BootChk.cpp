// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss & Ne.app (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app/snippet-efi-driver-bootchk

#include "Efi.h"

SInt32 BootChkModule(VoidPtr ImageHandle) {
	/// Write your boot check driver here!
	return kEfiOk;
}
