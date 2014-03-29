#ifndef _TRANSPOSE_KERNEL_H_
#define _TRANSPOSE_KERNEL_H_

#define BLOCK_SIZE 16

__global__ void transpose(float *odata, float *idata,
                          const unsigned int dim_1, const unsigned int dim_2,
                          const unsigned int dim_3, const unsigned int dim_4)
{
	__shared__ float block[BLOCK_SIZE][BLOCK_SIZE+1];
	

        // width  -> dim_3
        // height -> dim_4

	// read the matrix tile into shared memory
	unsigned int xIndex = blockIdx.x * BLOCK_SIZE + threadIdx.x;
	unsigned int yIndex = blockIdx.y * BLOCK_SIZE + threadIdx.y;
	if((xIndex < dim_3) && (yIndex < dim_4))
	{
		unsigned int index_in = yIndex * dim_3 + xIndex;
		block[threadIdx.y][threadIdx.x] = idata[index_in];
	}

	__syncthreads();

	// write the transposed matrix tile to global memory
	xIndex = blockIdx.y * BLOCK_SIZE + threadIdx.x;
	yIndex = blockIdx.x * BLOCK_SIZE + threadIdx.y;
	if((xIndex < dim_4) && (yIndex < dim_3))
	{
		unsigned int index_out = yIndex * dim_4 + xIndex;
		odata[index_out] = block[threadIdx.x][threadIdx.y];
	}
}


__global__ void transpose_naive(float *odata, float* idata,
                                const unsigned int dim_1, const unsigned int dim_2,
                                const unsigned int dim_3, const unsigned int dim_4)
{
   unsigned int xIndex = blockDim.x * blockIdx.x + threadIdx.x;
   unsigned int yIndex = blockDim.y * blockIdx.y + threadIdx.y;
   
   if (xIndex < dim_3 && yIndex < dim_4)
   {
       unsigned int index_in  = xIndex + dim_3 * yIndex;
       unsigned int index_out = yIndex + dim_4 * xIndex;
       odata[index_out] = idata[index_in]; 
   }
}

#endif // _TRANSPOSE_KERNEL_H_
