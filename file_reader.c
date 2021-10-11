#include "file_reader.h"
#include "exceptions.h"
#include "memory.h"
#include <stdlib.h>

FILE* OpenFileMy(char* filename) {
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
    FILE* filePointer = OpenFileMy(filename);
    size_t bufferSize = GetSizeFile(filePointer);
    char* buffer = (char*)getMem(bufferSize * sizeof(char), "buffer");

    fread(buffer, sizeof(char), bufferSize, filePointer);
    // TODO: go through buffer and get \n array and size of it
    // Expand array on REALLOC_SIZE
    CloseFile(filePointer);

    readerP->bufferSize = bufferSize;
    readerP->buffer = buffer;
}

void ClearReader(reader_t* readerP) {
    if(readerP==NULL)
        Exception(NULL_READER_POINTER);

    ClearBuffer(readerP->buffer);
    // TODO: Free array of \n here
    freeMem(readerP, "reader");
}

void ClearBuffer(char* buffer) {
    if(buffer!=NULL)
        freeMem(buffer, "buffer");
    else
        Exception(NULL_BUFF_POINTER);
}
