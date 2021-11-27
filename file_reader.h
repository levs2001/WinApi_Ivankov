#ifndef HEADER_FILE_READER
#define HEADER_FILE_READER

#include<stdio.h>

#define LINE_END '\n'

// Структура с информацией о тексте, находящейся во viewer
typedef struct {
    // Указатель на массив с содержимым текста
    char* buffer;
    // Размер массива с содержимым текста
    size_t bufferSize;
    // Указатель на массив с индексами концов строк в тексте
    size_t* lnEnds;
    // Размер массива с индексами концов строк (количество переносов строк в тексте)
    size_t lnEndsSize;
    // Размер самой больщой строке в тексте
    size_t maxStrLen;
}reader_t;

/*
    Заполняет структуру reader_t содержимым файла, инициализируя ее
    Выделяется память под buffer и lnEnds
    params:
        [out] readerP - указатель на структуру, куда запишется содержимое файла
        [in] filename - имя файла, который надо записать
*/
void WriteFileInReader(reader_t* readerP, char* filename);

/*
    Освобождает память отданную структуре
    params:
        [out] readerP - указатель на структуру, куда записано содержимое файла
*/
void ClearReader(reader_t* readerP);

/*
    Освобождает память отданную под массивы(buffer и lnEnds) в reader и заполняет его значения нулями
    params:
        [out] readerP - указатель на структуру, куда записано содержимое файла
*/
void EmptyReader(reader_t* readerP);

/*
    Заполняет параметры ридера нулями и NULL
    params:
        [out] readerP - указатель на структуру, куда записано содержимое файла
*/
void NullifyReader(reader_t* readerP);
#endif

