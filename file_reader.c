#include "file_reader.h"
#include "exceptions.h"
#include "memory.h"
#include <stdlib.h>

#define LINE_END "\n"
#define REALLOC_NUM 10

static FILE* OpenFileMy(char* filename);
static size_t GetSizeFile(FILE* filePointer);
static void CloseFile(FILE* filePointer);
static size_t* ExpandLnEnds(size_t* lnEnds, size_t newSize);
static void InitLnEnds(reader_t* readerP);
static size_t GetMaxStrLen(reader_t* readerP);
static void ClearLnEnds(size_t* lnEnds);
static void ClearBuffer(char* buffer);

void WriteFileInReader(reader_t* readerP, char* filename) {
    FILE* filePointer = OpenFileMy(filename);
    size_t bufferSize = GetSizeFile(filePointer);
    char* buffer = (char*)getMem(bufferSize * sizeof(char), "buffer");

    //Борьба с каретками
    bufferSize = fread(buffer, sizeof(char), bufferSize, filePointer);
    CloseFile(filePointer);

    readerP->bufferSize = bufferSize;
    readerP->buffer = buffer;
    InitLnEnds(readerP);
    readerP->maxStrLen = GetMaxStrLen(readerP);
}

void EmptyReader(reader_t* readerP) {
    if(readerP==NULL)
        Exception(NULL_READER_POINTER);
    if(readerP->buffer != NULL) {
        ClearBuffer(readerP->buffer);
    }
    if(readerP->lnEnds != NULL) {
        ClearLnEnds(readerP->lnEnds);
    }

    readerP->buffer = NULL;
    readerP->lnEnds = NULL;
    readerP->bufferSize = 0;
    readerP->lnEndsSize = 0;
    readerP->maxStrLen = 0;
}

void ClearReader(reader_t* readerP) {
    EmptyReader(readerP);
    freeMem(readerP, "reader");
}

static FILE* OpenFileMy(char* filename) {
    FILE* filePointer = fopen(filename, "r");

    if(filePointer == NULL) {
        Exception(FILE_NOT_OPEN);
        return NULL;
    }

    return filePointer;
}

static size_t GetSizeFile(FILE* filePointer) {
    rewind(filePointer);
    fseek(filePointer, 0L, SEEK_END);
    size_t fSize= ftell(filePointer);
    rewind(filePointer);
    return fSize;
}

static void CloseFile(FILE* filePointer) {
    fclose(filePointer);
}

static size_t* ExpandLnEnds(size_t* lnEnds, size_t newSize) {
    size_t* newLnEnds = (size_t*)realloc(lnEnds, newSize);
    if(newLnEnds == NULL) {
        Exception(REALLOC_REFUSE_LN_ENDS);
    }
    return newLnEnds;
}

static void InitLnEnds(reader_t* readerP) {
    size_t lnEndsSize = 0;
    size_t lnEndsGivenSize = REALLOC_NUM;
    size_t* lnEnds = (size_t*)getMem(sizeof(size_t) * lnEndsGivenSize, "lnEnds");

    for(size_t i = 0; i < readerP->bufferSize; i++) {
        if(readerP->buffer[i] == '\n') {
            if(lnEndsSize >= lnEndsGivenSize - 1) {
                lnEndsGivenSize += REALLOC_NUM;
                lnEnds = ExpandLnEnds(lnEnds, lnEndsGivenSize*sizeof(size_t));
            }
//
            lnEnds[lnEndsSize] = i;
            lnEndsSize++;
        }
    }

    readerP->lnEndsSize = lnEndsSize;
    readerP->lnEnds = lnEnds;
}

static size_t GetMaxStrLen(reader_t* readerP) {
    // TODO: I should see case when no "\n"
    if(readerP->lnEndsSize > 0) {
        size_t maxStrLen = readerP->lnEnds[0];

        for(size_t i = 0; i < readerP->lnEndsSize - 1; i++) {
            if(readerP->lnEnds[i + 1] - readerP->lnEnds[i] > maxStrLen) {
                maxStrLen = readerP->lnEnds[i + 1] - readerP->lnEnds[i];
            }
        }

        // Checking last str:
        if((long)(readerP->bufferSize - readerP->lnEnds[readerP->lnEndsSize - 1] - readerP->lnEndsSize) > (long)maxStrLen) {
            maxStrLen = readerP->bufferSize - readerP->lnEnds[readerP->lnEndsSize - 1] - readerP->lnEndsSize;
        }
        return maxStrLen;
    }

    return readerP->bufferSize;
}

static void ClearLnEnds(size_t* lnEnds) {
    if(lnEnds!=NULL)
        freeMem(lnEnds, "lnEnds");
    else
        Exception(NULL_LN_ENDS_POINTER);
}

static void ClearBuffer(char* buffer) {
    if(buffer!=NULL)
        freeMem(buffer, "buffer");
    else
        Exception(NULL_BUFF_POINTER);
}
