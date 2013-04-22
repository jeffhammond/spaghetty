    void transpose_4321_loop_3241_( double *unsorted, double *sorted,
                                    int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4, double *p_factor ) {

    unsigned int dim1 = *p_dim1;
    unsigned int dim2 = *p_dim2;
    unsigned int dim3 = *p_dim3;
    unsigned int dim4 = *p_dim4;

    unsigned int old_offset,new_offset;
    unsigned int old_t1,new_t1;
    unsigned int old_t2,new_t2;
    unsigned int old_t3,new_t3;

    unsigned int j1,j2,j3,j4;

    double factor = *p_factor;

    unsigned int dim12 = dim1*dim2;
    unsigned int dim34 = dim3*dim4;
    unsigned int dim123 = dim1*dim2*dim3;
    unsigned int dim234 = dim2*dim3*dim4;

    #pragma ivdep
    #pragma parallel
    #pragma loop count min(10) max(80) avg(40)
    #pragma unroll
    for( j3 = 0; j3<dim3; j3++) {
        old_t1 = dim4*j3;
        new_t1 = dim12*j3;
        #pragma loop count min(10) max(80) avg(40)
        #pragma unroll
        for( j2 = 0; j2<dim2; j2++) {
            old_t2 = old_t1 + j2*dim34;
            new_t2 = new_t1 + j2*dim1;
            #pragma loop count min(10) max(80) avg(40)
            #pragma unroll
            #pragma vector always
            for( j4 = 0; j4<dim4; j4++) {
                old_t3 = old_t2 + j4;
                new_t3 = new_t2 + dim123*j4;
                #pragma loop count min(10) max(80) avg(40)
                #pragma unroll
                #pragma vector always
                for( j1 = 0; j1<dim1; j1++) {
                    // old_offset = j4+dim4*(j3+dim3*(j2+dim2*(j1)));
                    // new_offset = j1+dim1*(j2+dim2*(j3+dim3*(j4)));
                    // old_offset = j4+dim4*j3+dim4*dim3*j2+dim4*dim3*dim2*j1;
                    // new_offset = j1+dim1*j2+dim1*dim2*j3+dim1*dim2*dim3*j4;
                    // old_offset = old_t3 + dim234*j1;
                    // new_offset = new_t3 + j1;
                    sorted[new_t3 + j1] = unsorted[old_t3 + dim234*j1] * factor;
                }
            }
        }
    }
    return;
    }

