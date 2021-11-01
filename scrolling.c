#include"viewer_comps.h"
#include"scrolling.h"

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

