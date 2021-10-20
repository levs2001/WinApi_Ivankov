#ifndef HEADER_VIEWER_COMPS
#define HEADER_VIEWER_COMPS
#include<stddef.h>
#include<stdbool.h>
#include"file_reader.h"
#include"text_comps.h"
#include"win_comps.h"

#define HORZ_SCROLL false

typedef struct {
    reader_t* readerP;
    myFont_t* fontP;
    winParams_t* winParamsP;
    bool isHorzScroll;
}viewer_t;

void InitViewer(viewer_t* viewerP, HWND hwnd);
void ClearViewer(viewer_t* viewerP);
void SendFileInViewer(viewer_t* viewerP, char* filename);
void ShowViewer(viewer_t* viewerP);
void ResizeViewer(viewer_t* viewerP, HWND hwnd);

void ScrollVertLineDownViewer(viewer_t* viewerP);
void ScrollVertLineUpViewer(viewer_t* viewerP);
void ScrollVertPageUpViewer(viewer_t* viewerP);
void ScrollVertPageDownViewer(viewer_t* viewerP);

void ScrollHorzLineDownViewer(viewer_t* viewerP);
void ScrollHorzLineUpViewer(viewer_t* viewerP);
void ScrollHorzPageUpViewer(viewer_t* viewerP);
void ScrollHorzPageDownViewer(viewer_t* viewerP);
#endif
