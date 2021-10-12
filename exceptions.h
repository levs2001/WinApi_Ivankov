#ifndef HEADER_EXCEPTIONS
#define HEADER_EXCEPTIONS

#include <stdio.h>

typedef enum {
    FILE_NOT_OPEN,
    NULL_BUFF_POINTER,
    NULL_READER_POINTER,
    NULL_VIEWER_POINTER,
    NULL_WIN_PARAMS_POINTER,
    NULL_FONT_POINTER,
    NULL_LN_ENDS_POINTER,
    REALLOC_REFUSE_LN_ENDS
} eException;

void Exception(eException exceptionType);
void logMsg(char* msg);

#endif
