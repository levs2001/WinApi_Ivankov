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
    /// Counting during resize and vScrolling, need to know what part of buffer should be printed
    //�������� ������� � ���������� ���������� ������� ������������ ������ �������
    size_t firstPrSymI;
    size_t lastPrSymI;
}viewer_t;

/*
    �������������� ��� viewer:
        �������� ������ ��� ����
        ������������ �� ����������
        (� ��� ����� ���������� �� viewer ���������� ����)
    params:
        [out] viewerP - ��������� �� viewer
        [in] hwnd - ��������� �� ����, ��� �� ���������� viewer
*/
void InitViewer(viewer_t* viewerP, HWND hwnd);

/*
    ����������� ��� ������ ���������� ��� viewer
    ���������� ����� ��������� ����
    params:
        [out] viewerP - ��������� �� viewer
*/
void ClearViewer(viewer_t* viewerP);

/*
    ��������� ���� � ���������� ��� ��������� �� viewer
    params:
        [out] viewerP - ��������� �� viewer
        [in] filename - ��� �����
*/
void SendFileInViewer(viewer_t* viewerP, char* filename);

/*
    ������������ viewer � ����
    params:
        [in] viewerP - ��������� �� viewer
        [in] hdc - ���������� ���� ��� ���������
*/
void ShowViewer(viewer_t* viewerP, HDC hdc);

/*
    ������ ��� ��������� viewer � ������ ������ ������� ����
    params:
        [out] viewerP - ��������� �� viewer
        [in] hwnd - ��������� �� ����, ��� �� ���������� viewer
*/
void ResizeViewer(viewer_t* viewerP, HWND hwnd);

/*
    ������������ �������� �������� ���� �������������
    params:
        [in|out] viewerP - ��������� �� viewer
        [in] hwnd - ��������� �� ����, ��� �� ���������� viewer
        [in] wParam - �������� ����������� ��� ����������� �� ������� ��������� ��������
*/
void ProcessMouseWheel(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    ������������ ������������ ���������
    params:
        [in|out] viewerP - ��������� �� viewer
        [in] hwnd - ��������� �� ����, ��� �� ���������� viewer
        [in] wParam - �������� ����������� ��� �����������:
            ������� ����������(������ ���������, �������� �������� � ��)
            ������� ������� �� scrollBar
*/
void ProcessVscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    ������������ �������������� ���������
    params:
        [in|out] viewerP - ��������� �� viewer
        [in] hwnd - ��������� �� ����, ��� �� ���������� viewer
        [in] wParam - �������� ����������� ��� �����������:
            ������� ����������(������ ���������, �������� �������� � ��)
            ������� ������� �� scrollBar
*/
void ProcessHscrollViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    ������������ ������� ������ �� ����������. ������� ������������ ��� ����������
    params:
        [in|out] viewerP - ��������� �� viewer
        [in] hwnd - ��������� �� ����, ��� �� ���������� viewer
        [in] wParam - �������� ����������� ��� ����������� ����������� �������
*/
void ProcessKeyDownViewer(viewer_t* viewerP, HWND hwnd, WPARAM wParam);

/*
    �������� ������� ����� �� viewer(���� ������� �� ������� ����)
    � ��������� �������������� ���������
    params:
        [out] viewerP - ��������� �� viewer
*/
void WrapOnViewer(viewer_t* viewerP);

/*
    ��������� ������� ����� �� viewer � �������� �������������� ���������
    params:
        [out] viewerP - ��������� �� viewer
*/
void WrapOffViewer(viewer_t* viewerP);

/*
    ������� viewer �� ���� ���������� � ���������� �����
    (� ��� ����� � ����������� ������),
    ������������� ���������, ���������� �� ���� ����������
    params:
        [out] viewerP - ��������� �� viewer
*/
void CloseFileInViewer(viewer_t* viewerP);
#endif
