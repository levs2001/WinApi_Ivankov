#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include"viewer_comps.h"
#include"file_reader.h"
#include"exceptions.h"
#include"text_comps.h"
#include"memory.h"

#define WINDOW_MIN_X 0

static int CountPrLines(viewer_t* viewerP);
static void SetVscrollMax(viewer_t* viewerP);
static void SetHscrollMax(viewer_t* viewerP);
static void PrintStrInViewer(char* str, size_t strSize, winParams_t* winParamsP, size_t fontHeight, int* shiftP);
static void PrintParsedTextInViewer(viewer_t* viewerP);
static void PrintTextInViewer(viewer_t* viewerP);

void ResizeViewer(viewer_t* viewerP, HWND hwnd) {
    SetWindowSize(viewerP->winParamsP, hwnd);
    CountWinSizesInSyms(viewerP->fontP, viewerP->winParamsP);
    SetVscrollMax(viewerP);
    SetHscrollMax(viewerP);
    SetScrollRange(hwnd, SB_VERT, 0, viewerP->winParamsP->vScrollMax, FALSE);
    SetScrollRange(hwnd, SB_HORZ, 0, viewerP->winParamsP->hScrollMax, FALSE);
}

void InitViewer(viewer_t* viewerP, HWND hwnd) {
    viewerP->readerP = (reader_t*)getMem(sizeof(reader_t), "reader");
    viewerP->fontP = CreateDefaultFont();
    viewerP->winParamsP = GetWinParams(viewerP->fontP, hwnd);

    SelectFont(viewerP->winParamsP->hdc, viewerP->fontP);

    //Will be done in normal view after added menu
    viewerP->isHorzScroll = HORZ_SCROLL;
}

void SendFileInViewer(viewer_t* viewerP, char* filename) {
    WriteFileInReader(viewerP->readerP, filename);
}

void ShowViewer(viewer_t* viewerP) {
    if(viewerP->isHorzScroll) {
        PrintTextInViewer(viewerP);
    } else {
        PrintParsedTextInViewer(viewerP);
    }
}

void ClearViewer(viewer_t* viewerStaticP) {
    if(viewerStaticP == NULL) {
        Exception(NULL_VIEWER_POINTER);
    }

    ClearReader(viewerStaticP->readerP);
    ClearWinParams(viewerStaticP->winParamsP);
    ClearFont(viewerStaticP->fontP);
}

void ScrollVertLineUpViewer(viewer_t* viewerP) {
    if(viewerP->winParamsP->vScrollPos > 0) {
        viewerP->winParamsP->vScrollPos -= 1;
    }
}

void ScrollVertLineDownViewer(viewer_t* viewerP) {
    if(viewerP->winParamsP->vScrollPos < viewerP->winParamsP->vScrollMax) {
        viewerP->winParamsP->vScrollPos += 1;
    }
}

void ScrollVertPageUpViewer(viewer_t* viewerP) {
    if(viewerP->winParamsP->vScrollPos > viewerP->winParamsP->heightInSyms) {
        viewerP->winParamsP->vScrollPos -= viewerP->winParamsP->heightInSyms;
    } else {
        viewerP->winParamsP->vScrollPos = 0;
    }
}

void ScrollVertPageDownViewer(viewer_t* viewerP) {
    if(viewerP->winParamsP->vScrollPos + viewerP->winParamsP->heightInSyms < viewerP->winParamsP->vScrollMax) {
        viewerP->winParamsP->vScrollPos += viewerP->winParamsP->heightInSyms;
    } else {
        viewerP->winParamsP->vScrollPos = viewerP->winParamsP->vScrollMax;
    }
}

void ScrollHorzLineUpViewer(viewer_t* viewerP) {
    if(viewerP->isHorzScroll) {
        if(viewerP->winParamsP->hScrollPos > 0) {
            viewerP->winParamsP->hScrollPos -= 1;
        }
    }
}

void ScrollHorzLineDownViewer(viewer_t* viewerP) {
    if(viewerP->isHorzScroll) {
        if(viewerP->winParamsP->hScrollPos < viewerP->winParamsP->hScrollMax) {
            viewerP->winParamsP->hScrollPos += 1;
        }
    }
}

void ScrollHorzPageUpViewer(viewer_t* viewerP) {
    if(viewerP->isHorzScroll) {
        if(viewerP->winParamsP->hScrollPos > viewerP->winParamsP->widthInSyms) {
            viewerP->winParamsP->hScrollPos -= viewerP->winParamsP->widthInSyms;
        } else {
            viewerP->winParamsP->hScrollPos = 0;
        }
    }
}

