#include "Memory.h"

int MemInitial(BOOT_CONFIG *BootConfig){
    //EFI_MEMORTY_DESCRIPTOR *EfiMemory = (EFI_MEMORTY_DESCRIPTOR *)(BootConfig->MemoryMap.Buffer);
    EFI_MEMORY_DESCRIPTOR *EfiMemory = (EFI_MEMORY_DESCRIPTOR *)(BootConfig->MemoryMap.Buffer);
    
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

    return 0;
}