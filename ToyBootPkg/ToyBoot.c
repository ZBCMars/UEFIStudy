#include "ToyBoot.h"

EFI_STATUS
EFIAPI
UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT8 Step = 1;

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
    BootConfig.VideoConfig = VideoConfig;

    UINT64 (*KernelEntry)(BOOT_CONFIG *BootConfig);
    KernelEntry = (UINT64 (*)(BOOT_CONFIG *BootConfig))KernelEntryPoint;
    
    BootConfig.MemoryMap.MapSize = 8192;
    BootConfig.MemoryMap.Buffer = NULL;
    BootConfig.MemoryMap.MapKey = 0;
    BootConfig.MemoryMap.DescriptorSize = 0;
    BootConfig.MemoryMap.DescriptorVersion = 0;
    Status = ByeBootService(ImageHandle, &BootConfig.MemoryMap);
    
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

EFI_STATUS ByeBootService(
    IN EFI_HANDLE ImageHandle,
    OUT MEMORY_MAP *MemoryMap
){
    EFI_STATUS Status = EFI_SUCCESS;

    Status = gBS->AllocatePool(EfiLoaderData, MemoryMap->MapSize, &MemoryMap->Buffer);

    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to AllocatePool for MemoryMap.\n");
        return Status;
    }

    Status = gBS->GetMemoryMap(
        &MemoryMap->MapSize,
        (EFI_MEMORY_DESCRIPTOR *)MemoryMap->Buffer,
        &MemoryMap->MapKey,
        &MemoryMap->DescriptorSize,
        &MemoryMap->DescriptorVersion
    );

    Status = gBS->ExitBootServices(ImageHandle, MemoryMap->MapKey);

    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to ExitBootServices.\n");
        return Status;
    }

    return Status;
}
