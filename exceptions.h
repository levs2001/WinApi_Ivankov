#ifndef HEADER_EXCEPTIONS
#define HEADER_EXCEPTIONS

#include <stdio.h>

// Виды исключений в ходе работы программы
typedef enum {
    // Не удалось открыть файл
    FILE_NOT_OPEN,
    // При освобождении памяти выделенной под буффер выяснилось, что там NULL
    NULL_BUFF_POINTER,
    // При освобождении памяти выделенной под reader выяснилось, что там NULL
    NULL_READER_POINTER,
    // При освобождении памяти выделенной под viewer выяснилось, что там NULL
    NULL_VIEWER_POINTER,
    // При освобождении памяти выделенной под структуру параметров окна выяснилось, что там NULL
    NULL_WIN_PARAMS_POINTER,
    // При освобождении памяти выделенной под параметры шрифта выяснилось, что там NULL
    NULL_FONT_POINTER,
    // При освобождении памяти выделенной под массив концов строк выяснилось, что там NULL
    NULL_LN_ENDS_POINTER,
    // Не удалось расширить массив концов строк
    REALLOC_REFUSE_LN_ENDS
} eException;

/*
    Записывает информацию об исключении в лог
    params:
        [in] exceptionType - вид исключения
*/
void Exception(eException exceptionType);

/*
    Записывает сообщение в лог (консоль)
    params:
        [in] msg - указатель на строку с сообщением
*/
void logMsg(char* msg);

#endif
