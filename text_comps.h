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
        [in] myFontP - ��������� �� ��������� � ����������� � ������
*/
void ClearFont(myFont_t* myFontP);

/*
    ������� ���� ������������ ����� � ����������� �� myFont.
    ��� ����� ������� ���������� ����������� ����� � �������� ��� ��� ����
    params:
        [in] hdc - ���������� ����
        [in] myFont - ��������� �� ��������� � ����������� ������
*/
void SelectFont(HDC hdc, myFont_t* myFont);
#endif
