#ifndef HEADER_WIN_COMPS
#define HEADER_WIN_COMPS
#include<stddef.h>
#include<stdbool.h>
#include<windows.h>
#include"text_comps.h"

#define MIN_X 0
// ���������, �������� ��������� ����
typedef struct {
    // ������ ����
    size_t width;
    // ������ ����
    size_t height;
    // ���������� ��������, ������� ����� ����������� � ����� ������, �� ������ �� ������� ����
    size_t widthInSyms;
    // ���������� �����, ������� ����� �����������, �� ������ �� ������� ����
    size_t heightInSyms;
    // ������� ������������� ����������
    size_t vScrollPos;
    // ������� ��������������� ���������
    size_t hScrollPos;
    // ����������� ��������� ������� ������������� ����������, ������ ����� ���������� �����,
    // ������� ����� ����������� � viewer
    size_t vScrollMax;
    // ����������� ��������� ������� ��������������� ����������, ������ ����� ����� ������������ ������
    size_t hScrollMax;
}winParams_t;

/*
    �������������� �������� ��������� ���������� ����, �������� ��� ��� ������
    params:
        [in] hwnd - ��������� �� ����, ��� �� ���������� viewer
        [in] myFontP - ��������� �� ��������� � ����������� ������������� ������
    return:
        ��������� �� ��� ��������� � ����������� ����
*/
winParams_t* InitWinParams(HWND hwnd, myFont_t* myFontP);

/*
    ������ ��������� ���� � ����������� �� �������� ����, � ������� ������������ ����
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
        [in] hwnd - ��������� �� ����, ��� �� ���������� viewer
        [in] myFontP - ��������� �� ��������� � ����������� ������������� ������
*/
void ResizeWinParams(winParams_t* winParamsP, HWND hwnd, myFont_t* myFontP);

/*
    ����������� ������, ���������� �� ��������� � ����������� ����
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ClearWinParams(winParams_t* winParamsP);

/*
    ������� ��������� ������, � ������� ������������ ����� ������� ����
    ���������� ��� ����� � filenameP
    params:
        [in] hwnd - ��������� �� ���� ���������
        [out] filenameP - ��������� �� ������, ���� ������ ���������� ��� �����
    return:
        true - � ������ ������
        false - � ������ ������� (��������, ���� ������� �� ��������� ����)
*/
bool OpenFileDlg(HWND hwnd, LPSTR filenameP);

#endif
