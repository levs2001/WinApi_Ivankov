/*
    Файл с функциями, отвечающими за скроллинг.
    Комментарии к не static функциям можно посмотреть в заголовочном файле.
    Комментарии к static функциям можно посмотреть в объявлениях.
*/

#include"win_comps.h"
#include"scrolling.h"


void ResizeVscrollParams(winParams_t* winParamsP, size_t prLinesCount) {
    size_t oldVertMax = winParamsP->vScrollMax;

    if((long)(prLinesCount - winParamsP->heightInSyms) >= 0) {
        winParamsP->vScrollMax = prLinesCount - winParamsP->heightInSyms;
        winParamsP->vScrollPos = winParamsP->vScrollPos * ((double)winParamsP->vScrollMax / (oldVertMax > 0 ? oldVertMax : 1));
    } else {
        winParamsP->vScrollMax = 0;
        winParamsP->vScrollPos = 0;
    }
}

void ResizeHscrollParams(winParams_t* winParamsP, size_t maxStrLen, bool isHorzScroll) {
    size_t oldHorzMax = winParamsP->hScrollMax;

    if(isHorzScroll && maxStrLen > winParamsP->widthInSyms) {
        winParamsP->hScrollMax = maxStrLen - winParamsP->widthInSyms;
        winParamsP->hScrollPos = winParamsP->hScrollPos * ((double)winParamsP->hScrollMax / (oldHorzMax > 0 ? oldHorzMax : 1));
    } else {
        winParamsP->hScrollMax = 0;
        winParamsP->hScrollPos = 0;
    }
}

void ChangeVScrollPos(winParams_t* winParamsP, long delta) {
    if(delta > 0) {
        if(winParamsP->vScrollPos + delta > winParamsP->vScrollMax) {
            winParamsP->vScrollPos = winParamsP->vScrollMax;
            return;
        }
    } else {
        if((long)winParamsP->vScrollPos + delta < 0) {
            winParamsP->vScrollPos = 0;
            return;
        }
    }

    winParamsP->vScrollPos += delta;
}

void ScrollVertLineUpViewer(winParams_t* winParamsP) {
    ChangeVScrollPos(winParamsP, -1);
}

void ScrollVertLineDownViewer(winParams_t* winParamsP) {
    ChangeVScrollPos(winParamsP, 1);
}

void ScrollVertPageUpViewer(winParams_t* winParamsP) {
    ChangeVScrollPos(winParamsP, -winParamsP->heightInSyms);
}

void ScrollVertPageDownViewer(winParams_t* winParamsP) {
    ChangeVScrollPos(winParamsP, winParamsP->heightInSyms);
}

void ScrollHorzLineUpViewer(winParams_t* winParamsP, bool isHorzScroll) {
    if(isHorzScroll) {
        if(winParamsP->hScrollPos > 0) {
            winParamsP->hScrollPos -= 1;
        }
    }
}

void ScrollHorzLineDownViewer(winParams_t* winParamsP, bool isHorzScroll) {
    if(isHorzScroll) {
        if(winParamsP->hScrollPos < winParamsP->hScrollMax) {
            winParamsP->hScrollPos += 1;
        }
    }
}

void ScrollHorzPageUpViewer(winParams_t* winParamsP, bool isHorzScroll) {
    if(isHorzScroll) {
        if(winParamsP->hScrollPos > winParamsP->widthInSyms) {
            winParamsP->hScrollPos -= winParamsP->widthInSyms;
        } else {
            winParamsP->hScrollPos = 0;
        }
    }
}

void ScrollHorzPageDownViewer(winParams_t* winParamsP, bool isHorzScroll) {
    if(isHorzScroll) {
        if(winParamsP->hScrollPos + winParamsP->widthInSyms < winParamsP->hScrollMax) {
            winParamsP->hScrollPos += winParamsP->widthInSyms;
        } else {
            winParamsP->hScrollPos = winParamsP->hScrollMax;
        }
    }
}

size_t GetScrollPosMyFromSystem(size_t myScrollMax, int sysScrPos) {
    size_t myScrPos = sysScrPos;
    if(myScrollMax > SCROLL_RANGE_MAX) {
        myScrPos = (size_t)((double)sysScrPos / (double)SCROLL_RANGE_MAX * myScrollMax);
    }

    return myScrPos;
}

int GetScrollPosSystemFromMy(size_t myScrollMax, size_t myScrPos) {
    size_t sysScrPos = myScrPos;
    if(myScrollMax > SCROLL_RANGE_MAX) {
        sysScrPos = (size_t)((double)sysScrPos / myScrollMax * SCROLL_RANGE_MAX);
    }

    return (int)sysScrPos;
}
