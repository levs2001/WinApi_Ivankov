#include "exceptions.h"

void Exception(eException exceptionType) {
    switch(exceptionType) {
    case FILE_NOT_OPEN:
        printf("Error: File for reading wasn't open.");
        break;
    case NULL_BUFF_POINTER:
        printf("Error: NULL pointer during buffer clearing.");
        break;
    case NULL_VIEWER_POINTER:
        printf("Error: NULL pointer during viewer clearing.");
        break;
    case NULL_READER_POINTER:
        printf("Error: NULL reader_t pointer.");
        break;
    }
}
