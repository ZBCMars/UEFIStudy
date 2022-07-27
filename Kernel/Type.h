typedef void VOID;
typedef unsigned char UINT8;
typedef UINT8 CHAR8;
typedef unsigned int  UINT32;
typedef unsigned long long  UINT64;
typedef UINT64 UINTN;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

#define NULL ((VOID *) 0)

typedef enum {
  EfiReservedMemoryType,
  EfiLoaderCode,
  EfiLoaderData,
  EfiBootServicesCode,
  EfiBootServicesData,
  EfiRuntimeServicesCode,
  EfiRuntimeServicesData,
  EfiConventionalMemory,
  EfiUnusableMemory,
  EfiACPIReclaimMemory,
  EfiACPIMemoryNVS,
  EfiMemoryMappedIO,
  EfiMemoryMappedIOPortSpace,
  EfiPalCode,
  EfiPersistentMemory,
  EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef struct
{
  UINT8 Blue;
  UINT8 Green;
  UINT8 Red;
  UINT8 Reserved;
} BGR_PIXEL;

typedef struct{
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINTN                FrameBufferSize;
    UINT32               HorizontalResolution;
    UINT32               VerticalResolution;
    UINT32               PixelPerScanLine;
} VIDEO_CONFIG;

typedef struct
{
    UINT32  Type;
    UINT32  ReservedA;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS  VirtualStart;
    UINT64  NumberOfPages;
    UINT64  Attribute;
    UINT64  ReservedB;
} EFI_MEMORY_DESCRIPTOR;

typedef struct
{
    UINTN Size;
    UINTN PageSize;
    UINTN Width;
    UINTN Height;
    UINTN Offset;
    UINT64 PixelStart;
} BMP_CONFIG;

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
    BMP_CONFIG   AsciiBmp;
} BOOT_CONFIG;

