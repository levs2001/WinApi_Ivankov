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

void ShowViewer(viewer_t* viewerPointer, HDC hdc, RECT windRect) {
    // Make parsing to next string
    // Make scrolling
    TextOut(hdc, windRect.left, windRect.top, viewerPointer->buffer, viewerPointer->bufferSize);
}

void ClearViewer(viewer_t* viewerPointer) {
    ClearBuffer(viewerPointer->buffer);
    if(viewerPointer!=NULL)
        free(viewerPointer);
    else
        Exception(NULL_VIEWER_POINTER);
}
