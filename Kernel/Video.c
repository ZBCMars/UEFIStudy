#include "Video.h"

VIDEO_CONFIG *VideoConfig;
UINT32 *VideoStart;
BMP_CONFIG *AsciiBmp;
UINT32 *AsciiStart;

int VideoInitial(BOOT_CONFIG *BootConfig){
    VideoConfig = &BootConfig->VideoConfig;
    VideoStart = (UINT32 *)BootConfig->VideoConfig.FrameBufferBase;
    AsciiBmp = &BootConfig->AsciiBmp;
    AsciiStart = (UINT32 *)BootConfig->AsciiBmp.PixelStart;

    BLOCK BackGround;
    BackGround.Start.X = 0;
    BackGround.Start.Y = 0;
    BackGround.End.X = BootConfig->VideoConfig.HorizontalResolution - 1;
    BackGround.End.Y = BootConfig->VideoConfig.VerticalResolution - 1;
    BackGround.Color = 0xFF18679A;
    DrawBlock(BackGround);
    
    return 0;
}

int DrawPixel(PIXEL Pixel){
    UINT32 *Position = VideoStart + (Pixel.Y - 1) * VideoConfig->PixelPerScanLine + Pixel.X;
    *Position = Pixel.Color;
    return 0;
}

int DrawBlock(BLOCK Block)
{
    PIXEL Pixel;
    Pixel.Color = Block.Color;
    for(int i = Block.Start.Y; i < Block.End.Y; i++)
    {
        for(int j = Block.Start.X; j < Block.End.X; j++)
        {
            Pixel.X = j;
            Pixel.Y = i;
            DrawPixel(Pixel);
        }
    }
    return 0;
}

int DrawLetter(UINT8 Ascii, POINT Destination){
    UINT8 Index = Ascii - 32;
    
    if(Ascii < 32 || Ascii > 126){
        Index = 127 - 32;
    }
    UINT32 *From = AsciiStart + (Index % 32) * LetterWidth
                   + (Index / 32) * LetterHeight * AsciiBmp->Width;
    UINT32 *To = VideoStart + Destination.X + Destination.Y * VideoConfig->PixelPerScanLine;
    //UINT32 Color;
    UINT32 Output = *AsciiStart;

    for(int i = 0; i < LetterHeight; i++)
    {
        for(int j = 0; j < LetterWidth; j++)
        {
            //Color = *From;
            //Color = ((Color & 0x000000ff) << 24 ) | ((Color & 0x0000ff00) << 8) | ((Color & 0x00ff0000) >> 8) | ((Color & 0xff000000 ) >> 24);
            *To = *From;
            From++;
            To++;
        }
        From = From + AsciiBmp->Width - LetterWidth;
        To = To + VideoConfig->PixelPerScanLine - LetterWidth;
    }
    
    return Output;
}
