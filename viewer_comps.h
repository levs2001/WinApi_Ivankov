#ifndef HEADER_VIEWER_COMPS
#define HEADER_VIEWER_COMPS
#include<stddef.h>
#include"file_reader.h"
#include"text_comps.h"

typedef struct {
    size_t width;
    size_t height;
    size_t widthInSyms;
    size_t heightInSyms;
    size_t vScrollPos;
    size_t hScrollPos;
    size_t vScrollMax;
    HDC hdc;
}winParams_t;

typedef struct {
    reader_t* readerP;
    myFont_t* fontP;
    winParams_t* winParamsP;
}viewer_t;

void InitViewer(viewer_t* viewerP, HWND hwnd);
void ClearViewer(viewer_t* viewerP);
void SendFileInViewer(viewer_t* viewerP, char* filename);
void ShowViewer(viewer_t* viewerP);
void ResizeViewer(viewer_t* viewerP, HWND hwnd);
void ScrollLineDownViewer(viewer_t* viewerP);
void ScrollLineUpViewer(viewer_t* viewerP);
void ScrollPageUpViewer(viewer_t* viewerP);
void ScrollPageDownViewer(viewer_t* viewerP);

#endif
