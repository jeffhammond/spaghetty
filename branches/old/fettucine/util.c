#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void zero4d(int dim1, int dim2, int dim3, int dim4, double * a)
{
    int i;
#pragma omp parallel for private(i) schedule(static)
    for (i=0;i<(dim1*dim2*dim3*dim4);i++) a[i] = 0.0;
    return;
}

void rand4d(int dim1, int dim2, int dim3, int dim4, double * a)
{
    printf("begin rand4d\n");
    for (int i=0;i<(dim1*dim2*dim3*dim4);i++) a[i] = (double) rand()/RAND_MAX;
    printf(" end  rand4d\n");
    fflush(stdout);
    return;
}

void copy4d(int dim1, int dim2, int dim3, int dim4, double * in, double * out)
{
    for (int i=0;i<(dim1*dim2*dim3*dim4);i++) out[i] = in[i];
    return;
}

void init4d(int dim1, int dim2, int dim3, int dim4, double * a)
{
    double shift1, shift2, shift3;

    if (dim1<100 && dim2<100 && dim3<100 && dim4<100) shift1 = 0.001;
    else shift1 = 0.0001;

    shift2 = shift1*shift1;
    shift3 = shift2*shift1;

    for (int i=0;i<dim1;i++)
        for (int j=0;j<dim2;j++)
            for (int k=0;k<dim3;k++)
                for (int l=0;l<dim4;l++)
                    a[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l] = (double) (i + j*shift1 + k*shift2 + l*shift3);

    return;
}

double diff4d(int dim1, int dim2, int dim3, int dim4, double * a, double * b)
{
    double error = 0.0;

    for (int i=0;i<dim1;i++)
        for (int j=0;j<dim2;j++)
            for (int k=0;k<dim3;k++)
                for (int l=0;l<dim4;l++)
                {
                    error += fabs( a[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l] - b[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l]);
                }

    return error;
}

void print4d(int dim1, int dim2, int dim3, int dim4, double * a)
{
    for (int i=0;i<dim1;i++)
        for (int j=0;j<dim2;j++)
            for (int k=0;k<dim3;k++)
                for (int l=0;l<dim4;l++)
                {
                    printf("[%2d,%2d,%2d,%2d] = ",i,j,k,l);
                    printf("%20.14lf ",a[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l]);
                    printf("\n");
                }

    return;
}

void print4d2(int dim1, int dim2, int dim3, int dim4, double * a, double * b)
{
    for (int i=0;i<dim1;i++)
        for (int j=0;j<dim2;j++)
            for (int k=0;k<dim3;k++)
                for (int l=0;l<dim4;l++)
                {
                    printf("[%2d,%2d,%2d,%2d] = ",i,j,k,l);
                    printf("%20.14lf ",a[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l]);
                    printf("%20.14lf ",b[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l]);
                    printf("\n");
                }

    return;
}

void print4d3(int dim1, int dim2, int dim3, int dim4, double * a, double * b, double * c)
{
    for (int i=0;i<dim1;i++)
        for (int j=0;j<dim2;j++)
            for (int k=0;k<dim3;k++)
                for (int l=0;l<dim4;l++)
                {
                    printf("[%2d,%2d,%2d,%2d] = ",i,j,k,l);
                    printf("%20.14lf ",a[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l]);
                    printf("%20.14lf ",b[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l]);
                    printf("%20.14lf ",c[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l]);
                    printf("\n");
                }

    return;
}


