#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"

unsigned long long getticks(void);

int main()
{
    unsigned long long t0, t1, dt, thirata, tbest;

    int best[4];
    double error, one = 1.0;

    int a,b,c,d,d1,d2,d3,d4;

    double * iptr = (double*) malloc(23*34*25*16*sizeof(double));
    double * optr = (double*) malloc(23*34*25*16*sizeof(double));
    double * hptr = (double*) malloc(23*34*25*16*sizeof(double));

    rand4d(23,34,25,16,iptr);
    zero4d(23,34,25,16,optr);
    zero4d(23,34,25,16,hptr);

    d1=23;
    d2=34;
    d3=25;
    d4=16;

    printf("===========================================\n");
    a=1; b=2; c=3; d=4;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  1234      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1234_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1234_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=1; b=2; c=4; d=3;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  1243      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1243_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1243_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=1; b=3; c=2; d=4;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  1324      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1324_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1324_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=1; b=3; c=4; d=2;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  1342      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1342_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1342_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=1; b=4; c=2; d=3;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  1423      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1423_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1423_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=1; b=4; c=3; d=2;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  1432      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_1432_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_1432_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=2; b=1; c=3; d=4;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  2134      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2134_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2134_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=2; b=1; c=4; d=3;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  2143      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2143_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2143_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=2; b=3; c=1; d=4;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  2314      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2314_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2314_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=2; b=3; c=4; d=1;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  2341      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2341_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2341_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=2; b=4; c=1; d=3;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  2413      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2413_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2413_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=2; b=4; c=3; d=1;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  2431      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_2431_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_2431_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=3; b=1; c=2; d=4;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  3124      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3124_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3124_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=3; b=1; c=4; d=2;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  3142      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3142_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3142_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=3; b=2; c=1; d=4;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  3214      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3214_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3214_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=3; b=2; c=4; d=1;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  3241      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3241_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3241_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=3; b=4; c=1; d=2;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  3412      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3412_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3412_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=3; b=4; c=2; d=1;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  3421      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_3421_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_3421_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=4; b=1; c=2; d=3;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  4123      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4123_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4123_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=4; b=1; c=3; d=2;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  4132      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4132_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4132_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=4; b=2; c=1; d=3;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  4213      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4213_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4213_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=4; b=2; c=3; d=1;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  4231      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4231_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4231_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=4; b=3; c=1; d=2;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  4312      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4312_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4312_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");
    a=4; b=3; c=2; d=1;
    t0 = getticks();
    for (int t=0;t<100;t++) tce_sort_4_(iptr,hptr,&d1,&d2,&d3,&d4,&a,&b,&c,&d,&one);
    t1 = getticks();
    thirata = (t1-t0)/100;    printf("hirata  4321      took %12llu cycles\n",thirata);
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_1234(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_1234 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_1243(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_1243 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 2;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_1324(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_1324 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_1342(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_1342 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 3;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_1423(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_1423 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_1432(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_1432 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 1;
       best[1] = 4;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_2134(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_2134 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 3;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_2143(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_2143 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 1;
       best[2] = 4;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_2314(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_2314 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_2341(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_2341 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 3;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_2413(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_2413 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_2431(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_2431 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 2;
       best[1] = 4;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_3124(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_3124 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 2;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_3142(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_3142 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 1;
       best[2] = 4;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_3214(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_3214 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 1;
       best[3] = 4;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_3241(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_3241 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 2;
       best[2] = 4;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_3412(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_3412 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_3421(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_3421 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 3;
       best[1] = 4;
       best[2] = 2;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_4123(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_4123 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 2;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_4132(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_4132 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 1;
       best[2] = 3;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_4213(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_4213 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 1;
       best[3] = 3;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_4231(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_4231 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 2;
       best[2] = 3;
       best[3] = 1;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_4312(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_4312 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 1;
       best[3] = 2;
    }
    t0 = getticks();
    for (int t=0;t<100;t++) permute_4321_4321(23,34,25,16,iptr,optr);
    t1 = getticks();
    dt = (t1-t0)/100;    error = diff4d(23,34,25,16,optr,hptr);
    printf("permute_4321_4321 took %12llu cycles (error = %lf)\n",dt,error);
    if (error<1e-13 && dt<tbest)
    {
       tbest = dt;
       best[0] = 4;
       best[1] = 3;
       best[2] = 2;
       best[3] = 1;
    }
    printf("BEST         %1d%1d%1d%1d took %12llu cycles (%lf faster than original)\n",best[0],best[1],best[2],best[3],tbest,(double)thirata/(double)tbest);
    printf("===========================================\n");

    free(iptr);
    free(optr);

    return 0;
}
