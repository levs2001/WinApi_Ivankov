#ifndef HEADER_EXCEPTIONS
#define HEADER_EXCEPTIONS

#include <stdio.h>

typedef enum {
    FILE_NOT_OPEN
} eException;

void Exception(eException exceptionType);


#endif
