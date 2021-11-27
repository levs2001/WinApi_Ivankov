#ifndef HEADER_VIEWER_COMPS
#define HEADER_VIEWER_COMPS
#include<stddef.h>
#include<stdbool.h>
#include"file_reader.h"
#include"text_comps.h"
#include"win_comps.h"

// Главная структура в проекте, в ней вся информация о viewer
typedef struct {
    // Указатель на reader в котором содержатся все данные о выводимом тексте
    reader_t* readerP;
    // Указатель на используемы шрифт и его параметры
    myFont_t* fontP;
    // Указатель на параметры окна (размеры, параметры скроллинга)
    winParams_t* winParamsP;
    // Показывает включен ли горизнтальный скроллинг (Wrap off)
    bool isHorzScroll;
    /// Counting during resize and vScrolling, need to know what part of buffer should be printed
    //Смещение первого и последнего выводимого индекса относительно начала буффера
    size_t firstPrSymI;
    size_t lastPrSymI;
}viewer_t;

/*
    Инициализирует наш viewer:
        Выделяет память для него
        Инициализует всё содержимое
        (в том числе записывает во viewer дескриптор окна)
    params:
        [out] viewerP - указатель на viewer
        [in] hwnd - указатель на окно, где мы отображаем viewer
*/
void InitViewer(viewer_t* viewerP, HWND hwnd);

/*
    Освобождает всю память выделенную под viewer
    Вызывается перед закрытием окна
    params:
        [out] viewerP - указатель на viewer
*/
void ClearViewer(viewer_t* viewerP);

/*
    Открывает файл и записывает его параметры во viewer
    params:
        [out] viewerP - указатель на viewer
        [in] filename - имя файла
*/
void SendFileInViewer(viewer_t* viewerP, char* filename);

/*
    Отрисовывает viewer в окно
    params:
        [in] viewerP - указатель на viewer
        [in] hdc - дескриптор окна для отрисовки
*/
void ShowViewer(viewer_t* viewerP, HDC hdc);

/*
    Меняет все параметры viewer с учетом нового размера окна
    params:
        [out] viewerP - указатель на viewer
        [in] hwnd - указатель на окно, где мы отображаем viewer
*/
void ResizeViewer(viewer_t* viewerP, HWND hwnd);

/*
    Обрабатывает кручение колесика мыши пользователем
    params:
        [in|out] viewerP - указатель на viewer
        [in] hwnd - указатель на окно, где мы отображаем viewer
        [in] wParam - параметр использумый для определения на сколько крутанули колесико
*/
void ProcessMouseWheel(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    Обрабатывает вертикальный скроллинг
    params:
        [in|out] viewerP - указатель на viewer
        [in] hwnd - указатель на окно, где мы отображаем viewer
        [in] wParam - параметр использумый для определения:
            команды скроллинга(нажата стрелочка, подвинут ползунок и тд)
            текущей позиции на scrollBar
*/
void ProcessVscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    Обрабатывает горизонтальный скроллинг
    params:
        [in|out] viewerP - указатель на viewer
        [in] hwnd - указатель на окно, где мы отображаем viewer
        [in] wParam - параметр использумый для определения:
            команды скроллинга(нажата стрелочка, подвинут ползунок и тд)
            текущей позиции на scrollBar
*/
void ProcessHscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    Обрабатывает нажатие клавиш на клавиатуре. Клавиши используются для скроллинга
    params:
        [in|out] viewerP - указатель на viewer
        [in] hwnd - указатель на окно, где мы отображаем viewer
        [in] wParam - параметр использумый для определения виртуальной клавиши
*/
void ProcessKeyDownViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    Включает перенос строк во viewer(если выходит за пределы окна)
    и отключает горизонтальный скроллинг
    params:
        [out] viewerP - указатель на viewer
*/
void WrapOnViewer(viewer_t* viewerP);

/*
    Отключает перенос строк во viewer и включает горизонтальный скроллинг
    params:
        [out] viewerP - указатель на viewer
*/
void WrapOffViewer(viewer_t* viewerP);

/*
    Очищает viewer от всей информации о содержимом файла
    (в том числе и освобождает память),
    Нуллифицирует параметры, завязанные на этой информации
    params:
        [out] viewerP - указатель на viewer
*/
void CloseFileInViewer(viewer_t* viewerP);
#endif
