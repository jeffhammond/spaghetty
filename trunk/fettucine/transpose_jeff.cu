/*
 * My heavily modified version of the NVIDIA transpose code.
 */

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// includes, project
//#include <cutil.h>
#include "/opt/nvidia/cuda/common/inc/cutil.h"

// includes, kernels
#include <transpose_kernel_jeff.cu>

////////////////////////////////////////////////////////////////////////////////
// declaration, forward
void runTest( int argc, char** argv);
extern "C" void computeGold( float* reference, float* idata, 
                         const unsigned int size_a, const unsigned int size_b,
                         const unsigned int size_c, const unsigned int size_d );

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int
main( int argc, char** argv) 
{
    runTest( argc, argv);

    CUT_EXIT(argc, argv);
}


////////////////////////////////////////////////////////////////////////////////
//! Run a simple test for CUDA
////////////////////////////////////////////////////////////////////////////////
void
runTest( int argc, char** argv) 
{
    // number of runs to average timing over
    int numIterations = 8;
    // size of the matrix
#ifdef __DEVICE_EMULATION__
    const unsigned int size_a = 4;
    const unsigned int size_b = 4;
    const unsigned int size_c = 4;
    const unsigned int size_d = 4;
#else
    const unsigned int size = 8;
    const unsigned int size_a = size;
    const unsigned int size_b = size;
    const unsigned int size_c = size;
    const unsigned int size_d = size;
#endif
    // size of memory required to store the matrix
    const unsigned int mem_size = sizeof(float) * size_a * size_b * size_c * size_d;
    
    unsigned int timer;
    cutCreateTimer(&timer);

    CUT_DEVICE_INIT(argc, argv);

    // allocate host memory
    float* h_idata = (float*) malloc(mem_size);
    // initalize the memory
    unsigned int num=0;
    for( unsigned int i = 0; i < (size_a); ++i){
      for( unsigned int j = 0; j < (size_b); ++j){
        for( unsigned int k = 0; k < (size_c); ++k){
          for( unsigned int l = 0; l < (size_d); ++l){
            h_idata[num++] = (float) (i + j*10 + k*100 + l*1000);
          }
        }
      }
    }

    // allocate device memory
    float* d_idata;
    float* d_odata;
    CUDA_SAFE_CALL( cudaMalloc( (void**) &d_idata, mem_size));
    CUDA_SAFE_CALL( cudaMalloc( (void**) &d_odata, mem_size));

    // copy host memory to device
    CUDA_SAFE_CALL( cudaMemcpy( d_idata, h_idata, mem_size,
                                cudaMemcpyHostToDevice) );

    printf("Transposing a %d by %d by %d by %d matrix of floats...\n", size_a, size_b, size_c, size_d);

    // setup execution parameters
    dim3 dimBlock(8,8,8);
    dim3 dimGrid(size_a/dimBlock.x, size_b/dimBlock.y, size_c/dimBlock.z);

    // warmup so we don't time CUDA startup
    transpose_jeff<<< dimGrid, dimBlock >>>(d_odata, d_idata, size_a, size_b, size_c, size_d);

    // execute the kernel
    cutStartTimer(timer);
    for (int i = 0; i < numIterations; ++i){
        transpose_jeff<<< dimGrid, dimBlock >>>(d_odata, d_idata, size_a, size_b, size_c, size_d);
    }
    cudaThreadSynchronize();
    cutStopTimer(timer);
    float gpuTime = cutGetTimerValue(timer);

    printf("GPU transpose average time: %0.3f ms\n", gpuTime / numIterations);

    // check if kernel execution generated and error
    CUT_CHECK_ERROR("Kernel execution failed");

    // copy result from device to host
    float* h_odata = (float*) malloc(mem_size);
    CUDA_SAFE_CALL( cudaMemcpy( h_odata, d_odata, mem_size,
                                cudaMemcpyDeviceToHost) );

    // compute reference solution
    float* reference = (float*) malloc( mem_size);

    // execute the kernel
    cutResetTimer(timer);
    cutStartTimer(timer);
    for (int i = 0; i < numIterations; ++i){
         computeGold( reference, h_idata, size_a, size_b, size_c, size_d);
    }
    cutStopTimer(timer);
    float cpuTime = cutGetTimerValue(timer);

    printf("CPU transpose average time: %0.3f ms\n", cpuTime / numIterations);

    // check result

    if((size_a * size_b * size_c * size_d)<10001){
    printf("==================================================================\n");
    printf("                    Initial      Reference     OutputData\n");
    printf("==================================================================\n");
    for( unsigned int i = 0; i < (size_a); ++i){
      for( unsigned int j = 0; j < (size_b); ++j){
        for( unsigned int k = 0; k < (size_c); ++k){
          for( unsigned int l = 0; l < (size_d); ++l){
            printf("%3d %3d %3d %3d", i, j, k, l);
            printf("%14.7f",h_idata[i+size_b*(j+size_c*(k+size_d*l))]);
            printf("%14.7f",reference[i+size_b*(j+size_c*(k+size_d*l))]);
            printf("%14.7f\n",h_odata[i+size_b*(j+size_c*(k+size_d*l))]);
          }
        }
      }
    }
    }
    CUTBoolean res = cutComparef( reference, h_odata, size_a * size_b * size_c * size_d);
    printf("==================================================================\n");
    printf(    "Test %s\n", (1    == res)    ? "PASSED" : "FAILED");
    printf("==================================================================\n");

    printf("GPU transpose average time: %0.3f ms\n", gpuTime / numIterations);
    printf("CPU transpose average time: %0.3f ms\n", cpuTime / numIterations);
    printf("Averaged over %d runs\n", numIterations);

    // cleanup memory
    free(h_idata);
    free(h_odata);
    free( reference);
    CUDA_SAFE_CALL(cudaFree(d_idata));
    CUDA_SAFE_CALL(cudaFree(d_odata));
    CUT_SAFE_CALL(cutDeleteTimer(timer));
}
