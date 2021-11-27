#ifndef HEADER_EXCEPTIONS
#define HEADER_EXCEPTIONS

#include <stdio.h>

// ���� ���������� � ���� ������ ���������
typedef enum {
    // �� ������� ������� ����
    FILE_NOT_OPEN,
    // ��� ������������ ������ ���������� ��� ������ ����������, ��� ��� NULL
    NULL_BUFF_POINTER,
    // ��� ������������ ������ ���������� ��� reader ����������, ��� ��� NULL
    NULL_READER_POINTER,
    // ��� ������������ ������ ���������� ��� viewer ����������, ��� ��� NULL
    NULL_VIEWER_POINTER,
    // ��� ������������ ������ ���������� ��� ��������� ���������� ���� ����������, ��� ��� NULL
    NULL_WIN_PARAMS_POINTER,
    // ��� ������������ ������ ���������� ��� ��������� ������ ����������, ��� ��� NULL
    NULL_FONT_POINTER,
    // ��� ������������ ������ ���������� ��� ������ ������ ����� ����������, ��� ��� NULL
    NULL_LN_ENDS_POINTER,
    // �� ������� ��������� ������ ������ �����
    REALLOC_REFUSE_LN_ENDS
} eException;

/*
    ���������� ���������� �� ���������� � ���
    params:
        [in] exceptionType - ��� ����������
*/
void Exception(eException exceptionType);

/*
    ���������� ��������� � ��� (�������)
    params:
        [in] msg - ��������� �� ������ � ����������
*/
void logMsg(char* msg);

#endif
