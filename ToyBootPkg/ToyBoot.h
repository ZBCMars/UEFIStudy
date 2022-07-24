#include "Elf.h"
#include "Motion.h"

typedef struct
{
    UINTN MapSize;
    VOID *Buffer;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
} MEMORY_MAP;

typedef struct
{
    VIDEO_CONFIG VideoConfig;
    MEMORY_MAP MemoryMap;
    BMP_CONFIG AsciiBmp;
} BOOT_CONFIG; // @Boot.h

EFI_STATUS ByeBootService(EFI_HANDLE ImageHandle, MEMORY_MAP *MemoryMap);
