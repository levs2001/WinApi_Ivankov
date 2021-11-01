#ifndef HEADER_FILE_READER
#define HEADER_FILE_READER

#include<stdio.h>

#define TEST_FILENAME "D:\\MyProgramms\\CodeBlocks\\WinApi_Ivankov\\test_for_lab.txt"

typedef struct {
    char* buffer;
    size_t bufferSize;
    size_t* lnEnds;
    size_t lnEndsSize;
    size_t maxStrLen;
}reader_t;


//FILE* OpenFileMy(char* filename);
//void CloseFile(FILE* filePointer);
//size_t GetSizeFile(FILE* filePointer);
void WriteFileInReader(reader_t* readerP, char* filename);
//void ClearBuffer(char* buffer);
void ClearReader(reader_t* readerP);
void EmptyReader(reader_t* readerP);
//size_t GetMaxStrLen(reader_t* readerP);
#endif

