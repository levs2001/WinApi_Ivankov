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

size_t GetSizeFile(FILE* filePointer) {
    rewind(filePointer);
    fseek(filePointer, 0L, SEEK_END);
    size_t fSize= ftell(filePointer);
    rewind(filePointer);
    return fSize;
}

void CloseFile(FILE* filePointer) {
    fclose(filePointer);
}

void WriteFileInReader(reader_t* readerP, char* filename) {
    FILE* filePointer = OpenFile(filename);
    size_t bufferSize = GetSizeFile(filePointer);
    char* buffer = (char*)malloc(bufferSize * sizeof(char));

    fread(buffer, sizeof(char), bufferSize, filePointer);
    CloseFile(filePointer);

    readerP->bufferSize = bufferSize;
    readerP->buffer = buffer;
}

void ClearReader(reader_t* readerP) {
    if(readerP==NULL)
        Exception(NULL_READER_POINTER);

    ClearBuffer(readerP->buffer);
    free(readerP);
}

void ClearBuffer(char* buffer) {
    if(buffer!=NULL)
        free(buffer);
    else
        Exception(NULL_BUFF_POINTER);
}
