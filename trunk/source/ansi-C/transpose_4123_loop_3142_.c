    void transpose_4123_loop_3142_( double *unsorted, double *sorted,
                                    int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4, double *p_factor ) {

    int dim1,dim2,dim3,dim4;
    unsigned int old_offset,new_offset;
    unsigned int j1,j2,j3,j4;
    double factor;
    factor = *p_factor;

    dim1 = *p_dim1;
    dim2 = *p_dim2;
    dim3 = *p_dim3;
    dim4 = *p_dim4;

    /* pluto start (dim1,dim2,dim3,dim4) */
    for( j3 = 0; j3<dim3; j3++) {
        for( j1 = 0; j1<dim1; j1++) {
            for( j4 = 0; j4<dim4; j4++) {
                for( j2 = 0; j2<dim2; j2++) {
                    old_offset = j4+dim4*(j3+dim3*(j2+dim2*(j1)));
                    new_offset = j3+dim3*(j2+dim2*(j1+dim1*(j4)));
                    sorted[new_offset] = unsorted[old_offset] * factor;
                }
            }
        }
    }
    /* pluto end */
    return;
    }

