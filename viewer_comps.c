#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include"viewer_comps.h"
#include"file_reader.h"
#include"exceptions.h"
#include"text_comps.h"
#include"memory.h"

#define WINDOW_MIN_X 0
//TODO: Divide window functions
//TODO: Fix horizontal scrolling

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

int CountPrLines(viewer_t* viewerP) {
    reader_t* readerP = viewerP->readerP;

    //Count first str in file
    int prLinesCount = ceil((double)readerP->lnEnds[0] / viewerP->winParamsP->widthInSyms);

    //Count strs between \n
    for(int i = 0; i < readerP->lnEndsSize - 1; i++) {
        prLinesCount += ceil((double)(readerP->lnEnds[i + 1] - readerP->lnEnds[i]) / viewerP->winParamsP->widthInSyms);
    }

    //Count last string
    prLinesCount += ceil((double)(readerP->bufferSize - readerP->lnEnds[readerP->lnEndsSize - 1] - readerP->lnEndsSize)
                         / viewerP->winParamsP->widthInSyms);
    return prLinesCount;
}

void SetVscrollMax(viewer_t* viewerP) {
    int prLinesCount = CountPrLines(viewerP);//viewerP->readerP->bufferSize / viewerP->winParamsP->widthInSyms + viewerP->readerP->lnEndsSize;
    if((int)(prLinesCount - viewerP->winParamsP->heightInSyms) >= 0)
        viewerP->winParamsP->vScrollMax = prLinesCount - viewerP->winParamsP->heightInSyms;
    else
        viewerP->winParamsP->vScrollMax = 0;
}

void SetHscrollMax(viewer_t* viewerP) {
    if(viewerP->isHorzScroll && viewerP->readerP->maxStrLen > viewerP->winParamsP->widthInSyms) {
        viewerP->winParamsP->hScrollMax = viewerP->readerP->maxStrLen - viewerP->winParamsP->widthInSyms;
    } else {
        viewerP->winParamsP->hScrollMax = 0;
    }
}

void ResizeViewer(viewer_t* viewerP, HWND hwnd) {
    SetWindowSize(viewerP->winParamsP, hwnd);
    CountWinSizesInSyms(viewerP->fontP, viewerP->winParamsP);
    SetVscrollMax(viewerP);
    SetHscrollMax(viewerP);
    SetScrollRange(hwnd, SB_VERT, 0, viewerP->winParamsP->vScrollMax, FALSE);
    SetScrollRange(hwnd, SB_HORZ, 0, viewerP->winParamsP->hScrollMax, FALSE);
    //TODO: Check this count, it's just experiment
    // TODO: Here I can count printedLinesCount to know scrolling range
}

void ClearWinParams(winParams_t* winParamsP) {
    if(winParamsP == NULL)
        Exception(NULL_WIN_PARAMS_POINTER);

    freeMem(winParamsP, "winParams");
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

void PrintStrInViewer(char* str, size_t strSize, winParams_t* winParamsP, size_t fontHeight, size_t* curHeightP) {
    // Case for "\n" in string
    if(strSize == 0) {
        TextOut(winParamsP->hdc, WINDOW_MIN_X, *curHeightP, "\n", 1);
        *curHeightP += fontHeight;
    }

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

void PrintParsedTextInViewer(viewer_t* viewerP) {
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
    PrintStrInViewer(readerP->buffer + curSymN, readerP->bufferSize - curSymN - readerP->lnEndsSize,
                     winParamsP, fontP->height, &curHeight);
}

void PrintTextInViewer(viewer_t* viewerP) {
    winParams_t* winParamsP = viewerP->winParamsP;
    myFont_t* fontP = viewerP->fontP;
    reader_t* readerP = viewerP->readerP;

    //TODO: Refactor scrolling
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
