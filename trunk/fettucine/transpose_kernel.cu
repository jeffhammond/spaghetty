/*
 * This began as code that NVIDIA had a copyright on but about the only
 * things that are the same are the include files, the filenames themselves,
 * and the commends.  If there is a problem with this, let me know.
 *
 * Jeff Hammond, August 2008
 */

/*
 * GPU code
 */

#ifndef _TRANSPOSE_KERNEL_H_
#define _TRANSPOSE_KERNEL_H_

__global__ void transpose(float *odata, float* idata, int dim1, int dim2, int dim3, int dim4)
{

	unsigned int j1 = blockDim.x * blockIdx.x + threadIdx.x;
	unsigned int j2 = blockDim.y * blockIdx.y + threadIdx.y;
   
	unsigned int index_in,index_out;

	if (j1 < dim1 && j2 < dim2){
		for (int j3 = 0; j3 < dim3; ++j3){
			for (int j4 = 0; j4 < dim4; ++j4){
				index_in  = j4 + dim4*j3 + dim4*dim3*j2 + dim4*dim3*dim2*j1;
				index_out = j1 + dim1*j2 + dim1*dim2*j3 + dim1*dim2*dim3*j4;
				odata[index_out] = idata[index_in];
			}
		}
	}
}

#endif // _TRANSPOSE_KERNEL_H_
