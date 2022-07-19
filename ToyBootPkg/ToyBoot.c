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
    DrawStep(Step++);
    DrawStep(Step++);
    
    Status = DrawLogo(ImageHandle);

    #ifdef LOG
    if(EFI_ERROR(Status)){
        LogError(Status);
    }
    else{
        LogTip("Step is good.\n");
    }
    #endif
    DrawStep(Step++);
    
    EFI_PHYSICAL_ADDRESS KernelEntryPoint;
    Status = Relocate(ImageHandle, L"\\Kernel.elf", &KernelEntryPoint);
    #ifdef LOG
    if(EFI_ERROR(Status)){
        LogError(Status);
    }
    else{
        LogTip("Kernel Entry Get.\n");
    }
    #endif
    DrawStep(Step++);

    /*
    int (*KernelEntry)();
    KernelEntry = (int (*)())KernelEntryPoint;
    int X = KernelEntry();
    Print(L"Return value from Kernel = %d.\n", X);
    */

    BOOT_CONFIG BootConfig;
    BootConfig.FrameBufferBase = VideoConfig.FrameBufferBase;
    BootConfig.FrameBufferSize = VideoConfig.FrameBufferSize;

    UINT64 (*KernelEntry)(BOOT_CONFIG *BootConfig);
    KernelEntry = (UINT64 (*)(BOOT_CONFIG *BootConfig))KernelEntryPoint;
    UINT64 PassBack = KernelEntry(&BootConfig);
    Print(L"PassBack = 0x%llX.\n", PassBack);

    /*
    EFI_FILE_PROTOCOL *Bin;
    Status = GetFileHandle(ImageHandle, L"Kernel.bin", &Bin);
    EFI_PHYSICAL_ADDRESS BinAddress;
    Status = ReadFile(Bin, &BinAddress);

    asm("jmp %0"::"m"(BinAddress));
    */

    return Status;
}
