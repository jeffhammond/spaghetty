/*
 * My heavily modified version of the NVIDIA transpose code.
 */

#ifndef _TRANSPOSE_KERNEL_H_
#define _TRANSPOSE_KERNEL_H_

// Thread block size
#define BLOCK_SIZE 16
// Algorithm to use
#define TEST

#ifdef TEST
__global__ void transpose_jeff(float *odata, float* idata,
                               const unsigned int dim_1, const unsigned int dim_2,
                               const unsigned int dim_3, const unsigned int dim_4)
{
        unsigned int j1,j2,j3,j4;

        __shared__ float block[BLOCK_SIZE][BLOCK_SIZE];

	for (j1 = 0; j1 < dim_1; ++j1){
		for (j2 = 0; j2 < dim_2; ++j2){

			// read the matrix tile into shared memory
			j3 = blockIdx.x * BLOCK_SIZE + threadIdx.x;
			j4 = blockIdx.y * BLOCK_SIZE + threadIdx.y;
			if((j3 < dim_3) && (j4 < dim_4)){
				unsigned int index_in = j4 + dim_4*j3 + dim_4*dim_3*j2 + dim_4*dim_3*dim_2*j1;
				block[threadIdx.y][threadIdx.x] = idata[index_in];
			}

			__syncthreads();

			// write the transposed matrix tile to global memory
			j3 = blockIdx.x * BLOCK_SIZE + threadIdx.y;
			j4 = blockIdx.y * BLOCK_SIZE + threadIdx.x;
			if((j3 < dim_3) && (j4 < dim_4)){
				unsigned int index_out = j1 + dim_1*j2 + dim_1*dim_2*j3 + dim_1*dim_2*dim_3*j4;
				odata[index_out] = block[threadIdx.x][threadIdx.y];
			}

			__syncthreads();

		}
	}
}
#endif

/* This version works but is slow than the CPU but no small amount */
#ifdef WORKS
__global__ void transpose_jeff(float *odata, float* idata,
                               const unsigned int dim_1, const unsigned int dim_2,
                               const unsigned int dim_3, const unsigned int dim_4)
{

	unsigned int j1,j2,j3,j4;

        __shared__ float block[BLOCK_SIZE][BLOCK_SIZE+1];

        for (j3 = 0; j3 < dim_3; ++j3){
                for (j2 = 0; j2 < dim_2; ++j2){


		        // read the matrix tile into shared memory
		        j1 = blockIdx.x * BLOCK_SIZE + threadIdx.x;
		        j4 = blockIdx.y * BLOCK_SIZE + threadIdx.y;
		        if((j1 < dim_1) && (j4 < dim_4)){
		                //unsigned int index_in = j4 * dim_1 + j1;
		                unsigned int index_in = j4 + dim_4*j3 + dim_4*dim_3*j2 + dim_4*dim_3*dim_2*j1;
		                block[threadIdx.y][threadIdx.x] = idata[index_in];
		        }

		        __syncthreads();

		        // write the transposed matrix tile to global memory
		        j1 = blockIdx.x * BLOCK_SIZE + threadIdx.y;
		        j4 = blockIdx.y * BLOCK_SIZE + threadIdx.x;
		        if((j4 < dim_4) && (j1 < dim_1)){
		                //unsigned int index_out = j1 * dim_4 + j4;
		                unsigned int index_out = j1 + dim_1*j2 + dim_1*dim_2*j3 + dim_1*dim_2*dim_3*j4;
		                odata[index_out] = block[threadIdx.x][threadIdx.y];
		        }

		        __syncthreads();

		}
	}
}
#endif

/* This is the stupid version which uses only one thread */
#ifdef STUPID
__global__ void transpose_jeff(float *odata, float* idata,
                               const unsigned int dim_1, const unsigned int dim_2,
                               const unsigned int dim_3, const unsigned int dim_4)
{

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
#endif

#endif // _TRANSPOSE_KERNEL_H_
