#ifndef HEADER_TEXT_COMPS
#define HEADER_TEXT_COMPS

typedef struct {
    size_t height;
    size_t width;
    HFONT hFont;
}myFont_t;

myFont_t* CreateDefaultFont();
//HFONT CreateDefaultLogicalFont();

#endif
