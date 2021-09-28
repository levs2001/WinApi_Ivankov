#include "viewer_comps.h"
#include <stdlib.h>

viewer_t* InitViewer() {
    viewer_t* viewerPointer = (viewer_t*)malloc(sizeof(viewer_t));
    return viewerPointer;
}
