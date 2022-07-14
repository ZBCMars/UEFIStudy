#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

EFI_STATUS
EFIAPI
UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status = EFI_SUCCESS;

    #ifdef LOG
    Status = LogInitial(ImageHandle);
    if(EFI_ERROR(Status)){
        LogError(Status);
    }
    else{
        LogTip("Log is good.\n");
    }
    #endif

    VIDEO_CONFIG VideoConfig;
    Status = VideoInit(ImageHandle, &VideoConfig);

    #ifdef LOG
    if(EFI_ERROR(Status)){
        LogError(Status);
    }
    else{
        LogTip("Video is good.\n");
    }
    #endif

    return Status;
}
