#include<stdlib.h>
#include<windows.h>
#include"viewer_comps.h"
#include"file_reader.h"
#include"exceptions.h"
#include"text_comps.h"
#include"memory.h"

#define WINDOW_MIN_X 0
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
    // TODO: Here I can count printedLinesCount to know scrolling range
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

void PrintStrInViewer(char* str, size_t strSize, winParams_t* winParamsP, size_t fontHeight, size_t* curHeightP) {
    size_t curHeight = *curHeightP;

    size_t curSymN = 0;
    size_t symsCountToWr = 0;
    while(curSymN < strSize) {
        if(curSymN + winParamsP->widthInSyms < strSize) {
            symsCountToWr = winParamsP->widthInSyms;
        } else {
            symsCountToWr = strSize - curSymN;
        }
        TextOut(winParamsP->hdc, WINDOW_MIN_X, curHeight, str + curSymN, symsCountToWr);

        curSymN += symsCountToWr;
        curHeight += fontHeight;
    }

    *curHeightP = curHeight;
}

void PrintTextInViewer(viewer_t* viewerP) {
    winParams_t* winParamsP = viewerP->winParamsP;
    myFont_t* fontP = viewerP->fontP;
    reader_t* readerP = viewerP->readerP;

    //TODO: Refactor scrolling
    size_t curHeight = - winParamsP->vScrollPos * fontP->height;
    size_t curSymN = 0;

    // Printing strings to '\n'
    for(int i = 0; i < readerP->lnEndsSize; i++) {
        // + 1 for \n
        PrintStrInViewer(readerP->buffer + curSymN, readerP->lnEnds[i] - curSymN, winParamsP, fontP->height, &curHeight);
        curSymN = readerP->lnEnds[i] + 1;
    }

    //printing last string
    PrintStrInViewer(readerP->buffer + curSymN, readerP->bufferSize - curSymN, winParamsP, fontP->height, &curHeight);
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

void ScrollLineUpViewer(viewer_t* viewerP) {
    if(viewerP->winParamsP->vScrollPos > 0) {
        viewerP->winParamsP->vScrollPos -= 1;
    }
}

void ScrollLineDownViewer(viewer_t* viewerP) {
    //TODO: Remove opportunity to move under text
    viewerP->winParamsP->vScrollPos += 1;
}

void ScrollPageUpViewer(viewer_t* viewerP) {
    // TODO: Make this function
    if(viewerP->winParamsP->vScrollPos > 0) {
        viewerP->winParamsP->vScrollPos -= 1;
    }
}

void ScrollPageDownViewer(viewer_t* viewerP) {
    // TODO: Make this function
    viewerP->winParamsP->vScrollPos += 1;
}
