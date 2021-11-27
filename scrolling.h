#ifndef HEADER_SCROLLING
#define HEADER_SCROLLING

#include"viewer_comps.h"
#include"win_comps.h"
#include<stdbool.h>

#define HORZ_SCROLL_DEFAULT false

// ������������ �������� ���������� ���������
#define SCROLL_RANGE_MAX 65535

/*
    ������ ��������� ������������� ���������� vScrollMax � vScrollPos,
    ��� ����� ������ ����.
    params:
        [in|out] viewerP - ��������� �� ��������� �������
        [in] prLinesCount - ���������� �����, ������� ����� ������� � viewer
*/
void ResizeVscrollParams(viewer_t* viewerP, size_t prLinesCount);

/*
    ������ ��������� ��������������� ���������� hScrollMax � hScrollPos,
    ��� ����� ������ ���� (��� �������, ��� �������������� ��������� �������)
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
        [in] isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ResizeHscrollParams(winParams_t* winParamsP, size_t maxStrLen, bool isHorzScroll);

/*
    ������ ������� ������������� ���������� (��� ���������� �� 1 ������ ������ �����),
    ����� ��� ������, ����� ������������ ����� ������� ����� �� ���������� ��� ������ ����
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ScrollVertLineUpViewer(winParams_t* winParamsP);

/*
    ������ ������� ������������� ���������� (��� ���������� �� 1 ������ ������ ����),
    ����� ��� ������, ����� ������������ ����� ������� ���� �� ���������� ��� ������ ����
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ScrollVertLineDownViewer(winParams_t* winParamsP);

/*
    ������ ������� ������������� ���������� (��� ���������� ����� �� ����������� ����� ������, ����������� � ����),
    ����� ��� ������, ����� ������������ ����� �� ������ ��� ���� �������� ��� pageUp �� ����������
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ScrollVertPageUpViewer(winParams_t* winParamsP);

/*
    ������ ������� ������������� ���������� (��� ���������� ���� �� ����������� ����� ������, ����������� � ����),
    ����� ��� ������, ����� ������������ ����� �� ������ ��� ���� �������� ��� pageDown �� ����������
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ScrollVertPageDownViewer(winParams_t* winParamsP);

/*
    ������ ������� ��������������� ���������� (��� ���������� �� 1 ������ ������ �����),
    ����� ��� ������, ����� ������������ ����� ������� ����� �� ���������� ��� ������ ����.
    �������� ��� �������, ��� ������� �������������� ���������
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
        [in] isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ScrollHorzLineUpViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    ������ ������� ��������������� ���������� (��� ���������� �� 1 ������ ������ ������),
    ����� ��� ������, ����� ������������ ����� ������� ������ �� ���������� ��� ������ ����.
    �������� ��� �������, ��� ������� �������������� ���������
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
        [in] isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ScrollHorzLineDownViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    ������ ������� ��������������� ���������� (��� ���������� ����� �� ���������� �������� � ������, ����������� � ����),
    ����� ��� ������, ����� ������������ ����� ����� �� �������� �� ������ ����.
    �������� ��� �������, ��� ������� �������������� ���������
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
        [in] isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ScrollHorzPageUpViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    ������ ������� ��������������� ���������� (��� ���������� ������ �� ����������� �������� � ������, ����������� � ����),
    ����� ��� ������, ����� ������������ ����� ������ �� �������� �� ������ ����.
    �������� ��� �������, ��� ������� �������������� ���������
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
        [in] isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ScrollHorzPageDownViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    ���������� ��������� ������� ���������� �� ��� (��� ����� ���� �� ����� �� �� ����������� ��������� �� ��������� ����������)
    params:
        [in] myScrollMax - ����������� ��������� ������� ����������
        [in] sysScrPos - ��������� ������� ����������
    return:
        ��� ������� ����������
*/
size_t GetScrollPosMyFromSystem(size_t myScrollMax, int sysScrPos);

/*
    ���������� ��� ������� ���������� �� ��������� (��� ����� ���� �� ����� �� �� ����������� ��������� �� ��������� ����������)
    params:
        [in] myScrollMax - ����������� ��������� ������� ����������
        [in] myScrPos - ��� ������� ����������
    return:
        ��������� ������� ����������
*/
int GetScrollPosSystemFromMy(size_t myScrollMax, size_t myScrPos);

/*
    ������ �������� ��������� ����������� �� ������������ ���������, ���� ��� ��������
    params:
        [in|out] winParamsP - ��������� �� ��� ��������� � ����������� ����
        [in] delta - �������� �� ������� ���� �������� ������� ������������� ����������
*/
void ChangeVScrollPos(winParams_t* winParamsP, long delta);
#endif
