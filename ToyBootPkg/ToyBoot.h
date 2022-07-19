#include "Elf.h"
#include "Motion.h"

typedef struct{
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINT64               FrameBufferSize;
} BOOT_CONFIG;
