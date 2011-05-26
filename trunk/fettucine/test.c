#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long getticks(void);
void init4d(int dim1, int dim2, int dim3, int dim4, double * ptr);
void zero4d(int dim1, int dim2, int dim3, int dim4, double * ptr);
void rand4d(int dim1, int dim2, int dim3, int dim4, double * ptr);
double diff4d(int dim1, int dim2, int dim3, int dim4, double * a, double * b);
void print4d(int dim1, int dim2, int dim3, int dim4, double * ptr);
void print4d2(int dim1, int dim2, int dim3, int dim4, double * a, double * b);

int main()
{
    unsigned long long t0, t1;

    double * iptr = (double*) malloc(3*3*3*3*sizeof(double));
    double * optr = (double*) malloc(3*3*3*3*sizeof(double));

    rand4d(3,3,3,3,iptr);
    zero4d(3,3,3,3,optr);

    printf("===========================================\n");
    t0 = getticks();
    for (int t=0;t<100;t++)permute_4321_2341(3,3,3,3,iptr,optr);
    t1 = getticks();
    printf("permute_4321_2341 took %12llu cycles\n",(t1-t0)/100);
    printf("===========================================\n");

    print4d2(3,3,3,3,iptr,optr);

    free(iptr);
    free(optr);

    return 0;
}
