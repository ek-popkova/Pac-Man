#include "drawingFunctions.h"

//colour constants
COLORREF YELLOW = RGB(255, 255, 0);
COLORREF GOLD = RGB(255, 215, 0);
COLORREF PINK = RGB(255, 0, 255);
COLORREF LIME = RGB(0, 255, 0);
COLORREF CRIMSON = RGB(220, 20, 60);

wchar_t buferForInt[128];


void seedDrawing(HDC hdc)
{
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, YELLOW);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, YELLOW);
    for (int i = 0; i < FIELD_SIZE_HORIZONTAL; i++)
    {
        for (int j = 0; j < FIELD_SIZE_VERTICAL; j++)
        {
            if ((FIELD[i][j] == SEED) || ((FIELD[i][j] == CHANGESEED))) {
                Ellipse(hdc, i * SQUARE_SIZE + SEED_SIZE, j * SQUARE_SIZE + SEED_SIZE, (i + 1) * SQUARE_SIZE - SEED_SIZE, (j + 1) * SQUARE_SIZE - SEED_SIZE);
            }
        }
    }
}


void packmanDrawing(HDC hdc)
{
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, GOLD);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, GOLD);
    Ellipse(hdc, Packman.x, Packman.y, Packman.x + SQUARE_SIZE, Packman.y + SQUARE_SIZE);
}

void ghostDrawing(HDC hdc, entityWithCoordinates ghost, COLORREF colour)
{
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, colour);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, colour);
    Ellipse(hdc, ghost.x, ghost.y, ghost.x + SQUARE_SIZE, ghost.y + SQUARE_SIZE);
}

void textDrawing(HDC hdc)
{
    int c = wsprintf(buferForInt, TEXT("Your score is: %i"), calculateScore());
    TextOut(hdc, 30, 430, buferForInt, c);
    int d;
    switch (gameStatus)
    {
    case THREE:
    {
        d = wsprintf(buferForInt, TEXT("♥ ♥ ♥"));
        TextOut(hdc, 195, 230, buferForInt, d);
        break;
    }
    case TWO:
    {
        d = wsprintf(buferForInt, TEXT("♥ ♥"));
        TextOut(hdc, 195, 230, buferForInt, d);
        break;
    }
    case ONE:
    {
        d = wsprintf(buferForInt, TEXT("♥"));
        TextOut(hdc, 195, 230, buferForInt, d);
        break;
    }
    };
}

void statusDrawing(HDC hdc)
{
    if ((gameStatus == THREE) || (gameStatus == TWO) || (gameStatus == ONE))
    {
        int m = wsprintf(buferForInt, TEXT("PACKMAN"));
        TextOut(hdc, 180, 210, buferForInt, m);
    }
    if (gameStatus == WIN)
    {
        int m = wsprintf(buferForInt, TEXT("You win!"));
        TextOut(hdc, 188, 210, buferForInt, m);
        int n = wsprintf(buferForInt, TEXT("Press ESC to restart, SPACE to quit"));
        TextOut(hdc, 110, 230, buferForInt, n);
    }
    if (gameStatus == LOSE)
    {
        int m = wsprintf(buferForInt, TEXT("You loose"));
        TextOut(hdc, 180, 210, buferForInt, m);
        int n = wsprintf(buferForInt, TEXT("Press ESC to restart, SPACE to quit"));
        TextOut(hdc, 110, 250, buferForInt, n);
        int k = wsprintf(buferForInt, TEXT("Your score is %i"), calculateScore());
        TextOut(hdc, 160, 230, buferForInt, k);
    }
}

void virtualDrawing(HDC hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBM = CreateCompatibleBitmap(hdc, ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top);
    SelectObject(memDC, memBM);
    BG = LoadImage(hInstance, TEXT(".\\pacmanworld.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    //remove it 
    BITMAP bitmap;

    SelectObject(memDC, BG);
    GetObject(BG, sizeof(bitmap), &bitmap);

    seedDrawing(memDC);
    packmanDrawing(memDC);

    ghostDrawing(memDC, Ghost[0], LIME);
    ghostDrawing(memDC, Ghost[1], LIME);
    ghostDrawing(memDC, Ghost[2], LIME);
    ghostDrawing(memDC, Ghost[3], CRIMSON); //это умный

    textDrawing(memDC);
    statusDrawing(memDC);

    BitBlt(hdc, 0, 0, ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top, memDC, 0, 0, SRCCOPY);
    DeleteDC(memDC);
    DeleteObject(memBM);
}

//void fieldDrawing(HDC hdc)
//{
//    for (int i = 0; i < FIELD_SIZE_HORIZONTAL; i++)
//    {
//        for (int j = 0; j < FIELD_SIZE_VERTICAL; j++)
//        {
//            SelectObject(hdc, GetStockObject(DC_BRUSH));
//            SetDCBrushColor(hdc, RGB(255, 255, 255));
//            Rectangle(hdc, i * SQUARE_SIZE, j * SQUARE_SIZE, (i + 1) * SQUARE_SIZE, (j + 1) * SQUARE_SIZE);
//            if (FIELD[i][j] == BLOCK) {
//                SelectObject(hdc, GetStockObject(DC_BRUSH));
//                SetDCBrushColor(hdc, RGB(0, 0, 0));
//                Rectangle(hdc, i * SQUARE_SIZE, j * SQUARE_SIZE, (i + 1) * SQUARE_SIZE, (j + 1) * SQUARE_SIZE);
//            }
//        }
//    }
//}