/*
    Основной файл с функциями viewer.
    Комментарии к не static функциям можно посмотреть в заголовочном файле.
    Комментарии к static функциям можно посмотреть в объявлениях.
*/

#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include"viewer_comps.h"
#include"file_reader.h"
#include"exceptions.h"
#include"text_comps.h"
#include"memory.h"
#include "scrolling.h"

/*Эта константа используется при скроллинге.
При THUMBTRACK и THUMBPOSITION мы переходим от системной позиции скроллинга к нашей,
в остальных случаях наоборот. Удобно узнавать какой случай, проверяя определена ли уже системная позиция
и в зависимости от этого отображать (от системного к нашему или наоборот).*/
#define POS_NOT_STATED -1

/*
    Функция меняет firstPrI (индекс первого символа из буффера, который будет выведен в окно)
    и lastPrI (индекс последнего) в viewer.
    params:
        [in|out] viewerP - указатель на viewer
*/
static void SetPrintedBuffIndexes(viewer_t* viewerP);

/*
    Функция считает количество строк, которое может быть выведено (при Wrap On это число больше, ведь включен перенос)
    Она учитывает даже строки, которые реально не выводятся, ведь их положение за пределами окна.
    Значение из этой функции в том числе используется для определения range у вертикального скроллинга.
    params:
        [in] viewerP - указатель на viewer
    return:
        количество строк
*/
static size_t CountPrLines(viewer_t* viewerP);

/*
    Выводит текст файла, который до этого открыли и записали во viewer, в окно
    params:
        [in] viewerP - указатель на viewer
        [in] hdc - дескриптор окна, в которое происходит вывод
*/
static void PrintTextInViewer(viewer_t* viewerP, HDC hdc);

/*
    Подсчитывает сколько символов из буффера должно быть выведено в конкретной строке окна. Нужна чтобы не выводить лишнее,
        если мы ушли горизонтальным скроллингом правее текста или собираемся вывести больше чем ширина окна.
    params:
        [in] collectedPrSym - количество символов набранных от начала строки до переноса (перенос и начало не обязательно LINE_END,
            они могут быть связаны с шириной окна, если включен режим WRAP ON)
        [in] hScrollPos - позиция горизонтального скроллинга
        [in] winWidthInSyms - ширина окна в символах (максимальное количество символов, которые могут поместиться в строку)
    return:
        количество символов в строке
*/
static size_t GetSymsCountToPrintInStr(size_t collectedPrSym, size_t hScrollPos, size_t winWidthInSyms);

void ProcessMouseWheel(viewer_t* viewerP, HWND hwnd, WPARAM wParam) {
    size_t myOldVscrollPos = viewerP->winParamsP->vScrollPos;

    long delta = -GET_WHEEL_DELTA_WPARAM(wParam) / 120;
    ChangeVScrollPos(viewerP->winParamsP, delta);

    if(viewerP->winParamsP->vScrollPos != myOldVscrollPos) {
        int newSysPos = GetScrollPosSystemFromMy(viewerP->winParamsP->vScrollMax, viewerP->winParamsP->vScrollPos);
        SetScrollPos(hwnd, SB_VERT, newSysPos, TRUE);
        SetPrintedBuffIndexes(viewerP);
        InvalidateRect(hwnd, NULL, TRUE);
    }
}

void ProcessVscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam) {
    int newSysPos = POS_NOT_STATED;
    size_t myOldVScrollPos = viewerP->winParamsP->vScrollPos;

    switch(LOWORD(wParam)) {
    case SB_LINEUP:
        ScrollVertLineUpViewer(viewerP->winParamsP);
        break;
    case SB_LINEDOWN:
        ScrollVertLineDownViewer(viewerP->winParamsP);
        break;
    case SB_PAGEUP:
        ScrollVertPageUpViewer(viewerP->winParamsP);
        break;
    case SB_PAGEDOWN:
        ScrollVertPageDownViewer(viewerP->winParamsP);
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

    if(viewerP->winParamsP->vScrollPos != myOldVScrollPos) {
        if(newSysPos == POS_NOT_STATED) {
            newSysPos = GetScrollPosSystemFromMy(viewerP->winParamsP->vScrollMax, viewerP->winParamsP->vScrollPos);
        }

        SetScrollPos(hwnd, SB_VERT, newSysPos, TRUE);
        SetPrintedBuffIndexes(viewerP);
        InvalidateRect(hwnd, NULL, TRUE);
    }
}

void ProcessHscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam) {
    int newSysPos = POS_NOT_STATED;
    size_t myOldHScrollPos = viewerP->winParamsP->hScrollPos;

    switch(LOWORD(wParam)) {
    case SB_LINEUP:
        ScrollHorzLineUpViewer(viewerP->winParamsP, viewerP->isHorzScroll);
        break;
    case SB_LINEDOWN:
        ScrollHorzLineDownViewer(viewerP->winParamsP, viewerP->isHorzScroll);
        break;
    case SB_PAGEUP:
        ScrollHorzPageUpViewer(viewerP->winParamsP, viewerP->isHorzScroll);
        break;
    case SB_PAGEDOWN:
        ScrollHorzPageDownViewer(viewerP->winParamsP, viewerP->isHorzScroll);
        break;
    case SB_THUMBTRACK:
        newSysPos = HIWORD(wParam);
        viewerP->winParamsP->hScrollPos = GetScrollPosMyFromSystem(viewerP->winParamsP->hScrollMax, newSysPos);
        break;
    case SB_THUMBPOSITION:
        newSysPos = HIWORD(wParam);
        viewerP->winParamsP->hScrollPos = GetScrollPosMyFromSystem(viewerP->winParamsP->hScrollMax, newSysPos);
        break;
    }

    if(viewerP->winParamsP->hScrollPos != myOldHScrollPos) {
        if(newSysPos == POS_NOT_STATED) {
            newSysPos = GetScrollPosSystemFromMy(viewerP->winParamsP->hScrollMax, viewerP->winParamsP->hScrollPos);
        }

        SetScrollPos(hwnd, SB_HORZ, newSysPos, TRUE);
        InvalidateRect(hwnd, NULL, TRUE);
    }
}

void ProcessKeyDownViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam) {
    int newSysVpos = POS_NOT_STATED;
    int newSysHpos = POS_NOT_STATED;

    size_t myOldVScrollPos = viewerP->winParamsP->vScrollPos;
    size_t myOldHScrollPos = viewerP->winParamsP->hScrollPos;

    switch (wParam) {
    case VK_UP:
        ScrollVertLineUpViewer(viewerP->winParamsP);
        break;
    case VK_DOWN:
        ScrollVertLineDownViewer(viewerP->winParamsP);
        break;
    case VK_PRIOR: //Page up key
        ScrollVertPageUpViewer(viewerP->winParamsP);
        break;
    case VK_NEXT: //Page down key
        ScrollVertPageDownViewer(viewerP->winParamsP);
        break;
    case VK_LEFT:
        ScrollHorzLineUpViewer(viewerP->winParamsP, viewerP->isHorzScroll);
        break;
    case VK_RIGHT:
        ScrollHorzLineDownViewer(viewerP->winParamsP, viewerP->isHorzScroll);
        break;
    }

    if(viewerP->winParamsP->vScrollPos != myOldVScrollPos) {
        newSysVpos = GetScrollPosSystemFromMy(viewerP->winParamsP->vScrollMax, viewerP->winParamsP->vScrollPos);
        SetScrollPos(hwnd, SB_VERT, newSysVpos, TRUE);
        SetPrintedBuffIndexes(viewerP);
        InvalidateRect(hwnd, NULL, TRUE);
    }

    if(viewerP->winParamsP->hScrollPos != myOldHScrollPos) {
        newSysHpos = GetScrollPosSystemFromMy(viewerP->winParamsP->hScrollMax, viewerP->winParamsP->hScrollPos);
        SetScrollPos(hwnd, SB_HORZ, newSysHpos, TRUE);
        SetPrintedBuffIndexes(viewerP);
        InvalidateRect(hwnd, NULL, TRUE);
    }
}

void ResizeViewer(viewer_t* viewerP, HWND hwnd) {
    ResizeWinParams(viewerP->winParamsP, hwnd, viewerP->fontP);

    // Масштабирование параметров скроллинга к новому размеру окна
    ResizeVscrollParams(viewerP, CountPrLines(viewerP));
    ResizeHscrollParams(viewerP->winParamsP, viewerP->readerP->maxStrLen, viewerP->isHorzScroll);
    SetScrollRange(hwnd, SB_VERT, 0, viewerP->winParamsP->vScrollMax < SCROLL_RANGE_MAX ? viewerP->winParamsP->vScrollMax : SCROLL_RANGE_MAX, FALSE);
    SetScrollRange(hwnd, SB_HORZ, 0, viewerP->winParamsP->hScrollMax < SCROLL_RANGE_MAX ? viewerP->winParamsP->hScrollMax : SCROLL_RANGE_MAX, FALSE);
    SetScrollPos(hwnd, SB_VERT, GetScrollPosSystemFromMy(viewerP->winParamsP->vScrollMax, viewerP->winParamsP->vScrollPos), TRUE);
    SetScrollPos(hwnd, SB_HORZ, GetScrollPosSystemFromMy(viewerP->winParamsP->hScrollMax, viewerP->winParamsP->hScrollPos), TRUE);
    SetPrintedBuffIndexes(viewerP);
}

