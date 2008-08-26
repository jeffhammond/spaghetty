/*
 * My heavily modified version of the NVIDIA transpose code.
 */

/*
 * CPU Code
 */

////////////////////////////////////////////////////////////////////////////////
// export C interface
extern "C"
void computeGold( float* reference, float* idata,
                  const unsigned int dim_1, const unsigned int dim_2,
                  const unsigned int dim_3, const unsigned int dim_4 );

////////////////////////////////////////////////////////////////////////////////
//! Compute reference data set
////////////////////////////////////////////////////////////////////////////////
void
computeGold( float* reference, float* idata,
            const unsigned int dim_1, const unsigned int dim_2,
            const unsigned int dim_3, const unsigned int dim_4 )
{
    for( unsigned int j3 = 0; j3 < dim_3; ++j3) {
      for( unsigned int j2 = 0; j2 < dim_2; ++j2) {
        for( unsigned int j4 = 0; j4 < dim_4; ++j4) {
          for( unsigned int j1 = 0; j1 < dim_1; ++j1) {
            unsigned int old_offset = j4 + dim_4 * ( j3 + dim_3 * ( j2 + dim_2 * j1 ) );
            unsigned int new_offset = j1 + dim_1 * ( j2 + dim_2 * ( j3 + dim_3 * j4 ) );
            reference[new_offset] = idata[old_offset];
          }
        }  
      }
    }  
}

