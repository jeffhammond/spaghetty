/*
 * Copyright 1993-2007 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */

/* Small Matrix transpose with Cuda (Example for a 16x16 matrix)
* Reference solution.
*/

////////////////////////////////////////////////////////////////////////////////
// export C interface
extern "C" 
void computeGold( float* reference, float* idata, 
                  const unsigned int dim1, const unsigned int dim2,
                  const unsigned int dim3, const unsigned int dim4 );

////////////////////////////////////////////////////////////////////////////////
//! Compute reference data set
////////////////////////////////////////////////////////////////////////////////
void
computeGold( float* reference, float* idata, 
            const unsigned int dim1, const unsigned int dim2,
            const unsigned int dim3, const unsigned int dim4 ) 
{
    for( unsigned int j3 = 0; j3 < dim3; ++j3) {
      for( unsigned int j2 = 0; j2 < dim2; ++j2) {
        for( unsigned int j4 = 0; j4 < dim4; ++j4) {
          for( unsigned int j1 = 0; j1 < dim1; ++j1) {
            unsigned int old_offset = j4 + dim4 * ( j3 + dim3 * ( j2 + dim2 * j1 ) );
            unsigned int new_offset = j1 + dim1 * ( j2 + dim2 * ( j3 + dim3 * j4 ) );
            reference[new_offset] = idata[old_offset];
          }
        }  
      }
    }  
}

