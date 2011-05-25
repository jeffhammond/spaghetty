#ifdef HAVE_DCMF_TIMEBASE

#include "dcmf.h"

__inline__ unsigned long long getticks(void)
{
    return DCMF_Timebase();
}


#else

/*
 * author: azutomo Yoshii kazutomo@mcs.anl.gov
 * from http://www.mcs.anl.gov/~kazutomo/getticks.html
 * */

#if defined(__i386__)

__inline__ unsigned long long getticks(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

#elif defined(__x86_64__)

__inline__ unsigned long long getticks(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#elif defined(__powerpc__)

__inline__ unsigned long long getticks(void)
{
    unsigned long long int result=0;
    unsigned long int upper, lower,tmp;
    __asm__ volatile(
            "0:                  \n"
            "\tmftbu   %0           \n"
            "\tmftb    %1           \n"
            "\tmftbu   %2           \n"
            "\tcmpw    %2,%0        \n"
            "\tbne     0b         \n"
            : "=r"(upper),"=r"(lower),"=r"(tmp)
    );
    result = upper;
    result = result<<32;
    result = result|lower;

    return(result);
}

#else

#error NO CYCLE-ACCURATE COUNTER AVAILABLE

//#include <time.h>
////unsigned long long getticks(void) { return (unsigned long long) clock(); }
//
//#endif // targets
//
//#endif // HAVE_DCMF_TIMEBASE
//
//
