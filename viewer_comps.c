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
#define SCROLL_RANGE_MAX 65535
#define POS_NOT_STATED -1

static int CountPrLines(viewer_t* viewerP);
static void ResizeHscrollParams(viewer_t* viewerP);
static void ResizeVscrollParams(viewer_t* viewerP);
static void PrintTextInViewer(viewer_t* viewerP);
static size_t GetScrollPosMyFromSystem(size_t myScrollMax, int sysScrPos);
static int GetScrollPosSystemFromMy(size_t myScrollMax, size_t myScrPos);
// TODO divide to files and divide statics that now isn't signed as static

void ProcessVscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam) {
    int newSysPos = POS_NOT_STATED;

    switch(LOWORD(wParam)) {
    case SB_LINEUP:
        ScrollVertLineUpViewer(viewerP);
        break;
    case SB_LINEDOWN:
        ScrollVertLineDownViewer(viewerP);
        break;
    case SB_PAGEUP:
        ScrollVertPageUpViewer(viewerP);
        break;
    case SB_PAGEDOWN:
        ScrollVertPageDownViewer(viewerP);
        break;
    case SB_THUMBTRACK:
        newSysPos = HIWORD(wParam);
        viewerP->winParamsP->vScrollPos = GetScrollPosMyFromSystem(viewerP->winParamsP->vScrollMax, newSysPos);
        break;
    case SB_THUMBPOSITION:
        newSysPos = HIWORD(wParam);
        viewerP->winParamsP->vScrollPos = GetScrollPosMyFromSystem(viewerP->winParamsP->vScrollMax, newSysPos);
        break;
    }

    if(newSysPos == POS_NOT_STATED) {
        newSysPos = GetScrollPosSystemFromMy(viewerP->winParamsP->vScrollMax, viewerP->winParamsP->vScrollPos);
    }

    SetScrollPos(hwnd, SB_VERT, newSysPos, TRUE);
    SetPrintedBuffIndexes(viewerP);
    InvalidateRect(hwnd, NULL, TRUE);
}

void ProcessHscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam) {
    int newSysPos = POS_NOT_STATED;

    switch(LOWORD(wParam)) {
    case SB_LINEUP:
        ScrollHorzLineUpViewer(viewerP);
        break;
    case SB_LINEDOWN:
        ScrollHorzLineDownViewer(viewerP);
        break;
    case SB_PAGEUP:
        ScrollHorzPageUpViewer(viewerP);
        break;
    case SB_PAGEDOWN:
        ScrollHorzPageDownViewer(viewerP);
        break;
    case SB_THUMBPOSITION:
        newSysPos = HIWORD(wParam);
        viewerP->winParamsP->hScrollPos = GetScrollPosMyFromSystem(viewerP->winParamsP->hScrollMax, newSysPos);
        break;
    }

    if(newSysPos == POS_NOT_STATED) {
        newSysPos = GetScrollPosSystemFromMy(viewerP->winParamsP->hScrollMax, viewerP->winParamsP->hScrollPos);
    }

    SetScrollPos(hwnd, SB_HORZ, newSysPos, TRUE);
    InvalidateRect(hwnd, NULL, TRUE);
}

void ProcessKeyDownViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam) {
    int newSysVpos = POS_NOT_STATED;
    int newSysHpos = POS_NOT_STATED;

    switch (wParam) {
    case VK_UP:
        ScrollVertLineUpViewer(viewerP);
        break;
    case VK_DOWN:
        ScrollVertLineDownViewer(viewerP);
        break;
    case VK_PRIOR: //Page up key
        ScrollVertPageUpViewer(viewerP);
        break;
    case VK_NEXT: //Page down key
        ScrollVertPageDownViewer(viewerP);
        break;
    case VK_LEFT:
        ScrollHorzLineUpViewer(viewerP);
        break;
    case VK_RIGHT:
        ScrollHorzLineDownViewer(viewerP);
        break;
    }

    newSysVpos = GetScrollPosSystemFromMy(viewerP->winParamsP->vScrollMax, viewerP->winParamsP->vScrollPos);
    if (newSysVpos  != GetScrollPos(hwnd, SB_VERT)) {
        SetScrollPos(hwnd, SB_VERT, newSysVpos, TRUE);
        SetPrintedBuffIndexes(viewerP);
        InvalidateRect(hwnd, NULL, TRUE);
    }

    newSysHpos = GetScrollPosSystemFromMy(viewerP->winParamsP->hScrollMax, viewerP->winParamsP->hScrollPos);
    if (newSysHpos  != GetScrollPos(hwnd, SB_HORZ)) {
        SetScrollPos(hwnd, SB_HORZ, newSysHpos, TRUE);
        InvalidateRect(hwnd, NULL, TRUE);
    }
}

static size_t GetScrollPosMyFromSystem(size_t myScrollMax, int sysScrPos) {
    size_t myScrPos = sysScrPos;
    if(myScrollMax > SCROLL_RANGE_MAX) {
        myScrPos = (size_t)((double)sysScrPos / (double)SCROLL_RANGE_MAX * myScrollMax);
    }

    return myScrPos;
}

static int GetScrollPosSystemFromMy(size_t myScrollMax, size_t myScrPos) {
    size_t sysScrPos = myScrPos;
    if(myScrollMax > SCROLL_RANGE_MAX) {
        sysScrPos = (size_t)((double)sysScrPos / myScrollMax * SCROLL_RANGE_MAX);
    }

    return (int)sysScrPos;
}

static void ResizeVscrollParams(viewer_t* viewerP) {
    long prLinesCount = CountPrLines(viewerP);
    size_t oldVertMax = viewerP->winParamsP->vScrollMax;

    if((long)(prLinesCount - viewerP->winParamsP->heightInSyms) >= 0) {
        viewerP->winParamsP->vScrollMax = prLinesCount - viewerP->winParamsP->heightInSyms;
        viewerP->winParamsP->vScrollPos = viewerP->winParamsP->vScrollPos * ((double)viewerP->winParamsP->vScrollMax / (oldVertMax > 0 ? oldVertMax : 1));
    } else {
        viewerP->winParamsP->vScrollMax = 0;
    }
}

static void ResizeHscrollParams(viewer_t* viewerP) {
    size_t oldHorzMax = viewerP->winParamsP->hScrollMax;

    if(viewerP->isHorzScroll && viewerP->readerP->maxStrLen > viewerP->winParamsP->widthInSyms) {
        viewerP->winParamsP->hScrollMax = viewerP->readerP->maxStrLen - viewerP->winParamsP->widthInSyms;
        viewerP->winParamsP->hScrollPos = viewerP->winParamsP->hScrollPos * ((double)viewerP->winParamsP->hScrollMax / (oldHorzMax > 0 ? oldHorzMax : 1));
    } else {
        viewerP->winParamsP->hScrollMax = 0;
    }
}

void ResizeViewer(viewer_t* viewerP, HWND hwnd) {
    SetWindowSize(viewerP->winParamsP, hwnd);
    CountWinSizesInSyms(viewerP->fontP, viewerP->winParamsP);
    ResizeVscrollParams(viewerP);
    ResizeHscrollParams(viewerP);
    SetScrollRange(hwnd, SB_VERT, 0, viewerP->winParamsP->vScrollMax < SCROLL_RANGE_MAX ? viewerP->winParamsP->vScrollMax : SCROLL_RANGE_MAX, FALSE);
    SetScrollRange(hwnd, SB_HORZ, 0, viewerP->winParamsP->hScrollMax < SCROLL_RANGE_MAX ? viewerP->winParamsP->hScrollMax : SCROLL_RANGE_MAX, FALSE);
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
    viewerP->winParamsP->hScrollMax = 0;
    viewerP->winParamsP->vScrollMax = 0;
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
