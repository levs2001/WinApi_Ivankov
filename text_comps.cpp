#include <windows.h>
#include "text_comps.h"

#define DEFAULT_MYFONT_HEIGHT 100
#define DEFAULT_MYFONT_WIDTH 10

#define DEFAULT_MYFONT_WEIGHT 40
#define DEFAULT_MYFONT_ESCAPEMENT 0


myFont_t* CreateDefaultFont() {
    myFont_t* myFontP = (myFont_t*)malloc(sizeof(myFont_t));
    myFontP->height = DEFAULT_MYFONT_HEIGHT;
    myFontP->width = DEFAULT_MYFONT_WIDTH;
    myFontP->hFont = CreateFont(myFontP->height, myFontP->width, 0, 0, 0,
                                FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                0, 0, 0, FIXED_PITCH, "My font");
    return myFontP;
}

//HFONT CreateDefaultLogicalFont() {
//    LOGFONT lf; //создаЄм экземпл€р LOGFONT
//    lf.lfCharSet=DEFAULT_CHARSET; //значение по умолчанию
//    lf.lfPitchAndFamily=DEFAULT_PITCH; //значени€ по умолчанию
//    strcpy(lf.lfFaceName,"Times New Roman"); //копируем в строку название шрифта
//    lf.lfHeight=DEFAULT_MYFONT_HEIGHT; //высота
//    lf.lfWidth=DEFAULT_MYFONT_HEIGHT; //ширина
//    lf.lfWeight=DEFAULT_MYFONT_WEIGHT; //толщина
//    lf.lfEscapement=DEFAULT_MYFONT_ESCAPEMENT; //шрифт без поворота
//
//    HFONT hFont = CreateFontIndirect(&lf); //Cоздали шрифт
//
//    return hFont;
//}
