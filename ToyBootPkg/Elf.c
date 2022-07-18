#include "Elf.h"

EFI_STATUS Relocate(
    IN EFI_HANDLE ImageHandle,
    IN CHAR16 *FileName,
    OUT EFI_PHYSICAL_ADDRESS *KernelEntry
){
    EFI_STATUS Status = EFI_SUCCESS;

    EFI_FILE_PROTOCOL *Kernel;
    Status = GetFileHandle(ImageHandle, FileName, &Kernel);

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to GetFileHandle for Kernel.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:GetFileHandle for Kernel.\n");
    }
    #endif

    EFI_PHYSICAL_ADDRESS KernelBuffer;
    Status = ReadFile(Kernel, &KernelBuffer);

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to ReadFile for Kernel.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:ReadFile for Kernel.\n");
    }
    #endif

    Status = CheckELF(KernelBuffer);
    if(EFI_ERROR(Status)){
        return Status;
    }

    Status = LoadSegments(KernelBuffer, KernelEntry);

    return Status;
}

EFI_STATUS CheckELF(
    IN EFI_PHYSICAL_ADDRESS KernelBuffer
){
    EFI_STATUS Status = EFI_SUCCESS;

    UINT32 Magic = GetValue(KernelBuffer, 0x00, 4);
    if(Magic != 0x464C457F){
        #ifdef LOG
        LogError(NOT_ELF);
        #endif
        Status = NOT_ELF;
    }

    UINT8 Format = GetValue(KernelBuffer, 0x04, 1);
    if(Format == ELF_64){
        #ifdef LOG
        LogTip("SUCCESS:Elf file is 64-bit.\n");
        #endif
    }
    else{
        #ifdef LOG
        LogError(NOT_64_BIT);
        #endif
        Status = NOT_64_BIT;
    }

    return Status;
}

EFI_STATUS LoadSegments(
    IN EFI_PHYSICAL_ADDRESS KernelBufferBase,
    OUT EFI_PHYSICAL_ADDRESS *KernelEntry
){
    EFI_STATUS Status = EFI_SUCCESS;

    ELF_HEADER_64 *ElfHeader = (ELF_HEADER_64 *)KernelBufferBase;
    PROGRAM_HEADER_64 *PHeader = (PROGRAM_HEADER_64 *)(KernelBufferBase + ElfHeader->Phoff);

    EFI_PHYSICAL_ADDRESS LowAddr = 0xFFFFFFFFFFFFFFFF;
    EFI_PHYSICAL_ADDRESS HighAddr = 0;

    for(UINTN i = 0; i < ElfHeader->PHeadCount; i++){
        if(PHeader[i].Type == PT_LOAD){
            if(PHeader[i].PAddress < LowAddr){
                LowAddr = PHeader[i].PAddress;
            }
            if((PHeader[i].PAddress + PHeader[i].SizeInMemory) > HighAddr){
                HighAddr = PHeader[i].PAddress + PHeader[i].SizeInMemory;
            }
        }
    }

    UINTN PageCount = ((HighAddr - LowAddr) >> 12) + 1;

    EFI_PHYSICAL_ADDRESS KernelRelocateBase;
    Status = gBS->AllocatePages(
        AllocateAnyPages,
        EfiLoaderData,
        PageCount,
        &KernelRelocateBase
    );

    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to AllocatePages for KernelRelocateBase\n");
        return Status;
    }

    UINTN RelocateOffset = KernelRelocateBase - LowAddr;
    UINT64 *ZeroStart = (UINT64 *)KernelRelocateBase;

    for(UINTN i = 0; i < (PageCount << 9); i++){
        *ZeroStart = 0x000000000000;
        ZeroStart++;
    }

    for(UINTN i = 0; i < ElfHeader->PHeadCount; i++){
        UINT8 *SourceStart = (UINT8 *)KernelBufferBase + PHeader[i].Offset;
        UINT8 *DestStart = (UINT8 *)PHeader[i].VAddress + RelocateOffset;

        for(UINTN j = 0; j < PHeader[i].SizeInFile; j++){
            *DestStart = *SourceStart;
            DestStart++;
            SourceStart++;
        }
    }

    *KernelEntry = ElfHeader->Entry + RelocateOffset;

    #ifdef LOG
    if(EFI_ERROR(Status)){
        LogError(Status);
    }
    else{
        LogTip("Segs are Loaded.\n");
    }
    #endif

    return Status;
}