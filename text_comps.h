#ifndef HEADER_TEXT_COMPS
#define HEADER_TEXT_COMPS
#include <windows.h>
typedef struct {
    size_t height;
    size_t width;
}myFont_t;

myFont_t* CreateDefaultFont();
void ClearFont(myFont_t* myFontP);
void SelectFont(HDC hdc, myFont_t* myFont);
#endif
