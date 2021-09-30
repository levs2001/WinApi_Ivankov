#include<stdlib.h>
#include<windows.h>
#include"viewer_comps.h"
#include"file_reader.h"
#include"exceptions.h"

viewer_t* InitViewer() {
    viewer_t* viewerPointer = (viewer_t*)malloc(sizeof(viewer_t));
    return viewerPointer;
}

void SendFileInViewer(viewer_t* viewerPointer, char* filename) {
    viewerPointer->buffer = GetBufferFromFile(filename, &(viewerPointer->bufferSize));
}

void PrintTextInViewer(viewer_t* viewerPointer, HDC hdc, LPRECT windRectP) {
    //Here I will print text with TextOut
    //Make line break if we see line break in buffer and if meet the end of rect
    //    GetTextEx
}

void ShowViewer(viewer_t* viewerPointer, HDC hdc, LPRECT windRectP) {
    // Make parsing to next string
    // Make scrolling
    //    ExtTextOut(hdc, windRectP->left, windRectP->top, ETO_CLIPPED, windRectP, viewerPointer->buffer, viewerPointer->bufferSize, NULL);
    //    DrawText(hdc, viewerPointer->buffer, viewerPointer->bufferSize, windRectP, DT_EDITCONTROL | DT_PATH_ELLIPSIS);
}

void ClearViewer(viewer_t* viewerPointer) {
    ClearBuffer(viewerPointer->buffer);
    if(viewerPointer!=NULL)
        free(viewerPointer);
    else
        Exception(NULL_VIEWER_POINTER);
}