void InitViewer(viewer_t* viewerP, HWND hwnd) {
    viewerP->readerP = (reader_t*)getMem(sizeof(reader_t), "reader");

    NullifyReader(viewerP->readerP);
    viewerP->firstPrSymI = 0;
    viewerP->lastPrSymI = 0;

    viewerP->fontP = CreateDefaultFont();
    viewerP->winParamsP = InitWinParams(hwnd, viewerP->fontP);

    SelectFont(GetDC(hwnd), viewerP->fontP);
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

void ShowViewer(viewer_t* viewerP, HDC hdc) {
    PrintTextInViewer(viewerP, hdc);
}

void WrapOnViewer(viewer_t* viewerP) {
    viewerP->isHorzScroll = false;
    viewerP->winParamsP->hScrollPos = 0;
}

void WrapOffViewer(viewer_t* viewerP) {
    viewerP->isHorzScroll = true;
    viewerP->winParamsP->hScrollPos = 0;
}

void ClearViewer(viewer_t* viewerStaticP) {
    if(viewerStaticP == NULL) {
        Exception(NULL_VIEWER_POINTER);
    }

    ClearReader(viewerStaticP->readerP);
    ClearWinParams(viewerStaticP->winParamsP);
    ClearFont(viewerStaticP->fontP);
}

static void SetPrintedBuffIndexes(viewer_t* viewerP) {
    winParams_t* winParamsP = viewerP->winParamsP;
    reader_t* readerP = viewerP->readerP;

    size_t firstPrI = 0;
    //Количество символов набранных до перехода строки
    size_t collectedSymsN = 0;
    //Количесво строк от начала, которые должны быть пропущены
    long shift = winParamsP->vScrollPos;

    for(; firstPrI < readerP->bufferSize && shift > 0; firstPrI++) {
        if(readerP->buffer[firstPrI] == LINE_END
                || (collectedSymsN >= winParamsP->widthInSyms && !viewerP->isHorzScroll)) {
            collectedSymsN = 0;
            shift--;
        }
        collectedSymsN++;
    }

    //Теперь считаем lastPrI, для этого просто посмотрим какие символы выведятся во viewer после firstPrI
    size_t lastPrI = 0;
    shift = winParamsP->heightInSyms;
    collectedSymsN = 0;

    for(lastPrI = firstPrI; (long)lastPrI < (long)readerP->bufferSize && shift > 0; lastPrI++) {
        if(readerP->buffer[lastPrI] == LINE_END
                || (collectedSymsN >= winParamsP->widthInSyms && !viewerP->isHorzScroll)) {
            collectedSymsN = 0;
            shift--;
        }
        collectedSymsN++;
    }

    viewerP->firstPrSymI = firstPrI;
    viewerP->lastPrSymI = lastPrI;
}

static size_t CountPrLines(viewer_t* viewerP) {
    size_t prLinesCount = 0;
    size_t collectedSymsN  = 0;

    for(long i = 0; i < viewerP->readerP->bufferSize; i++) {
        if(viewerP->readerP->buffer[i] == LINE_END
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

static size_t GetSymsCountToPrintInStr(size_t collectedPrSym, size_t hScrollPos, size_t winWidthInSyms) {
    size_t countToPr = collectedPrSym > hScrollPos ? collectedPrSym - hScrollPos : 0;
    countToPr = countToPr < winWidthInSyms ? countToPr : winWidthInSyms;

    return countToPr;
}

static void PrintTextInViewer(viewer_t* viewerP, HDC hdc) {
    size_t collectedPrSym = 0;
    size_t yPrPos = 0;
    size_t beginPrPos = 0;
    size_t countToPr = 0;

    for(size_t i = viewerP->firstPrSymI; i < viewerP->lastPrSymI; i++) {
        if(viewerP->readerP->buffer[i] == LINE_END
                || (collectedPrSym >= viewerP->winParamsP->widthInSyms && !viewerP->isHorzScroll)) {
            beginPrPos = i - collectedPrSym + viewerP->winParamsP->hScrollPos;
            countToPr = GetSymsCountToPrintInStr(collectedPrSym, viewerP->winParamsP->hScrollPos, viewerP->winParamsP->widthInSyms);

            TextOut(hdc, MIN_X, yPrPos, viewerP->readerP->buffer + beginPrPos, countToPr);
            yPrPos += viewerP->fontP->height;
            collectedPrSym = 0;
        }

        //Игнорируем переносы строк, они не должны попадать в вывод
        if(viewerP->readerP->buffer[i] != LINE_END) {
            collectedPrSym++;
        }
    }

    if(collectedPrSym > 0) {
        beginPrPos = viewerP->lastPrSymI - collectedPrSym + viewerP->winParamsP->hScrollPos;
        countToPr = GetSymsCountToPrintInStr(collectedPrSym, viewerP->winParamsP->hScrollPos, viewerP->winParamsP->widthInSyms);
        TextOut(hdc, MIN_X, yPrPos, viewerP->readerP->buffer + beginPrPos, countToPr);
    }
}
