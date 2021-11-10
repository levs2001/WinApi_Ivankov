#ifndef HEADER_TEXT_COMPS
#define HEADER_TEXT_COMPS
#include <windows.h>

// ��������� � ����������� � ������, ������� ������������ �� viewer
typedef struct {
    // ������ ������
    size_t height;
    // ������ ������
    size_t width;
}myFont_t;

/*
    �������� ������ � �������������� ��������� � ����������� � ���� ������
    return:
        ��������� �� ��������� � ����������� � ���� ������
*/
myFont_t* CreateDefaultFont();

/*
    ����������� ������ ���������� ��� ��������� � ����������� � ������
    params:
        myFontP - ��������� �� ��������� � ����������� � ������
*/
void ClearFont(myFont_t* myFontP);

/*
    ������� ���� ������������ ����� � ����������� �� myFont.
    ��� ����� ������� ���������� ����������� ����� � �������� ��� ��� ����
    params:
        hdc - ���������� ����
        myFont - ��������� �� ��������� � ����������� ������
*/
void SelectFont(HDC hdc, myFont_t* myFont);
#endif
