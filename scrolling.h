#ifndef HEADER_SCROLLING
#define HEADER_SCROLLING

#include"win_comps.h"
#include<stdbool.h>

#define HORZ_SCROLL_DEFAULT false

// ������������ �������� ���������� ���������
#define SCROLL_RANGE_MAX 65535

/*
    ������ ��������� ������������� ���������� vScrollMax � vScrollPos,
    ��� ����� ������ ����
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
        prLinesCount - ���������� �����, ������� ����� ������� � viewer
*/
void ResizeVscrollParams(winParams_t* winParamsP, size_t prLinesCount);

/*
    ������ ��������� ��������������� ���������� hScrollMax � hScrollPos,
    ��� ����� ������ ���� (��� �������, ��� �������������� ��������� �������)
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
        isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ResizeHscrollParams(winParams_t* winParamsP, size_t maxStrLen, bool isHorzScroll);

/*
    ������ ������� ������������� ���������� (��� ���������� �� 1 ������ ������ �����),
    ����� ��� ������, ����� ������������ ����� ������� ����� �� ���������� ��� ������ ����
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ScrollVertLineUpViewer(winParams_t* winParamsP);

/*
    ������ ������� ������������� ���������� (��� ���������� �� 1 ������ ������ ����),
    ����� ��� ������, ����� ������������ ����� ������� ���� �� ���������� ��� ������ ����
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ScrollVertLineDownViewer(winParams_t* winParamsP);

/*
    ������ ������� ������������� ���������� (��� ���������� ����� �� ����������� ����� ������, ����������� � ����),
    ����� ��� ������, ����� ������������ ����� �� ������ ��� ���� �������� ��� pageUp �� ����������
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ScrollVertPageUpViewer(winParams_t* winParamsP);

/*
    ������ ������� ������������� ���������� (��� ���������� ���� �� ����������� ����� ������, ����������� � ����),
    ����� ��� ������, ����� ������������ ����� �� ������ ��� ���� �������� ��� pageDown �� ����������
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
*/
void ScrollVertPageDownViewer(winParams_t* winParamsP);

/*
    ������ ������� ��������������� ���������� (��� ���������� �� 1 ������ ������ �����),
    ����� ��� ������, ����� ������������ ����� ������� ����� �� ���������� ��� ������ ����.
    �������� ��� �������, ��� ������� �������������� ���������
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
        isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ScrollHorzLineUpViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    ������ ������� ��������������� ���������� (��� ���������� �� 1 ������ ������ ������),
    ����� ��� ������, ����� ������������ ����� ������� ������ �� ���������� ��� ������ ����.
    �������� ��� �������, ��� ������� �������������� ���������
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
        isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ScrollHorzLineDownViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    ������ ������� ��������������� ���������� (��� ���������� ����� �� ���������� �������� � ������, ����������� � ����),
    ����� ��� ������, ����� ������������ ����� ����� �� �������� �� ������ ����.
    �������� ��� �������, ��� ������� �������������� ���������
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
        isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ScrollHorzPageUpViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    ������ ������� ��������������� ���������� (��� ���������� ������ �� ����������� �������� � ������, ����������� � ����),
    ����� ��� ������, ����� ������������ ����� ������ �� �������� �� ������ ����.
    �������� ��� �������, ��� ������� �������������� ���������
    params:
        winParamsP - ��������� �� ��� ��������� � ����������� ����
        isHorzScroll - bool ������� �� �������������� ��������� (Wrap off)
*/
void ScrollHorzPageDownViewer(winParams_t* winParamsP, bool isHorzScroll);

/*
    ���������� ��������� ������� ���������� �� ��� (��� ����� ���� �� ����� �� �� ����������� ��������� �� ��������� ����������)
    params:
        myScrollMax - ����������� ��������� ������� ����������
        sysScrPos - ��������� ������� ����������
    return:
        ��� ������� ����������
*/
size_t GetScrollPosMyFromSystem(size_t myScrollMax, int sysScrPos);

/*
    ���������� ��� ������� ���������� �� ��������� (��� ����� ���� �� ����� �� �� ����������� ��������� �� ��������� ����������)
    params:
        myScrollMax - ����������� ��������� ������� ����������
        myScrPos - ��� ������� ����������
    return:
        ��������� ������� ����������
*/
int GetScrollPosSystemFromMy(size_t myScrollMax, size_t myScrPos);
#endif
