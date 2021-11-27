/*
    Файл с функциями отвечающими зза работу с файлом, получении метаинформации о нем.
    Комментарии к не static функциям можно посмотреть в заголовочном файле.
    Комментарии к static функциям можно посмотреть в объявлениях.
*/

#include "file_reader.h"
#include "exceptions.h"
#include "memory.h"
#include <stdlib.h>


// На сколько расширяем массив концов строк
#define REALLOC_NUM 10

/*
    Открывает файл на чтение
    params:
        [in] filename - имя файла
    return:
        Указатель на поток открытого файла
*/
static FILE* OpenFileMy(char* filename);

/*
    Вычисляет количество символов в файле
    params:
        [in] filePointer - указатель на поток открытого файла
    return:
        Количество символов в файле
*/
static size_t GetSizeFile(FILE* filePointer);

/*
    Закрывает открытый файл
    params:
        [in] filePointer - указатель на поток открытого файла
*/
static void CloseFile(FILE* filePointer);

/*
    Записывает в массив lnEnds индексы символов концов строк в тексте
    params:
        [in|out] readerP - указатель на структуру с содержимым файла
*/
static void InitLnEnds(reader_t* readerP);

/*
    Расширяет массив lnEnds
    params:
        [in] lnEnds - указатель на массив с индексами символов концов строк в тексте
        [in] newSize - новый размер массива
    return:
        Указатель на увеличенный массив

*/
static size_t* ExpandLnEnds(size_t* lnEnds, size_t newSize);

/*
    Вычисляет длину самой большой строки, записанной в ридер
    params:
        [in] readerP - указатель на структуру с содержимым файла
    return:
        Длина самой большой строки
*/
static size_t GetMaxStrLen(reader_t* readerP);

/*
    Освобождает память, выделенную на массив концов строк
    params:
        [in|out] lnEnds - указатель на массив концов строк
*/
static void ClearLnEnds(size_t* lnEnds);

/*
    Освобождает память, выделенную под буффер (текст из файла)
    params:
        [in|out] buffer - указатель на буффер (текст)
*/
static void ClearBuffer(char* buffer);


void WriteFileInReader(reader_t* readerP, char* filename) {
    FILE* filePointer = OpenFileMy(filename);
    size_t bufferSize = GetSizeFile(filePointer);
    char* buffer = (char*)getMem(bufferSize * sizeof(char), "buffer");

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

    NullifyReader(readerP);
}

void NullifyReader(reader_t* readerP) {
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
        if(readerP->buffer[i] == LINE_END) {
            if(lnEndsSize >= lnEndsGivenSize - 1) {
                lnEndsGivenSize += REALLOC_NUM;
                lnEnds = ExpandLnEnds(lnEnds, lnEndsGivenSize*sizeof(size_t));
            }

            lnEnds[lnEndsSize] = i;
            lnEndsSize++;
        }
    }

    readerP->lnEndsSize = lnEndsSize;
    readerP->lnEnds = lnEnds;
}

static size_t GetMaxStrLen(reader_t* readerP) {
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
