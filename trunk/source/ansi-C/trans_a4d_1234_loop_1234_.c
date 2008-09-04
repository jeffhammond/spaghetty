    #include <stdlib.h>
    #include <stdio.h>

    void trans_a4d_1234_loop_1234_( double *unsorted, double *sorted,
                                    int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4, double *p_factor ) {

    int dim1,dim2,dim3,dim4;
    int j1,j2,j3,j4;
    int i,j,k,l;
    double factor;
    double**** _sorted;

    factor = *p_factor;

    dim1 = *p_dim1;
    dim2 = *p_dim2;
    dim3 = *p_dim3;
    dim4 = *p_dim4;

    _sorted = (double ****) malloc (dim1*sizeof(double ***));

    for (i=0; i<dim1; i++) {
        _sorted[i] = (double ***) malloc (dim2*sizeof(double **));
    }

    for (i=0; i<dim1; i++) {
        for (j=0; j<dim2; j++) {
            _sorted[i][j] = (double **) malloc (dim3*sizeof(double *));
        }
    }

    for (i=0; i<dim1; i++) {
        for (j=0; j<dim2; j++) {
            for (k=0; k<dim3; k++) {
                _sorted[i][j][k] = &sorted[dim1*dim2*dim3*i + dim2*dim3*j + dim3*k];
            }
        }
    }

    /* pluto start (dim1,dim2,dim3,dim4) */
    for( j1 = 0; j1<dim1; j1++) {
        for( j2 = 0; j2<dim2; j2++) {
            for( j3 = 0; j3<dim3; j3++) {
                for( j4 = 0; j4<dim4; j4++) {
                    _sorted[j1][j2][j3][j4] = unsorted[j1][j2][j3][j4] * factor;
                }
            }
        }
    }
    /* pluto end */
    return;
    }

