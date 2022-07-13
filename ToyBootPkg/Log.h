#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>

#include "Setup.h"

EFI_STATUS LogInitial(EFI_HANDLE ImageHandle);
EFI_STATUS LogTip(CHAR8 *Message);
EFI_STATUS LogError(EFI_STATUS Code);
EFI_STATUS Close();
