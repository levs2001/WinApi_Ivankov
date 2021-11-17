/*
    Файл с функциями, отвечающими за шрифт.
    Комментарии к не static функциям можно посмотреть в заголовочном файле.
    Комментарии к static функциям можно посмотреть в объявлениях.
*/

#include <windows.h>
#include "exceptions.h"
#include "text_comps.h"
#include "memory.h"

#define DEFAULT_MYFONT_HEIGHT 17
#define DEFAULT_MYFONT_WIDTH 8


myFont_t* CreateDefaultFont() {
    myFont_t* myFontP = (myFont_t*)getMem(sizeof(myFont_t), "myFont");
    myFontP->height = DEFAULT_MYFONT_HEIGHT;
    myFontP->width = DEFAULT_MYFONT_WIDTH;

    return myFontP;
}

void SelectFont(HDC hdc, myFont_t* myFontP) {
    LOGFONT lf;
    GetObject(GetStockObject(ANSI_FIXED_FONT), sizeof(LOGFONT), &lf);
    HFONT hFont = CreateFont(myFontP->height, myFontP->width,
                                  lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
                                  lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut,
                                  lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision,
                                  lf.lfQuality, lf.lfPitchAndFamily, lf.lfFaceName);

    SelectObject(hdc, hFont);
    DeleteObject(hFont);
}

void ClearFont(myFont_t* myFontP) {
    if(myFontP == NULL)
        Exception(NULL_FONT_POINTER);
    freeMem(myFontP, "myFont");
}
