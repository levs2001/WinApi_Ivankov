#ifndef HEADER_SCROLLING
#define HEADER_SCROLLING

#include"viewer_comps.h"
#include"win_comps.h"
#include<stdbool.h>

#define HORZ_SCROLL_DEFAULT false

// Максимальный диапазон системного скроллига
#define SCROLL_RANGE_MAX 65535

/*
    Меняет параметры вертикального скроллинга vScrollMax и vScrollPos,
    под новый размер окна.
    params:
        [in|out] viewerP - указатель на структуру вьювера
        [in] prLinesCount - количество строк, которое можно увидеть в viewer
*/
void ResizeVscrollParams(viewer_t* viewerP, size_t prLinesCount);

/*
    Меняет параметры горизонтального скроллинга hScrollMax и hScrollPos,
    под новый размер окна (при условии, что горизонтальный скроллинг включен)
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
        [in] isHorzScroll - bool включен ли горизонтальный скроллинг (Wrap off)
*/
void ResizeHscrollParams(winParams_t* winParamsP, size_t maxStrLen, bool isHorzScroll);

/*
    Меняет позицию вертикального скроллинга (она сдвигается на 1 строку текста вверх),
    нужна для случая, когда пользователь нажал стрелку вверх на клавиатуре или скролл баре
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
*/
void ScrollVertLineUpViewer(winParams_t* winParamsP);

/*
    Меняет позицию вертикального скроллинга (она сдвигается на 1 строку текста вниз),
    нужна для случая, когда пользователь нажал стрелку вниз на клавиатуре или скролл баре
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
*/
void ScrollVertLineDownViewer(winParams_t* winParamsP);

/*
    Меняет позицию вертикального скроллинга (она сдвигается вверх на колиичество строк текста, размещенных в окне),
    нужна для случая, когда пользователь нажал на скролл бар выше ползунка или pageUp на клавиатуре
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
*/
void ScrollVertPageUpViewer(winParams_t* winParamsP);

/*
    Меняет позицию вертикального скроллинга (она сдвигается вниз на колиичество строк текста, размещенных в окне),
    нужна для случая, когда пользователь нажал на скролл бар ниже ползунка или pageDown на клавиатуре
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
*/
void ScrollVertPageDownViewer(winParams_t* winParamsP);

/*
    Меняет позицию горизонтального скроллинга (она сдвигается на 1 символ текста влево),
    нужна для случая, когда пользователь нажал стрелку влево на клавиатуре или скролл баре.
    Работает при условии, что включен горизонтальный скроллинг
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
        [in] isHorzScroll - bool включен ли горизонтальный скроллинг (Wrap off)
*/
void ScrollHorzLineUpViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    Меняет позицию горизонтального скроллинга (она сдвигается на 1 символ текста вправо),
    нужна для случая, когда пользователь нажал стрелку вправо на клавиатуре или скролл баре.
    Работает при условии, что включен горизонтальный скроллинг
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
        [in] isHorzScroll - bool включен ли горизонтальный скроллинг (Wrap off)
*/
void ScrollHorzLineDownViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    Меняет позицию горизонтального скроллинга (она сдвигается влево на количество символов в строке, размещенной в окне),
    нужна для случая, когда пользователь нажал слева от ползунка на скролл баре.
    Работает при условии, что включен горизонтальный скроллинг
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
        [in] isHorzScroll - bool включен ли горизонтальный скроллинг (Wrap off)
*/
void ScrollHorzPageUpViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    Меняет позицию горизонтального скроллинга (она сдвигается вправо на колиичество символов в строке, размещенной в окне),
    нужна для случая, когда пользователь нажал справа от ползунка на скролл баре.
    Работает при условии, что включен горизонтальный скроллинг
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
        [in] isHorzScroll - bool включен ли горизонтальный скроллинг (Wrap off)
*/
void ScrollHorzPageDownViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    Отображает системную позицию скроллинга на мою (они могут быть не равны из за ограничения диапазона на системном скроллинге)
    params:
        [in] myScrollMax - максимально возможная позиция скроллинга
        [in] sysScrPos - системная позиция скроллинга
    return:
        моя позиция скроллинга
*/
size_t GetScrollPosMyFromSystem(size_t myScrollMax, int sysScrPos);

/*
    Отображает мою позицию скроллинга на системную (они могут быть не равны из за ограничения диапазона на системном скроллинге)
    params:
        [in] myScrollMax - максимально возможная позиция скроллинга
        [in] myScrPos - моя позиция скроллинга
    return:
        системная позиция скроллинга
*/
int GetScrollPosSystemFromMy(size_t myScrollMax, size_t myScrPos);

/*
    Меняет значение параметра отвечающего за вертикальный скроллинг, если это возможно
    params:
        [in|out] winParamsP - указатель на мою структуру с параметрами окна
        [in] delta - величина на которую надо поменять позицию вертикального скроллинга
*/
void ChangeVScrollPos(winParams_t* winParamsP, long delta);
#endif
