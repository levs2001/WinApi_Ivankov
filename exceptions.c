#include "exceptions.h"

void Exception(eException exceptionType) {
    switch(exceptionType) {
    case FILE_NOT_OPEN:
        logMsg("Error: File for reading wasn't open.\n");
        break;
    case NULL_BUFF_POINTER:
        logMsg("Error: NULL pointer during buffer clearing.\n");
        break;
    case NULL_VIEWER_POINTER:
        logMsg("Error: NULL pointer during viewer clearing.\n");
        break;
    case NULL_READER_POINTER:
        logMsg("Error: NULL reader_t pointer.\n");
        break;
    case NULL_WIN_PARAMS_POINTER:
        logMsg("Error: NULL winParams_t pointer.\n");
        break;
    case NULL_FONT_POINTER:
        logMsg("Error: NULL font pointer.\n");
        break;
    }
}

void logMsg(char* msg) {
    printf(msg);
}
