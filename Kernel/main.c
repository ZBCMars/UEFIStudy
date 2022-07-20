#include "Type.h"

int DrawPixel(UINT32 *VideoHandle, UINT32 Color, int X, int Y){
    UINT32 *Pixel = VideoHandle;
    Pixel += Y * 1440 + X;
    *Pixel = Color;
    return 0;
}

UINT64 _start(BOOT_CONFIG *BootConfig){
    UINT64 PassBack = 0;
    UINT32 DarkBlue = 0xFF18679A;
    UINT32 *VideoHandle = (UINT32 *)(BootConfig->FrameBufferBase);
    for(int i = 0; i < 900; i++){
        for(int j = 0; j < 1440; j++){
            DrawPixel(VideoHandle, DarkBlue, j, i);
        }
    }
    PassBack = BootConfig->FrameBufferBase;
    return PassBack;
}