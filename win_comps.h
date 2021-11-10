#ifndef HEADER_WIN_COMPS
#define HEADER_WIN_COMPS
#include<stddef.h>
#include<stdbool.h>
#include<windows.h>
#include"text_comps.h"

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
        hwnd - ��������� �� ����, ��� �� ���������� viewer
        myFontP - ��������� �� ��������� � ����������� ������������� ������
    return:
        ��������� �� ��� ��������� � ����������� ����
*/
winParams_t* InitWinParams(HWND hwnd, myFont_t* myFontP);

/*
    ������ ��������� ���� � ����������� �� �������� ����, � ������� ������������ ����
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
        hwnd - ��������� �� ����, ��� �� ���������� viewer
        myFontP - ��������� �� ��������� � ����������� ������������� ������
*/
void ResizeWinParams(winParams_t* winParamsP, HWND hwnd, myFont_t* myFontP);

/*
    ����������� ������, ���������� �� ��������� � ����������� ����
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ClearWinParams(winParams_t* winParamsP);

/*
    ������� ��������� ������, � ������� ������������ ����� ������� ����
    ���������� ��� ����� � filenameP
    params:
        hwnd - ��������� �� ���� ���������
        filenameP - ��������� �� ������, ���� ������ ���������� ��� �����
    return:
        true - � ������ ������
        false - � ������ ������� (��������, ���� ������� �� ��������� ����)
*/
bool OpenFileDlg(HWND hwnd, LPSTR filenameP);

#endif
