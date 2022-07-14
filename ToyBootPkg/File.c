#include "File.h"

EFI_STATUS GetFileHandle(
    IN EFI_HANDLE ImageHandle,
    IN CHAR16 *FileName,
    OUT EFI_FILE_PROTOCOL **FileHandle
){
    EFI_STATUS Status = EFI_SUCCESS;

    UINTN HandleCount = 0;
    EFI_HANDLE *HandleBuffer = NULL;
    Status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        &HandleCount,
        &HandleBuffer
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to LocateHandleBuffer to SimpleFileSystemProtocol.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:Get %d Handles from SimpleFileSystemProtocol.\n", HandleCount);
    }
    #endif

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    Status = gBS->OpenProtocol(
        HandleBuffer[0],
        &gEfiSimpleFileSystemProtocolGuid,
        (VOID **)&FileSystem,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to OpenProtocol to SimpleFileSystemProtocol.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:Open the SimpleFileSystemProtocol.\n");
    }
    #endif

    EFI_FILE_PROTOCOL *Root;
    Status = FileSystem->OpenVolume(
        FileSystem,
        &Root
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to OpenVolume.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:Open the Volume.\n");
    }
    #endif

    Status = Root->Open(
        Root,
        FileHandle,
        FileName,
        EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to Open File.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:Open the File.\n");
    }
    #endif

    return Status;
}

EFI_STATUS ReadFile(
    IN EFI_FILE_PROTOCOL *File,
    OUT EFI_PHYSICAL_ADDRESS *FileBase
){
    EFI_STATUS Status = EFI_SUCCESS;

    EFI_FILE_INFO *FileInfo;
    UINTN InfoSize = sizeof(EFI_FILE_INFO) + 128;
    Status = gBS->AllocatePool(
        EfiLoaderData,
        InfoSize,
        (VOID **)&FileInfo
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to AllocatePool for FileInfo.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:AllocatePool for FileInfo.\n");
    }
    #endif

    Status = File->GetInfo(
        File,
        &gEfiFileInfoGuid,
        &InfoSize,
        FileInfo
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to GetInfo from BMP.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:GetInfo from BMP.\n");
    }
    #endif

    UINTN FilePageSize = (FileInfo->FileSize >> 12) + 1;
    EFI_PHYSICAL_ADDRESS FileBufferAddress;
    Status = gBS->AllocatePages(
        AllocateAnyPages,
        EfiLoaderData,
        FilePageSize,
        &FileBufferAddress
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to AllocatePages for File.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:AllocatePages for File.\n");
    }
    #endif

    UINTN ReadSize = FileInfo->FileSize;
    Status = File->Read(
        File,
        &ReadSize,
        (VOID *)FileBufferAddress
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to Read the File.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:Read the File.\n");
    }
    #endif

    gBS->FreePool(FileInfo);
    *FileBase = FileBufferAddress;

    return Status;
}