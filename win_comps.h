#ifndef HEADER_WIN_COMPS
#define HEADER_WIN_COMPS
#include<stddef.h>
#include<stdbool.h>
#include<windows.h>
#include"text_comps.h"

#define MIN_X 0
// —труктура, хран€ща€ параметры окна
typedef struct {
    // Ўирина окна
    size_t width;
    // ¬ысота окна
    size_t height;
    //  оличество символов, которые могут поместитьс€ в одной строке, не выход€ за пределы окна
    size_t widthInSyms;
    //  оличество строк, которые могут поместитьс€, не выход€ за пределы окна
    size_t heightInSyms;
    // ѕозици€ вертикального скроллинга
    size_t vScrollPos;
    // ѕозици€ горизонтального сроллинга
    size_t hScrollPos;
    // ћаксимально возможна€ позици€ вертикального скроллинга, обычно равна количеству строк,
    // которые можно просмотреть в viewer
    size_t vScrollMax;
    // ћаксимально возможна€ позици€ горизонтального скроллинга, обычно равна длине максимальной строки
    size_t hScrollMax;
}winParams_t;

/*
    »нициализирует значени€ структуры параметров окна, выдел€ет под нее пам€ть
    params:
        [in] hwnd - указатель на окно, где мы отображаем viewer
        [in] myFontP - указатель на структуру с параметрами используемого шрифта
    return:
        указатель на мою структуру с параметрами окна
*/
winParams_t* InitWinParams(HWND hwnd, myFont_t* myFontP);

/*
    ћен€ет параметры окна в зависимости от размеров окна, в которое отображаетс€ окно
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
        [in] hwnd - указатель на окно, где мы отображаем viewer
        [in] myFontP - указатель на структуру с параметрами используемого шрифта
*/
void ResizeWinParams(winParams_t* winParamsP, HWND hwnd, myFont_t* myFontP);

/*
    ќсвобождает пам€ть, выделенную на структуру с параметрами окна
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
*/
void ClearWinParams(winParams_t* winParamsP);

/*
    —оздает модальный диалог, в котором пользователь может выбрать файл
    «аписывает им€ файла в filenameP
    params:
        [in] hwnd - указатель на окно владельца
        [out] filenameP - указатель на строку, куда должно записатьс€ им€ файла
    return:
        true - в случае успеха
        false - в случае неудачи (например, если выбрали не текстовый файл)
*/
bool OpenFileDlg(HWND hwnd, LPSTR filenameP);

#endif
