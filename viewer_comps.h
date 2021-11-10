#ifndef HEADER_VIEWER_COMPS
#define HEADER_VIEWER_COMPS
#include<stddef.h>
#include<stdbool.h>
#include"file_reader.h"
#include"text_comps.h"
#include"win_comps.h"

// ������� ��������� � �������, � ��� ��� ���������� � viewer
typedef struct {
    // ��������� �� reader � ������� ���������� ��� ������ � ��������� ������
    reader_t* readerP;
    // ��������� �� ����������� ����� � ��� ���������
    myFont_t* fontP;
    // ��������� �� ��������� ���� (�������, ��������� ����������)
    winParams_t* winParamsP;
    // ���������� ������� �� ������������� ��������� (Wrap off)
    bool isHorzScroll;
    // Counting during resize and vScrolling, need to know what part of buffer should be printed
    size_t firstPrSymI;
    size_t lastPrSymI;
}viewer_t;

/*
    �������������� ��� viewer:
        �������� ������ ��� ����
        ������������ �� ����������
        (� ��� ����� ���������� �� viewer ���������� ����)
    params:
        viewerP - ��������� �� viewer
        hwnd - ��������� �� ����, ��� �� ���������� viewer
*/
void InitViewer(viewer_t* viewerP, HWND hwnd);

/*
    ����������� ��� ������ ���������� ��� viewer
    ���������� ����� ��������� ����
    params:
        viewerP - ��������� �� viewer
*/
void ClearViewer(viewer_t* viewerP);

/*
    ��������� ���� � ���������� ��� ��������� �� viewer
    params:
        viewerP - ��������� �� viewer
        filename - ��� �����
*/
void SendFileInViewer(viewer_t* viewerP, char* filename);

/*
    ������������ viewer � ����
    params:
        viewerP - ��������� �� viewer
        hdc - ���������� ���� ��� ���������
*/
void ShowViewer(viewer_t* viewerP, HDC hdc);

/*
    ������ ��� ��������� viewer � ������ ������ ������� ����
    params:
        viewerP - ��������� �� viewer
        hwnd - ��������� �� ����, ��� �� ���������� viewer
*/
void ResizeViewer(viewer_t* viewerP, HWND hwnd);

/*
    ������������ ������������ ���������
    params:
        viewerP - ��������� �� viewer
        hwnd - ��������� �� ����, ��� �� ���������� viewer
        wParam - �������� ����������� ��� �����������:
            ������� ����������(������ ���������, �������� �������� � ��)
            ������� ������� �� scrollBar
*/
void ProcessVscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    ������������ �������������� ���������
    params:
        viewerP - ��������� �� viewer
        hwnd - ��������� �� ����, ��� �� ���������� viewer
        wParam - �������� ����������� ��� �����������:
            ������� ����������(������ ���������, �������� �������� � ��)
            ������� ������� �� scrollBar
*/
void ProcessHscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    ������������ ������� ������ �� ����������. ������� ������������ ��� ����������
    params:
        viewerP - ��������� �� viewer
        hwnd - ��������� �� ����, ��� �� ���������� viewer
        wParam - �������� ����������� ��� ����������� ����������� �������
*/
void ProcessKeyDownViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    �������� ������� ����� �� viewer(���� ������� �� ������� ����)
    � ��������� �������������� ���������
    params:
        viewerP - ��������� �� viewer
*/
void WrapOnViewer(viewer_t* viewerP);

/*
    ��������� ������� ����� �� viewer � �������� �������������� ���������
    params:
        viewerP - ��������� �� viewer
*/
void WrapOffViewer(viewer_t* viewerP);

/*
    ������� viewer �� ���� ���������� � ���������� �����
    (� ��� ����� � ����������� ������),
    ������������� ���������, ���������� �� ���� ����������
    params:
        viewerP - ��������� �� viewer
*/
void CloseFileInViewer(viewer_t* viewerP);
#endif
