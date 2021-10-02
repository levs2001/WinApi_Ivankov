#include<stdlib.h>
#include<windows.h>
#include"viewer_comps.h"
#include"file_reader.h"
#include"exceptions.h"
#include"text_comps.h"

winParams_t* FillWindowParamsInViewer(viewer_t* viewerP, HWND hwnd) {
    winParams_t* winParamsP = (winParams_t*)malloc(sizeof(winParams_t));
    //    windowP->
    //TODO: Fill this function
    viewerP->winParamsP = winParamsP;
}

void InitViewer(viewer_t* viewerP, HWND hwnd) {
    viewerP->readerP = (reader_t*)malloc(sizeof(reader_t));
    viewerP->fontP = CreateDefaultFont();
    //TODO: Think about deleting hFont object, maybe I don'need it, becaus it uses onse and than shoud be deleted
    FillWindowParamsInViewer(viewerP, hwnd);

    SelectObject(viewerP->winParamsP->hdc, viewerP->fontP->hFont);

}

void SendFileInViewer(viewer_t* viewerP, char* filename) {
    WriteFileInReader(viewerP->readerP, filename);
}

void PrintTextInViewer(viewer_t* viewerP, LPRECT windRectP) {
    //Here I will print text with TextOut
    //Make line break if we see line break in buffer and if meet the end of rect
    //TODO: Remove from here LPRECT param, get it from viewerP
    TextOut(viewerP->winParamsP->hdc, windRectP->left, windRectP->top, viewerP->readerP->buffer, viewerP->readerP->bufferSize);
}

void ShowViewer(viewer_t* viewerP, LPRECT windRectP) {
    // Make scrolling
    PrintTextInViewer(viewerP, windRectP);
}

void ClearViewer(viewer_t* viewerP) {
    ClearReader(viewerP->readerP);
    //TODO: Free winParams and viewerP here
}
