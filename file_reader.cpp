#include "file_reader.h"
#include "exceptions.h"
#include <stdlib.h>

FILE* OpenFile(char* filename) {
    FILE* filePointer = fopen(filename, "r");

    if(filePointer == NULL) {
        Exception(FILE_NOT_OPEN);
        return NULL;
    }

    return filePointer;
}

//void GetPortionFromFile(char* portionContainer, size_t portionSize, FILE* filePointer) {
//    fgets(portionContainer, portionSize, filePointer);
//}

void CloseFile(FILE* filePointer) {
    fclose(filePointer);
}

//bufferSizeReturned - size of maked buffer, it depends on file size
char* GetBufferFromFile(char* filename, size_t* bufferSizePointer) {
    FILE* filePointer = OpenFile(filename);
    size_t bufferSize = GetSizeFile(filePointer);
    char* buffer = (char*)malloc(bufferSize * sizeof(char));

    fread(buffer, sizeof(char), bufferSize, filePointer);
    CloseFile(filePointer);

    *bufferSizePointer = bufferSize;
    return buffer;
}

size_t GetSizeFile(FILE* filePointer) {
    rewind(filePointer);
    fseek(filePointer, 0L, SEEK_END);
    size_t fSize= ftell(filePointer);
    rewind(filePointer);
    return fSize;
}

void ClearBuffer(char* buffer) {
    if(buffer!=NULL)
        free(buffer);
    else
        Exception(NULL_BUFF_POINTER);
}
