#include "Video.h"

EFI_STATUS GetGopHandle(
    IN EFI_HANDLE ImageHandle,
    OUT EFI_GRAPHICS_OUTPUT_PROTOCOL **Gop
){
    EFI_STATUS Status = EFI_SUCCESS;

    UINTN HandleCounts = 0;
    EFI_HANDLE *HandleBuffer = NULL;
    Status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiGraphicsOutputProtocolGuid,
        NULL,
        &HandleCounts,
        &HandleBuffer
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to LocateHandleBuffer to GraphicsOutputProtocol.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:Get %d Handles from GraphicsOutputProtocol.\n", HandleCounts);
    }
    #endif

    Status = gBS->OpenProtocol(
        HandleBuffer[0],
        &gEfiGraphicsOutputProtocolGuid,
        (VOID **)Gop,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to OpenProtocol to GraphicsOutputProtocol.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:Open the GraphicsOutputProtocol.\n");
    }
    #endif

    return Status;
}   

EFI_STATUS SetVideoMode(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop
){
    EFI_STATUS Status = EFI_SUCCESS;

    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *ModeInfo;
    UINTN ModeInfoSize = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);
    UINTN H = 0;
    UINTN V = 0;
    UINTN ModeIndex = 0;

    for(UINTN i = 0; i < Gop->Mode->MaxMode; i++){
        Status = Gop->QueryMode(
            Gop,
            i,
            &ModeInfoSize,
            &ModeInfo
        );
        H = ModeInfo->HorizontalResolution;
        V = ModeInfo->VerticalResolution;

        if(((H == 1024) && (V == 768)) || ((H == 1440) && (V == 900))){
            ModeIndex = i;
        }
    }

    Status = Gop->SetMode(Gop, ModeIndex);

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to SetMode.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:SetModeIndex to %d.\n", ModeIndex);
    }
    #endif

    return Status;
}
