
#include <stdio.h>
#include <xmmintrin.h>
#include <emmintrin.h>

#if defined(__GNUC__)
static double buf[256] __attribute__ ((aligned(128)));
static double buf1[256] __attribute__ ((aligned(128)));
#elif defined(__INTEL_COMPILER) || defined(__ICC)
__declspec(align(128)) static double buf[256],buf1[256];
#endif

#include <math.h>

    void transpose_4321_loop_3241_( double *unsorted, double *sorted,
                                    int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4, double *p_factor ) {

    int dim1,dim2,dim3,dim4;
    int dim1mod,dim2mod,dim3mod,dim4mod;
    unsigned int old_offset,new_offset;
    unsigned int j1,j2,j3,j4;
    double factor = *p_factor;
    double *pA, *pB;
    register __m128d x, y, z, w, t, t1,fac_vector;
    unsigned int N1,N2;
    fac_vector = _mm_load_sd(&factor);
    fac_vector = _mm_unpacklo_pd(fac_vector,fac_vector);


    dim1 = *p_dim1;
    dim2 = *p_dim2;
    dim3 = *p_dim3;
    dim4 = *p_dim4;

    N1 = dim2*dim3*dim4;
    N2 = dim2*dim3*dim4;

    dim1mod = (int) floor( (float)dim1 / (float) 4);
    dim2mod = (int) floor( (float)dim2 / (float) 4);
    dim3mod = (int) floor( (float)dim3 / (float) 4);
    dim4mod = (int) floor( (float)dim4 / (float) 4);

    /* pluto start (dim1,dim2,dim3,dim4) */
    #pragma ivdep
    #pragma parallel
    #pragma loop count min(10) max(80) avg(40)
    #pragma unroll
    for( j3 = 0; j3<dim3; j3++) {
        #pragma loop count min(10) max(80) avg(40)
        #pragma unroll
        for( j2 = 0; j2<dim2; j2++) {
            #pragma loop count min(10) max(80) avg(40)
            #pragma unroll
            #pragma vector always
            for( j4 = 0; j4<dim4; j4+=2) {
                #pragma loop count min(10) max(80) avg(40)
                #pragma unroll
                #pragma vector always
                for( j1 = 0; j1<dim1; j1+=2) {
                    //sorted[j1+dim1*(j2+dim2*(j3+dim3*j4))] = unsorted[j4+dim4*(j3+dim3*(j2+dim2*j1))] * factor;

		pA = unsorted + j4+dim4*(j3+dim3*(j2+dim2*j1));
		pB = sorted   + j1+dim1*(j2+dim2*(j3+dim3*j4));
		x = _mm_loadu_pd(pA);
		x = _mm_mul_pd(x,fac_vector);
		y = _mm_loadu_pd(pA + N2);
		y = _mm_mul_pd(y,fac_vector);
		z = _mm_shuffle_pd( x, y, 0);
		w = _mm_shuffle_pd( x, y, 3);
		_mm_storeu_pd(pB,z);
		_mm_storeu_pd(pB + N1,w);

                }
            }
        }
    }
    /* pluto end */
    return;
    }

