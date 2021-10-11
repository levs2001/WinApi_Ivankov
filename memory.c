#include "memory.h"
#include "exceptions.h"
#include<stdlib.h>

void* getMem(size_t memSize, char* reason) {
    logMsg("get memory: ");
    logMsg(reason);
    logMsg("\n");

    return malloc(memSize);
}

void freeMem(void* pointer, char* reason) {
    logMsg("free: ");
    logMsg(reason);
    logMsg("\n");

    free(pointer);
}

