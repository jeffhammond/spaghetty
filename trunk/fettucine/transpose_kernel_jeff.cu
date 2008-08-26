/*
 * My heavily modified version of the NVIDIA transpose code.
 */

/*
 * GPU Code
 */

#ifndef _TRANSPOSE_KERNEL_H_
#define _TRANSPOSE_KERNEL_H_

// Thread block size
#define BLOCK_SIZE 8

/*
__global__ void transpose_jeff(float *odata, float* idata,
                               const unsigned int dim_1, const unsigned int dim_2,
                               const unsigned int dim_3, const unsigned int dim_4)
{

	unsigned int bdx = blockDim.x;
	unsigned int bdy = blockDim.y;

        unsigned int bix = blockIdx.x;
        unsigned int biy = blockIdx.y;

        unsigned int tix = threadIdx.x;
        unsigned int tiy = threadIdx.y;
        unsigned int tiz = threadIdx.z;

	unsigned int index_in,index_out;

	for (unsigned int j3 = 0; j3 < dim_3; ++j3){
		for (unsigned int j2 = 0; j2 < dim_2; ++j2){
			for (unsigned int j1 = 0; j1 < dim_1; ++j1){
				for (unsigned int j4 = 0; j4 < dim_4; ++j4){
					index_in  = j4 + dim_4*j3 + dim_4*dim_3*j2 + dim_4*dim_3*dim_2*j1;
					index_out = j1 + dim_1*j2 + dim_1*dim_2*j3 + dim_1*dim_2*dim_3*j4;
					odata[index_out] = idata[index_in];
				}
			}
		}
	}
}
*/

__global__ void transpose_jeff(float *odata, float* idata,
                               const unsigned int dim_1, const unsigned int dim_2,
                               const unsigned int dim_3, const unsigned int dim_4)
{

	unsigned int j1,j2,j3,j4;

        __shared__ float block[BLOCK_SIZE][BLOCK_SIZE+1];

        for (j3 = 0; j3 < dim_3; ++j3){
                for (j2 = 0; j2 < dim_2; ++j2){

/***************************************************************************/

        // read the matrix tile into shared memory
        j1 = blockIdx.x * BLOCK_SIZE + threadIdx.x;
        j4 = blockIdx.y * BLOCK_SIZE + threadIdx.y;
        if((j1 < dim_1) && (j4 < dim_4))
        {
                //unsigned int index_in = j4 * dim_1 + j1;
                unsigned int index_in = j4 + dim_4*j3 + dim_4*dim_3*j2 + dim_4*dim_3*dim_2*j1;
                block[threadIdx.y][threadIdx.x] = idata[index_in];
        }

        __syncthreads();

        // write the transposed matrix tile to global memory
        j1 = blockIdx.x * BLOCK_SIZE + threadIdx.y;
        j4 = blockIdx.y * BLOCK_SIZE + threadIdx.x;
        if((j4 < dim_4) && (j1 < dim_1))
        {
                //unsigned int index_out = j1 * dim_4 + j4;
                unsigned int index_out = j1 + dim_1*j2 + dim_1*dim_2*j3 + dim_1*dim_2*dim_3*j4;
                odata[index_out] = block[threadIdx.x][threadIdx.y];
        }

/***************************************************************************/

		}
	}
}

/*
__global__ void transpose_jeff(float *odata, float* idata,
                               const unsigned int dim_1, const unsigned int dim_2,
                               const unsigned int dim_3, const unsigned int dim_4)
{

    unsigned int j1,j2,j3,j4;

    // Shared memory for sub-blocks
    __shared__ float ishare[BLOCK_SIZE][BLOCK_SIZE][BLOCK_SIZE][BLOCK_SIZE];
    __shared__ float oshare[BLOCK_SIZE][BLOCK_SIZE][BLOCK_SIZE][BLOCK_SIZE];

    j2 = blockIdx.x * blockDim.x + threadIdx.x;
    j3 = blockIdx.y * blockDim.y + threadIdx.y;

    for (jj1 = 0; jj1 < dim_1; jj1 += BLOCK_SIZE){
      for (jj4 = 0; jj4 < dim_4; jj4 += BLOCK_SIZE){



        // Load the matrices from device memory to shared memory; each thread loads one element of each matrix
        ishare[j1][j2][j3][j4] = idata[j1 + dim_1*j2 + dim_1*dim_2*j3 + dim_1*dim_2*dim_3*j4];

        // Synchronize to make sure the matrices are loaded
        __syncthreads();




        // Synchronize to make sure that the preceding computation is done before loading new sub-matrices
        __syncthreads();
      }
    }
    // Synchronize to make sure everything finishes
    __syncthreads();

}
*/

#endif // _TRANSPOSE_KERNEL_H_
