#ifndef HEADER_VIEWER_COMPS
#define HEADER_VIEWER_COMPS
#include<stddef.h>
#include"file_reader.h"
#include"text_comps.h"

typedef struct {
    LPRECT coord;
    size_t widthInSyms;
    HDC hdc;
}winParams_t;

typedef struct {
    reader_t* readerP;
    myFont_t* fontP;
    //Add windowParamms structure here, RECT and widthInSyms
    winParams_t* winParamsP;
}viewer_t;

void InitViewer(viewer_t* viewerP, HWND hwnd);
void ClearViewer(viewer_t* viewerP);
void SendFileInViewer(viewer_t* viewerP, char* filename);
void ShowViewer(viewer_t* viewerP, LPRECT windRect);

#endif
