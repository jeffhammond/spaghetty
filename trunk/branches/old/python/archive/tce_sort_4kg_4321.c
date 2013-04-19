#include <stdio.h>


/*
 * NOTE: 
 *        A and B must have nDim dimensions
 *        The size of A (dim0 * dim1 * ....  * dimN) must equal the 
 *           size of B
 *        aSize and perm must be single dimension arrys of size nDim
 *        aSize must contain the size of each dimension of A
 *        perm must contain the dimension permutation (i.e, let A has dimension sequence
 *         [0, 1, 2, 3] and size [2, 3, 4, 5]. The permutation array [2, 1, 3, 0] will
 *         cause nDTranspose to produce an array of dimension [4, 3, 5, 2]
 *
 */

void tce_sort_4kg_4321__(double * A, double * B, int * dim1, int * dim2, int * dim3, int * dim4, double * factor)
{
	int i,j,k,l;

	double *bPtr = B;
	double *aPtr[4];
	
        int d1 = (*dim1);
        int d2 = (*dim2);
        int d3 = (*dim3);
        int d4 = (*dim4);

	aPtr[0] = A;
	aPtr[1] = A;
	aPtr[2] = A;
	aPtr[3] = A;

	for (i = 0; i < d1; i++){
		aPtr[2] = aPtr[3];
		for (j = 0; j < d2; j++){
			aPtr[1] = aPtr[2];
			for (k = 0; k < d3; k++){
				aPtr[0] = aPtr[1];
				for (l = 0; l < d4; l++){
					*bPtr++ = *aPtr[0];
					aPtr[0] += d1*d2*d3;
				}
				aPtr[1] += d1*d2;
			}
			aPtr[2] += d1;
		}
		aPtr[3] += 1;
	}

}


