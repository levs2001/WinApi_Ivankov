#include <stdlib.h>
#include "viewer_comps.h"
#include "file_reader.h"
#include "exceptions.h"

viewer_t* InitViewer() {
    viewer_t* viewerPointer = (viewer_t*)malloc(sizeof(viewer_t));
    return viewerPointer;
}

void ClearViewer(viewer_t* viewerPointer) {
    ClearBuffer(viewerPointer->buffer);
    if(viewerPointer!=NULL)
        free(viewerPointer);
    else
        Exception(NULL_VIEWER_POINTER);
}
