#ifndef HEADER_EXCEPTIONS
#define HEADER_EXCEPTIONS

#include <stdio.h>

typedef enum {
    FILE_NOT_OPEN,
    NULL_BUFF_POINTER,
    NULL_READER_POINTER,
    NULL_VIEWER_POINTER
} eException;

void Exception(eException exceptionType);


#endif
