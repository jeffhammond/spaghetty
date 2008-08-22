/*
 * My heavily modified version of the NVIDIA transpose code.
 */

/*
 * GPU Code
 */

#ifndef _TRANSPOSE_KERNEL_H_
#define _TRANSPOSE_KERNEL_H_

__global__ void transpose(float *odata, float* idata,
                          const unsigned int dim_1, const unsigned int dim_2,
                          const unsigned int dim_3, const unsigned int dim_4)
{

	int bx = blockIdx.x;
	int by = blockIdx.y;
	int bz = blockIdx.z;

	// Thread index
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int tz = threadIdx.z;

	unsigned int j1,j2,j3,j4;
	unsigned int index_in,index_out;

	j3 = bx+tx;
	j2 = by+ty;
	j1 = bz+tz;

	if (j3 < dim_3){
	//for (j3 = 0; j3 < dim_3; ++j3){
		if (j2 < dim_2){
		//for (j2 = 0; j2 < dim_2; ++j2){
			if (j1 < dim_1){
			//for (j1 = 0; j1 < dim_1; ++j1){
				for (j4 = 0; j4 < dim_4; ++j4){
					index_in  = j4 + dim_4*j3 + dim_4*dim_3*j2 + dim_4*dim_3*dim_2*j1;
					index_out = j1 + dim_1*j2 + dim_1*dim_2*j3 + dim_1*dim_2*dim_3*j4;
					odata[index_out] = idata[index_in];
				}
			}
		}
	}
}

/*
__global__ void transpose(float *odata, float* idata,
                          const unsigned int dim_1, const unsigned int dim_2,
                          const unsigned int dim_3, const unsigned int dim_4)
{

	unsigned int j1 = blockDim.x * blockIdx.x + threadIdx.x;
	unsigned int j2 = blockDim.y * blockIdx.y + threadIdx.y;
   
	unsigned int index_in,index_out;

	if (j1 < dim_1 && j2 < dim_2){
		for (unsigned int j3 = 0; j3 < dim_3; ++j3){
			for (unsigned int j4 = 0; j4 < dim_4; ++j4){
				index_in  = j4 + dim_4*j3 + dim_4*dim_3*j2 + dim_4*dim_3*dim_2*j1;
				index_out = j1 + dim_1*j2 + dim_1*dim_2*j3 + dim_1*dim_2*dim_3*j4;
				odata[index_out] = idata[index_in];
			}
		}
	}
}
*/

#endif // _TRANSPOSE_KERNEL_H_
