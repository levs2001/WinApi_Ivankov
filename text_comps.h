#ifndef HEADER_TEXT_COMPS
#define HEADER_TEXT_COMPS
#include <windows.h>

// Структура с информацией о шрифте, который используется во viewer
typedef struct {
    // Высота шрифта
    size_t height;
    // Ширина шрифта
    size_t width;
}myFont_t;

/*
    Выделяет память и инициализирует структуру с информацией о моем шрифте
    return:
        Указатель на структуру с информацией о моем шрифте
*/
myFont_t* CreateDefaultFont();

/*
    Освобождает память выделенную под структуру с информацией о шрифте
    params:
        [in] myFontP - указатель на структуру с информацией о шрифте
*/
void ClearFont(myFont_t* myFontP);

/*
    Говорит окну использовать шрифт с параметрами из myFont.
    Для этого создает логический моношримный шрифт и выбирает его для окна
    params:
        [in] hdc - дескриптор окна
        [in] myFont - указатель на структуру с параметрами шрифта
*/
void SelectFont(HDC hdc, myFont_t* myFont);
#endif
