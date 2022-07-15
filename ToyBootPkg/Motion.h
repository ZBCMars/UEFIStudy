#include "File.h"
#include "Video.h"

EFI_STATUS VideoInit(
    IN EFI_HANDLE ImageHandle,
    OUT VIDEO_CONFIG *VideoConfig
);

EFI_STATUS DrawLogo(
    IN EFI_HANDLE ImageHandle
);
