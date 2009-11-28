#include <stdio.h>
#include <time.h>

int getticks_(void)
{
    return (int) clock();
}

double* gettime_(void)
{
    clock_t time1;
    double  time2;
    time1 = clock();
    time2 = (double) time1 / CLOCKS_PER_SEC;
    printf("time2 = %14.7f\n",time2);
    fflush(stdout);
    return time2;
}
