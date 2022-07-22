#include "Shell.h"

BASE Base;

int ShellInitial(){
    Base.Setup.Height = 860;
    Base.Setup.Width = 1400;
    Base.Setup.X = 20;
    Base.Setup.Y = 20;
    Base.Setup.Outlines = 1;

    BLOCK BackGround;
    BackGround.Color = 0xFF000000;
    BackGround.Start.X = 20;
    BackGround.Start.Y = 20;
    BackGround.End.X = 1420;
    BackGround.End.Y = 880;
    DrawBlock(BackGround);
    
    POINT Dest;
    Dest.X = 30;
    Dest.Y = 78;
    UINT32 Output = DrawLetter('T', Dest);

    if(Base.Setup.Outlines){
        BLOCK Outline;
        Outline.Color = 0xFFFFFFFF;
        Outline.Start.X = 20;
        Outline.Start.Y = 20;
        Outline.End.X = 1420;
        Outline.End.Y = 22;
        DrawBlock(Outline);

        Outline.Start.X = 20;
        Outline.Start.Y = 68;
        Outline.End.X = 1418;
        Outline.End.Y = 70;
        DrawBlock(Outline);

        Outline.Start.X = 20;
        Outline.Start.Y = 878;
        Outline.End.X = 1420;
        Outline.End.Y = 880;
        DrawBlock(Outline);

        Outline.Start.X = 20;
        Outline.Start.Y = 22;
        Outline.End.X = 22;
        Outline.End.Y = 878;
        DrawBlock(Outline);

        Outline.Start.X = 1418;
        Outline.Start.Y = 20;
        Outline.End.X = 1420;
        Outline.End.Y = 878;
        DrawBlock(Outline);
    }

    return 0;
}
