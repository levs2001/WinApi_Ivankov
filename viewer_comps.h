#ifndef HEADER_VIEWER_COMPS
#define HEADER_VIEWER_COMPS
#include<stddef.h>

typedef struct {
    char* buffer;
    size_t bufferSize;
}viewer_t;

viewer_t* InitViewer();
void ClearViewer(viewer_t* viewerPointer);
void SendFileInViewer(viewer_t* viewerPointer, char* filename);
void ShowViewer(viewer_t* viewerPointer, HDC hdc, LPRECT windRect);

#endif