void ScrollHorzPageDownViewer(viewer_t* viewerP) {
    if(viewerP->isHorzScroll) {
        if(viewerP->winParamsP->hScrollPos + viewerP->winParamsP->widthInSyms < viewerP->winParamsP->hScrollMax) {
            viewerP->winParamsP->hScrollPos += viewerP->winParamsP->widthInSyms;
        } else {
            viewerP->winParamsP->hScrollPos = viewerP->winParamsP->hScrollMax;
        }
    }
}

static int CountPrLines(viewer_t* viewerP) {
    reader_t* readerP = viewerP->readerP;

    //Counting first str in file
    int prLinesCount = ceil((double)readerP->lnEnds[0] / viewerP->winParamsP->widthInSyms);

    //Counting strs between \n
    for(int i = 0; i < readerP->lnEndsSize - 1; i++) {
        prLinesCount += ceil((double)(readerP->lnEnds[i + 1] - readerP->lnEnds[i]) / viewerP->winParamsP->widthInSyms);
    }

    //Counting last string
    prLinesCount += ceil((double)(readerP->bufferSize - readerP->lnEnds[readerP->lnEndsSize - 1] - readerP->lnEndsSize)
                         / viewerP->winParamsP->widthInSyms);
    return prLinesCount;
}

static void SetVscrollMax(viewer_t* viewerP) {
    int prLinesCount = CountPrLines(viewerP);
    if((int)(prLinesCount - viewerP->winParamsP->heightInSyms) >= 0)
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

static void PrintStrInViewer(char* str, size_t strSize, winParams_t* winParamsP, size_t fontHeight, int* shiftP) {
    int shift = *shiftP;

    if(strSize == 0) {
        if(shift >= 0 && shift < (int)winParamsP->height) {
            TextOut(winParamsP->hdc, WINDOW_MIN_X, shift, "\n", 1);
        }
        shift += fontHeight;
    } else {
        size_t curSymN = 0;
        size_t symsCountToWr = 0;
        while(curSymN < strSize) {
            if(curSymN + winParamsP->widthInSyms < strSize) {
                symsCountToWr = winParamsP->widthInSyms;
            } else {
                symsCountToWr = strSize - curSymN;
            }
            if(shift >= 0 && shift < (int)winParamsP->height) {
                TextOut(winParamsP->hdc, WINDOW_MIN_X, shift, str + curSymN, symsCountToWr);
            }
            curSymN += symsCountToWr;
            shift += fontHeight;
        }
    }
    *shiftP = shift;
}

static void PrintParsedTextInViewer(viewer_t* viewerP) {
    //TODO: Fix segmentation fauld with huge texts
    // This printing is for mode without scrolling
    winParams_t* winParamsP = viewerP->winParamsP;
    myFont_t* fontP = viewerP->fontP;
    reader_t* readerP = viewerP->readerP;

    int shift = -winParamsP->vScrollPos * fontP->height;
    size_t curSymN = 0;

    // Printing strings to '\n'
    for(int i = 0; i < readerP->lnEndsSize && shift < (int)winParamsP->height; i++) {
        // + 1 for \n
        PrintStrInViewer(readerP->buffer + curSymN, readerP->lnEnds[i] - curSymN, winParamsP, fontP->height, &shift);
        curSymN = readerP->lnEnds[i] + 1;
    }

    //printing last string
    if(shift < (int)winParamsP->height) {
        PrintStrInViewer(readerP->buffer + curSymN, readerP->bufferSize - curSymN - readerP->lnEndsSize,
                         winParamsP, fontP->height, &shift);
    }
}

static void PrintTextInViewer(viewer_t* viewerP) {
    //TODO: Don't print out of window
    // This printing is for mode with scrolling
    winParams_t* winParamsP = viewerP->winParamsP;
    myFont_t* fontP = viewerP->fontP;
    reader_t* readerP = viewerP->readerP;

    size_t curHeight = - winParamsP->vScrollPos * fontP->height;
    size_t curWidth = - winParamsP->hScrollPos * fontP->width;
    size_t curSymN = 0;

    // Printing strings to '\n'
    for(int i = 0; i < readerP->lnEndsSize; i++) {
        // + 1 for \n
        TextOut(viewerP->winParamsP->hdc, curWidth, curHeight, readerP->buffer + curSymN, readerP->lnEnds[i] - curSymN);
        //PrintStrInViewer(readerP->buffer + curSymN, readerP->lnEnds[i] - curSymN, winParamsP, fontP->height, &curHeight);
        curSymN = readerP->lnEnds[i] + 1;
        curHeight += viewerP->fontP->height;
    }

    //printing last string
    TextOut(viewerP->winParamsP->hdc, curWidth, curHeight, readerP->buffer + curSymN, readerP->bufferSize - curSymN - readerP->lnEndsSize);
}
