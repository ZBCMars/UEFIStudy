#include "Kernel.h"

UINT64 KernelStart(BOOT_CONFIG *BootConfig){
    UINT64 PassBack = 0;
    VideoInitial(BootConfig);
    ShellInitial();
    
    //MemInitial(BootConfig);
    
    /*
    char String[20];
    String[0] = 'z';
    String[1] = 'b';
    String[2] = 'c';
    String[3] = '\n';
    String[4] = '\0';
    PrintStr(String);

    PrintHex(0x123456789ABCDEF);
    */

    PrintDec(BootConfig->MemoryMap.MapKey);

    return PassBack;
}
