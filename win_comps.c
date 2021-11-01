#include"win_comps.h"
#include"exceptions.h"
#include"memory.h"
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

BOOL OpenFileDlg(HWND hwnd, PTCHAR name) {
    static OPENFILENAME ofn;
    static char szFilter[] = "Text Files(*.TXT)\0*.txt\0";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = name;
    ofn.nMaxFile = _MAX_PATH;
    ofn.lpstrFilter = szFilter;
    ofn.nFilterIndex = 1;
    ofn.lpstrTitle = TEXT("Пожалуйста, выберите файл");
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = "txt";
    ofn.lCustData = 0;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    return GetOpenFileName(&ofn);
}
