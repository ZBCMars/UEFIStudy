#include "Motion.h"

EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;

EFI_STATUS VideoInit(
    IN EFI_HANDLE ImageHandle,
    OUT VIDEO_CONFIG *VideoConfig
){
    EFI_STATUS Status = EFI_SUCCESS;

    Status = GetGopHandle(ImageHandle, &Gop);

    Status = SetVideoMode(Gop);

    VideoConfig->FrameBufferBase = Gop->Mode->FrameBufferBase;
    VideoConfig->FrameBufferSize = Gop->Mode->FrameBufferSize;
    VideoConfig->HorizontalResolution = Gop->Mode->Info->HorizontalResolution;
    VideoConfig->VerticalResolution = Gop->Mode->Info->VerticalResolution;
    VideoConfig->PixelPerScanLine = Gop->Mode->Info->PixelsPerScanLine;

    return Status;
}

EFI_STATUS DrawLogo(
    IN EFI_HANDLE ImageHandle
){
    EFI_STATUS Status = EFI_SUCCESS;

    CHAR16 *FileName = L"\\images.bmp";
    UINTN Hor = Gop->Mode->Info->HorizontalResolution;
    UINTN Ver = Gop->Mode->Info->VerticalResolution;

    EFI_FILE_PROTOCOL *Logo;
    Status = GetFileHandle(ImageHandle, FileName, &Logo);

    EFI_PHYSICAL_ADDRESS LogoAddress;
    Status = ReadFile(Logo, &LogoAddress);

    return Status;
}