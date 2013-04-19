#include <stdio.h>

unsigned long long getticks_(void)
{
     unsigned int rx, ry, rz;
     unsigned long long r64;

     do
     {
         asm volatile ( "mftbu %0" : "=r"(rx) );
         asm volatile ( "mftb %0" : "=r"(ry) );
         asm volatile ( "mftbu %0" : "=r"(rz) );
     }
     while ( rx != rz );

     r64 = rx;
     r64 = ( r64 << 32 ) | ry;
     
     return r64;
}
