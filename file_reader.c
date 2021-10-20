#include "file_reader.h"
#include "exceptions.h"
#include "memory.h"
#include <stdlib.h>

#define LINE_END "\n"
#define REALLOC_NUM 10

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
    CloseFile(filePointer);

    readerP->bufferSize = bufferSize;
    readerP->buffer = buffer;

    InitLnEnds(readerP);
    readerP->maxStrLen = GetMaxStrLen(readerP);
}

size_t* ExpandLnEnds(size_t* lnEnds, size_t newSize) {
    size_t* newLnEnds = (size_t*)realloc(lnEnds, newSize);
    if(newLnEnds == NULL) {
        Exception(REALLOC_REFUSE_LN_ENDS);
    }
    return newLnEnds;
}

size_t GetMaxStrLen(reader_t* readerP) {
    // TODO: I should see case when no "\n"
    size_t maxStrLen = readerP->lnEnds[0];

    for(size_t i = 0; i < readerP->lnEndsSize - 1; i++) {
        if(readerP->lnEnds[i + 1] - readerP->lnEnds[i] > maxStrLen) {
            maxStrLen = readerP->lnEnds[i + 1] - readerP->lnEnds[i];
        }
    }

    // Checking last str:
    if(readerP->bufferSize - readerP->lnEnds[readerP->lnEndsSize - 1] - readerP->lnEndsSize > maxStrLen) {
        maxStrLen = readerP->bufferSize - readerP->lnEnds[readerP->lnEndsSize - 1] - readerP->lnEndsSize;
    }

    return maxStrLen;
}

void InitLnEnds(reader_t* readerP) {
    size_t lnEndsSize = 0;
    size_t realMemSize = sizeof(size_t*) * REALLOC_NUM;
    size_t* lnEnds = (size_t*)getMem(realMemSize, "lnEnds");

    for(size_t i = 0; i < readerP->bufferSize; i++) {
        if(readerP->buffer[i] == '\n') {
            if(lnEndsSize >= realMemSize - 1) {
                realMemSize += sizeof(size_t*) * REALLOC_NUM;
                lnEnds = ExpandLnEnds(lnEnds, lnEndsSize);
            }

            lnEnds[lnEndsSize] = i;
            lnEndsSize++;
        }
    }

    readerP->lnEndsSize = lnEndsSize;
    readerP->lnEnds = lnEnds;
}

void ClearLnEnds(size_t* lnEnds) {
    if(lnEnds!=NULL)
        freeMem(lnEnds, "lnEnds");
    else
        Exception(NULL_LN_ENDS_POINTER);
}

void ClearReader(reader_t* readerP) {
    if(readerP==NULL)
        Exception(NULL_READER_POINTER);

    ClearBuffer(readerP->buffer);
    ClearLnEnds(readerP->lnEnds);
    freeMem(readerP, "reader");
}

void ClearBuffer(char* buffer) {
    if(buffer!=NULL)
        freeMem(buffer, "buffer");
    else
        Exception(NULL_BUFF_POINTER);
}
