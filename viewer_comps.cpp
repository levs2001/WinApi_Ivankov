#include<stdlib.h>
#include<windows.h>
#include"viewer_comps.h"
#include"file_reader.h"
#include"exceptions.h"
#include"text_comps.h"
#include"memory.h"

//TODO: Divide window functions
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

    SetWindowSize(winParamsP, hwnd);
    CountWinSizesInSyms(myFontP, winParamsP);

    winParamsP->vScrollPos = 0;
    winParamsP->hScrollPos = 0;

    return winParamsP;
}

void ResizeViewer(viewer_t* viewerP, HWND hwnd) {
    SetWindowSize(viewerP->winParamsP, hwnd);
    CountWinSizesInSyms(viewerP->fontP, viewerP->winParamsP);
}

void ClearWinParams(winParams_t* winParamsP) {
    if(winParamsP==NULL)
        Exception(NULL_WIN_PARAMS_POINTER);

    freeMem(winParamsP, "winParams");
}

void InitViewer(viewer_t* viewerP, HWND hwnd) {
    viewerP->readerP = (reader_t*)getMem(sizeof(reader_t), "reader");
    viewerP->fontP = CreateDefaultFont();
    viewerP->winParamsP = GetWinParams(viewerP->fontP, hwnd);

    SelectFont(viewerP->winParamsP->hdc, viewerP->fontP);
}

void SendFileInViewer(viewer_t* viewerP, char* filename) {
    WriteFileInReader(viewerP->readerP, filename);
}

void PrintTextInViewer(viewer_t* viewerP) {
    //TODO: I should watch all parts of buffer between "\n", this parts I should print using parser
    //Make line break if we see line break in buffer and if meet the end of rect
    winParams_t* winParamsP = viewerP->winParamsP;
    myFont_t* fontP = viewerP->fontP;
    reader_t* readerP = viewerP->readerP;

    size_t strCount = readerP->bufferSize / winParamsP->widthInSyms;
    size_t curHeight = - winParamsP->vScrollPos * fontP->height;
    size_t curSymN = 0;

    for(int i = 0; i < strCount; i++) {
        TextOut(winParamsP->hdc, 0, curHeight, readerP->buffer + curSymN, winParamsP->widthInSyms);
        curSymN += winParamsP->widthInSyms;
        curHeight += fontP->height;
    }
}

void ShowViewer(viewer_t* viewerP) {
    PrintTextInViewer(viewerP);
}

void ClearViewer(viewer_t* viewerStaticP) {
    if(viewerStaticP == NULL) {
        Exception(NULL_VIEWER_POINTER);
    }

    ClearReader(viewerStaticP->readerP);
    ClearWinParams(viewerStaticP->winParamsP);
    ClearFont(viewerStaticP->fontP);
}
