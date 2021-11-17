/*
    Файл с функциями, отвечающими за работу с памятью.
    Комментарии к не static функциям можно посмотреть в заголовочном файле.
    Комментарии к static функциям можно посмотреть в объявлениях.
*/

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

