#ifndef HEADER_FILE_READER
#define HEADER_FILE_READER

#include<stdio.h>

// ��������� � ����������� � ������, ����������� �� viewer
typedef struct {
    // ��������� �� ������ � ���������� ������
    char* buffer;
    // ������ ������� � ���������� ������
    size_t bufferSize;
    // ��������� �� ������ � ��������� ������ ����� � ������
    size_t* lnEnds;
    // ������ ������� � ��������� ������ ����� (���������� ��������� ����� � ������)
    size_t lnEndsSize;
    // ������ ����� ������� ������ � ������
    size_t maxStrLen;
}reader_t;

/*
    ��������� ��������� reader_t ���������� �����, ������������� ��
    ���������� ������ ��� buffer � lnEnds
    params:
        readerP - ��������� �� ���������, ���� ��������� ���������� �����
        filename - ��� �����, ������� ���� ��������
*/
void WriteFileInReader(reader_t* readerP, char* filename);

/*
    ����������� ������ �������� ���������
    params:
        readerP - ��������� �� ���������, ���� �������� ���������� �����
*/
void ClearReader(reader_t* readerP);

/*
    ����������� ������ �������� ��� �������(buffer � lnEnds) � reader � ��������� ��� �������� ������
    params:
        readerP - ��������� �� ���������, ���� �������� ���������� �����
*/
void EmptyReader(reader_t* readerP);

/*
    ��������� ��������� ������ ������ � NULL
    params:
        readerP - ��������� �� ���������, ���� �������� ���������� �����
*/
void NullifyReader(reader_t* readerP);
#endif

