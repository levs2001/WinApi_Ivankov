#ifndef HEADER_MEMORY
#define HEADER_MEMORY
#include<stddef.h>

/*
    Выделяет память, записывает о том, что память выделена и для чего в лог
    params:
        [in] memSize - сколько нужно выделить памяти
        [in] reason - указатель на строку, где записано для чего память
    return:
        указатель на блок выделенной памяти
*/
void* getMem(size_t memSize, char* reason);

/*
    Освобождает память, записывает в лог, что память особождена и для чего память использовалась
    params:
        [in|out] pointer - указатель на блок освобождаемой памяти
        [in] reason - указатель на строку, где записано для чего нужна была память
*/
void freeMem(void* pointer, char* reason);

#endif

