#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include"viewer_comps.h"
#include"file_reader.h"
#include"exceptions.h"
#include"text_comps.h"
#include"memory.h"
#include "scrolling.h"

#define WINDOW_MIN_X 0

static int CountPrLines(viewer_t* viewerP);
static void SetVscrollMax(viewer_t* viewerP);
static void SetHscrollMax(viewer_t* viewerP);
static void PrintTextInViewer(viewer_t* viewerP);

void ResizeViewer(viewer_t* viewerP, HWND hwnd) {
    SetWindowSize(viewerP->winParamsP, hwnd);
    CountWinSizesInSyms(viewerP->fontP, viewerP->winParamsP);
    SetVscrollMax(viewerP);
    SetHscrollMax(viewerP);
    SetScrollRange(hwnd, SB_VERT, 0, viewerP->winParamsP->vScrollMax, FALSE);
    SetScrollRange(hwnd, SB_HORZ, 0, viewerP->winParamsP->hScrollMax, FALSE);
    SetPrintedBuffIndexes(viewerP);
}

void SetPrintedBuffIndexes(viewer_t* viewerP) {
    winParams_t* winParamsP = viewerP->winParamsP;
    reader_t* readerP = viewerP->readerP;

    size_t firstPrI = 0;
    // оличество символов набранных до перехода строки
    size_t collectedSymsN = 0;
    // оличесво строк от начала, которые должны быть пропущены
    long shift = winParamsP->vScrollPos;

    for(; firstPrI < readerP->bufferSize && shift > 0; firstPrI++) {
        if(readerP->buffer[firstPrI] == '\n'
                || (collectedSymsN >= winParamsP->widthInSyms && !viewerP->isHorzScroll)) {
            collectedSymsN = 0;
            shift--;
        }
        collectedSymsN++;
    }

    //“еперь считаем lastPrI, дл€ этого просто посмотрим какие символы вывед€тс€ во viewer после firstPrI
    size_t lastPrI = 0;
    shift = winParamsP->heightInSyms;
    collectedSymsN = 0;

    for(lastPrI = firstPrI; (long)lastPrI < (long)readerP->bufferSize && shift > 0; lastPrI++) {
        if(readerP->buffer[lastPrI] == '\n'
                || (collectedSymsN >= winParamsP->widthInSyms && !viewerP->isHorzScroll)) {
            collectedSymsN = 0;
            shift--;
        }
        collectedSymsN++;
    }

    viewerP->firstPrSymI = firstPrI;
    viewerP->lastPrSymI = lastPrI;
}

void InitViewer(viewer_t* viewerP, HWND hwnd) {
    viewerP->readerP = (reader_t*)getMem(sizeof(reader_t), "reader");

    NullifyReader(viewerP->readerP);
    viewerP->firstPrSymI = 0;
    viewerP->lastPrSymI = 0;

    viewerP->fontP = CreateDefaultFont();
    viewerP->winParamsP = GetWinParams(viewerP->fontP, hwnd);

    SelectFont(viewerP->winParamsP->hdc, viewerP->fontP);
    viewerP->isHorzScroll = HORZ_SCROLL_DEFAULT;
}

void SendFileInViewer(viewer_t* viewerP, char* filename) {
    WriteFileInReader(viewerP->readerP, filename);
}

void CloseFileInViewer(viewer_t* viewerP) {
    EmptyReader(viewerP->readerP);
    viewerP->firstPrSymI = 0;
    viewerP->lastPrSymI = 0;
    viewerP->winParamsP->hScrollPos = 0;
    viewerP->winParamsP->vScrollPos = 0;
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

static int CountPrLines(viewer_t* viewerP) {
    size_t prLinesCount = 0;
    size_t collectedSymsN  = 0;

    for(long i = 0; i < viewerP->readerP->bufferSize; i++) {
        if(viewerP->readerP->buffer[i] == '\n'
                || (collectedSymsN >= viewerP->winParamsP->widthInSyms && !viewerP->isHorzScroll)) {
            collectedSymsN = 0;
            prLinesCount++;
        }
        collectedSymsN++;
    }

    if(collectedSymsN > 0) {
        prLinesCount++;
    }

    return prLinesCount;
}

static void SetVscrollMax(viewer_t* viewerP) {
    long prLinesCount = CountPrLines(viewerP);
    if((long)(prLinesCount - viewerP->winParamsP->heightInSyms) >= 0)
        viewerP->winParamsP->vScrollMax = prLinesCount - viewerP->winParamsP->heightInSyms;
    else
        viewerP->winParamsP->vScrollMax = 0;
}

static void SetHscrollMax(viewer_t* viewerP) {
    if(viewerP->isHorzScroll && viewerP->readerP->maxStrLen > viewerP->winParamsP->widthInSyms) {
        viewerP->winParamsP->hScrollMax = viewerP->readerP->maxStrLen - viewerP->winParamsP->widthInSyms;
    } else {
        viewerP->winParamsP->hScrollMax = 0;
    }
}

static void PrintTextInViewer(viewer_t* viewerP) {
    size_t collectedPrSym = 0;
    size_t yPrPos = 0;
    size_t curWidth = - viewerP->winParamsP->hScrollPos * viewerP->fontP->width;

    for(size_t i = viewerP->firstPrSymI; i < viewerP->lastPrSymI; i++) {
        if(viewerP->readerP->buffer[i] == '\n'
                || (collectedPrSym >= viewerP->winParamsP->widthInSyms && !viewerP->isHorzScroll)) {
            TextOut(viewerP->winParamsP->hdc, curWidth, yPrPos, viewerP->readerP->buffer + i - collectedPrSym, collectedPrSym);
            yPrPos += viewerP->fontP->height;
            collectedPrSym = 0;
        }
        collectedPrSym++;
    }

    if(collectedPrSym > 0) {
        TextOut(viewerP->winParamsP->hdc, curWidth, yPrPos, viewerP->readerP->buffer + viewerP->lastPrSymI - collectedPrSym, collectedPrSym);
    }
}

void WrapOnViewer(viewer_t* viewerP) {
    viewerP->isHorzScroll = false;
    viewerP->winParamsP->vScrollPos = 0;
    viewerP->winParamsP->vScrollPos = 0;
}

void WrapOffViewer(viewer_t* viewerP) {
    viewerP->isHorzScroll = true;
    viewerP->winParamsP->vScrollPos = 0;
    viewerP->winParamsP->vScrollPos = 0;
}
