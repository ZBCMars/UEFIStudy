#include "Memory.h"

int MemInitial(BOOT_CONFIG *BootConfig){
    //EFI_MEMORTY_DESCRIPTOR *EfiMemory = (EFI_MEMORTY_DESCRIPTOR *)(BootConfig->MemoryMap.Buffer);
    EFI_MEMORY_DESCRIPTOR *EfiMemory = (EFI_MEMORY_DESCRIPTOR *)(BootConfig->MemoryMap.Buffer);
    
    /*
    for(int i = 0; i < 22; i++)
    {
        PrintHex(EfiMemory->Type);
        PrintSpace();
        PrintHex(EfiMemory->PhysicalStart);
        PrintSpace();
        PrintHex(EfiMemory->VirtualStart);
        PrintSpace();
        PrintHex(EfiMemory->NumberOfPages);
        PrintSpace();
        PrintHex(EfiMemory->Attribute);
        PrintEnter();
        EfiMemory++;
    }
    */

    OS_MEMORY_DESCRIPTOR *OsMemory = NULL;

    int EfiMemoryPageSize = (BootConfig->MemoryMap.MapSize >> 12) + 1;
    PrintDec(EfiMemoryPageSize);
    PrintSpace();

    EFI_PHYSICAL_ADDRESS OsMemoryAddress = 0;
    int EfiDescriptorCount = BootConfig->MemoryMap.MapSize / BootConfig->MemoryMap.DescriptorSize;

    for(int i = 0; i < EfiDescriptorCount; i++){
        if(EfiMemoryPageSize < EfiMemory[i].NumberOfPages && EfiMemory[i].Type == 7){
            OsMemoryAddress = EfiMemory[i].PhysicalStart;
            OsMemory = (OS_MEMORY_DESCRIPTOR *)OsMemoryAddress;
            break;
        }
    }

    PrintHex((UINT64)OsMemory);
    PrintSpace();

    int OsMemDescNum = 0;
    for(int i = 0; i < EfiDescriptorCount; i++){
        if(EfiMemory[i].Type == EfiBootServicesCode
           || EfiMemory[i].Type == EfiBootServicesData
           || EfiMemory[i].Type == EfiConventionalMemory){
            OsMemory->Type = FREE_MEMORY;
        }
        else if(EfiMemory[i].Type == EfiMemoryMappedIO){
            OsMemory->Type = MMIO_MEMORY;
        }
        else{
            OsMemory->Type = UEFI_MEMORY;
        }

        OsMemory->PhysicalStart = EfiMemory[i].PhysicalStart;
        OsMemory->PageSize = EfiMemory[i].NumberOfPages;

        if(i > 0 && OsMemory->Type == (OsMemory-1)->Type){
            if(OsMemory->PhysicalStart == (OsMemory-1)->PhysicalStart + ((OsMemory-1)->PageSize << 12)){
                (OsMemory-1)->PageSize += OsMemory->PageSize;
                continue;
            }
        }
        OsMemory++;
        OsMemDescNum++;
    }

    PrintDec(EfiDescriptorCount);
    PrintSpace();
    PrintDec(OsMemDescNum);
    PrintEnter();

    OsMemory = (OS_MEMORY_DESCRIPTOR *)OsMemoryAddress;
    UINT64 TotalMemory = 0;
    for(int i = 0; i < OsMemDescNum; i++){
        PrintDec(OsMemory->Type);
        PrintSpace();
        PrintHex(OsMemory->PhysicalStart);
        PrintSpace();
        PrintHex(OsMemory->PageSize);
        PrintEnter();
        if(OsMemory->Type != MMIO_MEMORY){
            TotalMemory += OsMemory->PageSize;
        }
        OsMemory++;
    }

    return 0;
}
