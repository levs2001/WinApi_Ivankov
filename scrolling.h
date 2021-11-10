#ifndef HEADER_SCROLLING
#define HEADER_SCROLLING

#include"win_comps.h"
#include<stdbool.h>

#define HORZ_SCROLL_DEFAULT false
#define SCROLL_RANGE_MAX 65535

void ResizeVscrollParams(winParams_t* winParamsP, size_t prLinesCount);
void ResizeHscrollParams(winParams_t* winParamsP, size_t maxStrLen, bool isHorzScroll);

void ScrollVertLineUpViewer(winParams_t* winParamsP);
void ScrollVertLineDownViewer(winParams_t* winParamsP);
void ScrollVertPageUpViewer(winParams_t* winParamsP);
void ScrollVertPageDownViewer(winParams_t* winParamsP);

void ScrollHorzLineUpViewer(winParams_t* winParamsP, bool isHorzScroll);
void ScrollHorzLineDownViewer(winParams_t* winParamsP, bool isHorzScroll);
void ScrollHorzPageUpViewer(winParams_t* winParamsP, bool isHorzScroll);
void ScrollHorzPageDownViewer(winParams_t* winParamsP, bool isHorzScroll);

size_t GetScrollPosMyFromSystem(size_t myScrollMax, int sysScrPos);
int GetScrollPosSystemFromMy(size_t myScrollMax, size_t myScrPos);
#endif
