void init4d(int dim1, int dim2, int dim3, int dim4, double * ptr)
{
    int shift1, shift2, shift3;

    if (dim1<100 && dim2<100 && dim3<100 && dim4<100) shift1 = 100;
    else shift1 = 1000;

    shift2 = shift1*shift1;
    shift3 = shift2*shift1;

    for (int i=0;i<dim1;i++)
      for (int j=0;j<dim2;j++)
        for (int k=0;k<dim3;k++)
          for (int l=0;l<dim4;l++)
             ptr[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l] = (double) (i*shift3 + j*shift2 + k*shift1 + l);

    return;
}

void zero4d(int dim1, int dim2, int dim3, int dim4, double * ptr)
{
    for (int i=0;i<(dim1*dim2*dim3*dim4);i++) ptr[i] = 0.0;
    return;
}

