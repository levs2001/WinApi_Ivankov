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
//    LOGFONT lf; //������ ��������� LOGFONT
//    lf.lfCharSet=DEFAULT_CHARSET; //�������� �� ���������
//    lf.lfPitchAndFamily=DEFAULT_PITCH; //�������� �� ���������
//    strcpy(lf.lfFaceName,"Times New Roman"); //�������� � ������ �������� ������
//    lf.lfHeight=DEFAULT_MYFONT_HEIGHT; //������
//    lf.lfWidth=DEFAULT_MYFONT_HEIGHT; //������
//    lf.lfWeight=DEFAULT_MYFONT_WEIGHT; //�������
//    lf.lfEscapement=DEFAULT_MYFONT_ESCAPEMENT; //����� ��� ��������
//
//    HFONT hFont = CreateFontIndirect(&lf); //C������ �����
//
//    return hFont;
//}
