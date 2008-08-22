/*
 * This began as code that NVIDIA had a copyright on but about the only
 * things that are the same are the include files, the filenames themselves,
 * and the commends.  If there is a problem with this, let me know.
 *
 * Jeff Hammond, August 2008
 */

/*
 * CPU code
 */

extern "C" 
void computeGold( float* reference, float* idata, 
                  const unsigned int dim1, const unsigned int dim2,
                  const unsigned int dim3, const unsigned int dim4 );

void computeGold( float* reference, float* idata, 
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

