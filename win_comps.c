#include"win_comps.h"
#include"exceptions.h"

void CountWinSizesInSyms(myFont_t* myFontP, winParams_t* winParamsP) {
    winParamsP->widthInSyms = (winParamsP->width) / myFontP->width;
    winParamsP->heightInSyms = (winParamsP->height) / myFontP->height;
}

void SetWindowSize(winParams_t* winParamsP, HWND hwnd) {
    RECT winRect;
    GetClientRect(hwnd, &winRect);
    winParamsP->height = winRect.bottom - winRect.top;
    winParamsP->width = winRect.right - winRect.left;
}

winParams_t* GetWinParams(myFont_t* myFontP, HWND hwnd) {
    winParams_t* winParamsP = (winParams_t*)getMem(sizeof(winParams_t), "winParams");
    winParamsP->hdc = GetDC(hwnd);

    winParamsP->vScrollPos = 0;
    winParamsP->hScrollPos = 0;

    return winParamsP;
}

void ClearWinParams(winParams_t* winParamsP) {
    if(winParamsP == NULL)
        Exception(NULL_WIN_PARAMS_POINTER);

    freeMem(winParamsP, "winParams");
}
