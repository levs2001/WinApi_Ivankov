#ifndef HEADER_VIEWER_COMPS
#define HEADER_VIEWER_COMPS
#include<stddef.h>
#include<stdbool.h>
#include"file_reader.h"
#include"text_comps.h"
#include"win_comps.h"

typedef struct {
    reader_t* readerP;
    myFont_t* fontP;
    winParams_t* winParamsP;
    bool isHorzScroll;
    //Counting during resize and vScrolling, need to know what part of buffer should be printed
    size_t firstPrSymI;
    size_t lastPrSymI;
}viewer_t;

void InitViewer(viewer_t* viewerP, HWND hwnd);
void ClearViewer(viewer_t* viewerP);
void SendFileInViewer(viewer_t* viewerP, char* filename);
void ShowViewer(viewer_t* viewerP);
void ResizeViewer(viewer_t* viewerP, HWND hwnd);
void SetPrintedBuffIndexes(viewer_t* viewerP);

void ProcessVscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);
void ProcessHscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);
void ProcessKeyDownViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

void WrapOnViewer(viewer_t* viewerP);
void WrapOffViewer(viewer_t* viewerP);
void CloseFileInViewer(viewer_t* viewerP);
#endif
