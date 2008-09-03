#include <math.h>
#include <assert.h>
#include <omp.h>
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))
    void transpose_1234_loop_1234_( double *unsorted, double *sorted,
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




 int c1, c2, c3, c4;
 register int lb, ub, lb1, ub1, lb2, ub2;
 register int lbv, ubv;

for (c1=0;c1<=dim1-1;c1++) {
  for (c2=0;c2<=dim2-1;c2++) {
    for (c3=0;c3<=dim3-1;c3++) {
      for (c4=0;c4<=dim4-1;c4++) {
        {old_offset=dim4*(dim3*(dim2*(c1)+c2)+c3)+c4;} ;
        {new_offset=dim4*(dim3*(dim2*(c1)+c2)+c3)+c4;} ;
        {sorted[((int)floor(new_offset))]=unsorted[((int)floor(old_offset))]*factor;} ;
      }
    }
  }
}
    return;
    }

