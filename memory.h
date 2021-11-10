#ifndef HEADER_MEMORY
#define HEADER_MEMORY
#include<stddef.h>

/*
    �������� ������, ���������� � ���, ��� ������ �������� � ��� ���� � ���
    params:
        memSize - ������� ����� �������� ������
        reason - ��������� �� ������, ��� �������� ��� ���� ������
    return:
        ��������� �� ���� ���������� ������
*/
void* getMem(size_t memSize, char* reason);

/*
    ����������� ������, ���������� � ���, ��� ������ ���������� � ��� ���� ������ ��������������
    params:
        pointer - ��������� �� ���� ������������� ������
        reason - ��������� �� ������, ��� �������� ��� ���� ����� ���� ������
*/
void freeMem(void* pointer, char* reason);

#endif

