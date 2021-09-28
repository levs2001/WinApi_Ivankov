#include "exceptions.h"

void Exception(eException exceptionType) {
    switch(exceptionType) {
    case FILE_NOT_OPEN:
        printf("Error: File for reading wasn't open.");
        break;
    case NULL_BUFF_POINTER:
        printf("Error: NULL pointer during buffer clearing.");
    }
}
