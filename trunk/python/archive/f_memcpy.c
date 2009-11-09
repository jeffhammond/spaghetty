//#include <stdio.h>
#include <string.h>

void f_memcpy_(void* new, void* old, int* length)
{
  memcpy(new,old,*length);
  return;
}

