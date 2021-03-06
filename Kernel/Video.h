#include "Type.h"

#pragma pack(1)

typedef struct{
    UINT32 X;
    UINT32 Y;
    UINT32 Color;
} PIXEL;

typedef struct{
    UINT32 X;
    UINT32 Y;
} POINT;

typedef struct{
    POINT Start;
    POINT End;
    UINT32 Color;
} BLOCK;

#pragma pack()

int VideoInitial(BOOT_CONFIG *BootConfig);
int DrawPixel(PIXEL Pixel);
int DrawBlock(BLOCK Block);
int DrawLetter(UINT8 Ascii, POINT Destination);
