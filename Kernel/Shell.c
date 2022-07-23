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
    //UINT32 Output = DrawLetter('T', Dest);

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
    
    Base.Head.Title[0] = 'T';
    Base.Head.Title[1] = '0';
    Base.Head.Title[2] = 'y';
    Base.Head.Title[3] = 'O';
    Base.Head.Title[4] = 'S';

    POINT TitleStart;
    TitleStart.X = (Base.Setup.Width - 20 * 5) / 2 + 22;
    TitleStart.Y = 27;

    for(int i = 0; i < 5; i++){
        DrawLetter(Base.Head.Title[i], TitleStart);
        TitleStart.X += 20;
    }

    SetCursor(0);

    return 0;
}

int SetCursor(UINT8 Count){
    Base.Cursor.Col += Count;
    if(Base.Cursor.Col >= 69){
        Base.Cursor.Row += Base.Cursor.Col / 69;
        Base.Cursor.Col %= 69;
    }
    Base.Cursor.Pos.X = Base.Cursor.Start.X + Base.Cursor.Col * 20;
    Base.Cursor.Pos.Y = Base.Cursor.Start.Y + Base.Cursor.Row * 36;

    BLOCK Cursor;
    Cursor.Color = 0xFFFFFFFF;
    Cursor.Start.X = Base.Cursor.Pos.X + 1;
    Cursor.Start.Y = Base.Cursor.Pos.Y + 30;
    Cursor.End.X = Cursor.Start.X + 18;
    Cursor.End.Y = Cursor.Start.Y + 3;
    DrawBlock(Cursor);

    return 0;
}

int PrintStr(char *String){
    char *ToPrint = String;
    int Len = 0;

    while(*ToPrint != '\0'){
        Len++;
        ToPrint++;
    }

    for(int i = 0; i < Len; i++){
        if(String[i] == '\n'){
            DrawLetter(' ', Base.Cursor.Pos);
            SetCursor(69-Base.Cursor.Col);
            continue;
        }
        DrawLetter(String[i], Base.Cursor.Pos);
        SetCursor(1);
    }

    return 0;
}

int PrintHex(UINT64 Number){
    UINT64 Trans = Number;

    DrawLetter('0', Base.Cursor.Pos);
    SetCursor(1);
    DrawLetter('x', Base.Cursor.Pos);
    SetCursor(1);

    char Hex[16];
    int Len = 0;

    for(int i = 0; i < 16; i++){
        Hex[i] = Trans & 0xF;
        if(Hex[i] >= 0 && Hex[i] <= 9){
            Hex[i] += 48;
        }
        if(Hex[i] > 9 && Hex[i] < 16){
            Hex[i] += 55;
        }

        Trans = Trans >> 4;
        Len++;
        if(Trans == 0){
            break;
        }
    }

    for(int i = 0; i < Len; i++){
        DrawLetter(Hex[Len-i-1], Base.Cursor.Pos);
        SetCursor(1);
    }

    return 0;
}

int PrintDec(UINT64 Number){
    UINT64 Trans = Number;

    int Dec[20];
    int Len = 0;

    for(int i = 0; i < 20; i++){
        Dec[i] = (Trans % 10) + 48;
        Trans = Trans / 10;
        Len++;
        if(Trans == 0){
            break;
        }
    }

    for(int i = 0; i < Len; i++){
        DrawLetter(Dec[Len-i-1], Base.Cursor.Pos);
        SetCursor(1);
    }

    return 0;
}
