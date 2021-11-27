/*
    Файл с функциями изменения параметров, связанных с окном.
    Комментарии к не static функциям можно посмотреть в заголовочном файле.
    Комментарии к static функциям можно посмотреть в объявлениях.
*/

#include"win_comps.h"
#include"exceptions.h"
#include"memory.h"

/*
    Отображает размеры окна на размеры окна в символах (сколько можно записать по вертикали и горизонтали),
    перезаписывает эти параметры.
        params:
            [in|out] winParamsP - указатель на структуру с параметрами окна
            [in] myFontP - указатель на параметры используемого в окне шрифта
*/
static void CountWinSizesInSyms(winParams_t* winParamsP, myFont_t* myFontP) {
    winParamsP->widthInSyms = (winParamsP->width) / myFontP->width;
    winParamsP->heightInSyms = (winParamsP->height) / myFontP->height;
}

void SetWindowSize(winParams_t* winParamsP, HWND hwnd) {
    RECT winRect;
    GetClientRect(hwnd, &winRect);
    winParamsP->height = winRect.bottom - winRect.top;
    winParamsP->width = winRect.right - winRect.left;
}

void ResizeWinParams(winParams_t* winParamsP, HWND hwnd, myFont_t* myFontP) {
    SetWindowSize(winParamsP, hwnd);
    CountWinSizesInSyms(winParamsP, myFontP);
}

winParams_t* InitWinParams(HWND hwnd, myFont_t* myFontP) {
    winParams_t* winParamsP = (winParams_t*)getMem(sizeof(winParams_t), "winParams");
    ResizeWinParams(winParamsP, hwnd, myFontP);
    winParamsP->vScrollPos = 0;
    winParamsP->hScrollPos = 0;
    winParamsP->vScrollMax = 0;
    winParamsP->hScrollMax = 0;
    return winParamsP;
}

void ClearWinParams(winParams_t* winParamsP) {
    if(winParamsP == NULL)
        Exception(NULL_WIN_PARAMS_POINTER);

    freeMem(winParamsP, "winParams");
}

bool OpenFileDlg(HWND hwnd, LPSTR filenameP) {
    OPENFILENAME ofn;       // common dialog box structure
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = filenameP;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Text Files(*.TXT)\0*.txt\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    return GetOpenFileName(&ofn);
}
