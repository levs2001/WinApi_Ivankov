#ifndef HEADER_FILE_READER
#define HEADER_FILE_READER

#include<stdio.h>

#define FILE_DEFAULT_READING_PORTION 20
#define TEST_FILENAME "test_for_lab.txt"

FILE* OpenFile(char* filename);
void GetPortionFromFile(char* portionContainer, size_t portionSize, FILE* filePointer);
void CloseFile(FILE* filePointer);


#endif

