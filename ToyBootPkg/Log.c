#include "Log.h"

EFI_FILE_PROTOCOL *LogFile = NULL;

EFI_STATUS LogInitial(EFI_HANDLE ImageHandle){
    EFI_STATUS Status = EFI_SUCCESS;

    UINTN HandleCount = 0;
    EFI_HANDLE *Buffer = NULL;
    Status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        &HandleCount,
        &Buffer
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

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = NULL;
    Status = gBS->OpenProtocol(
        Buffer[0],
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

    EFI_FILE_PROTOCOL *File = NULL;
    Status = FileSystem->OpenVolume(
        FileSystem,
        &File
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

    File->Open(
        File,
        &LogFile,
        L"\\Log.txt",
        EFI_FILE_MODE_CREATE|EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
        EFI_FILE_ARCHIVE
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
EFI_STATUS LogTip(CHAR8 *Message){
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN MsgLen = AsciiStrLen(Message);

    Status = LogFile->Write(
        LogFile,
        &MsgLen,
        Message
    );

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to Write LogFile.\n");
        return Status;
    }
    #endif

    return Status;
}

EFI_STATUS LogError(EFI_STATUS Code){
    EFI_STATUS Status = EFI_SUCCESS;

    switch (Code)
    {
    case EFI_INVALID_PARAMETER:
        Status = LogTip("Error:EFI_INVALID_PARAMETER.\n");
        break;
    case EFI_NOT_FOUND:
        Status = LogTip("Error:EFI_NOT_FOUND.\n");
        break;
    case EFI_OUT_OF_RESOURCES:
        Status = LogTip("Error:EFI_OUT_OF_RESOURCES.\n");
        break;
    default:
        Status = LogTip("Error:Something went wrong.\n");
        break;
    }

    return Status;
}

EFI_STATUS Close(){
    EFI_STATUS Status = EFI_SUCCESS;
    Status = LogFile->Close(LogFile);

    #ifdef DEBUG
    if(EFI_ERROR(Status)){
        Print(L"ERROR:Failed to Close LogFile.\n");
        return Status;
    }
    else{
        Print(L"SUCCESS:Close the LogFIle.\n");
    }
    #endif

    return Status;
}
