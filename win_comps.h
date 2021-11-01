#ifndef HEADER_WIN_COMPS
#define HEADER_WIN_COMPS
#include<stddef.h>
#include<windows.h>
#include"text_comps.h"

typedef struct {
    size_t width;
    size_t height;
    size_t widthInSyms;
    size_t heightInSyms;

    size_t vScrollPos;
    size_t hScrollPos;
    size_t vScrollMax;
    size_t hScrollMax;
    HDC hdc;
}winParams_t;

void CountWinSizesInSyms(myFont_t* myFontP, winParams_t* winParamsP);
void SetWindowSize(winParams_t* winParamsP, HWND hwnd);
winParams_t* GetWinParams(myFont_t* myFontP, HWND hwnd);
void ClearWinParams(winParams_t* winParamsP);
BOOL OpenFileDlg(HWND hwnd, PTCHAR name);

#endif
