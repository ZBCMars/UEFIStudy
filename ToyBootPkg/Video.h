#include "File.h"

#include <Protocol/GraphicsOutput.h>

typedef struct{
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINTN                FrameBufferSize;
    UINT32               HorizontalResolution;
    UINT32               VerticalResolution;
    UINT32               PixelPerScanLine;
} VIDEO_CONFIG;

EFI_STATUS GetGopHandle(
    IN EFI_HANDLE ImageHandle,
    OUT EFI_GRAPHICS_OUTPUT_PROTOCOL **Gop
);

EFI_STATUS SetVideoMode(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop
);
