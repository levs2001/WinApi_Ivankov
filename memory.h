#ifndef HEADER_MEMORY
#define HEADER_MEMORY
#include<stddef.h>

/*
    �������� ������, ���������� � ���, ��� ������ �������� � ��� ���� � ���
    params:
        [in] memSize - ������� ����� �������� ������
        [in] reason - ��������� �� ������, ��� �������� ��� ���� ������
    return:
        ��������� �� ���� ���������� ������
*/
void* getMem(size_t memSize, char* reason);

/*
    ����������� ������, ���������� � ���, ��� ������ ���������� � ��� ���� ������ ��������������
    params:
        [in|out] pointer - ��������� �� ���� ������������� ������
        [in] reason - ��������� �� ������, ��� �������� ��� ���� ����� ���� ������
*/
void freeMem(void* pointer, char* reason);

#endif

