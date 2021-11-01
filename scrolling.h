#ifndef HEADER_SCROLLING
#define HEADER_SCROLLING

#include"viewer_comps.h"

#define HORZ_SCROLL_DEFAULT false

void ScrollVertLineDownViewer(viewer_t* viewerP);
void ScrollVertLineUpViewer(viewer_t* viewerP);
void ScrollVertPageUpViewer(viewer_t* viewerP);
void ScrollVertPageDownViewer(viewer_t* viewerP);

void ScrollHorzLineDownViewer(viewer_t* viewerP);
void ScrollHorzLineUpViewer(viewer_t* viewerP);
void ScrollHorzPageUpViewer(viewer_t* viewerP);
void ScrollHorzPageDownViewer(viewer_t* viewerP);
#endif
