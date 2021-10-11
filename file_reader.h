#ifndef HEADER_FILE_READER
#define HEADER_FILE_READER

#include<stdio.h>

#define TEST_FILENAME "test_for_lab.txt"

typedef struct {
    char* buffer;
    size_t bufferSize;
    // TODO: add array for \n and size of this array
}reader_t;


FILE* OpenFile(char* filename);
void CloseFile(FILE* filePointer);
size_t GetSizeFile(FILE* filePointer);
void WriteFileInReader(reader_t* readerP, char* filename);
void ClearBuffer(char* buffer);
void ClearReader(reader_t* readerP);
void WriteFileInReader(reader_t* readerP, char* filename);

#endif

