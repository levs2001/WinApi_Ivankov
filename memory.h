#ifndef HEADER_MEMORY
#define HEADER_MEMORY
#include<stddef.h>

void* getMem(size_t memSize, char* reason);
void freeMem(void* pointer, char* reason);

#endif

