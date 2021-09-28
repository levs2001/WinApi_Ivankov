#include "file_reader.h"
#include "exceptions.h"

#define FILE_DEFAULT_READING_PORTION 20
#define TEST_FILENAME "test_for_lab.txt"

FILE* OpenFile(char* filename) {
    FILE* filePointer = fopen(filename, "r");

    if(filePointer == NULL) {
        Exception(FILE_NOT_OPEN);
        return NULL;
    }

    return filePointer;
}

void GetPortionFromFile(char* portionContainer, size_t portionSize, FILE* filePointer) {
    fgets(portionContainer, portionSize, filePointer);
}

void CloseFile(FILE* filePointer) {
        fclose(filePointer);
}
