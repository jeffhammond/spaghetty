        subroutine transpose_3412_loop_1324(unsorted,sorted,
     &                           dim1,dim2,dim3,dim4,factor)
        implicit none
        integer dim1,dim2,dim3,dim4
        integer j1,j2,j3,j4
        double precision sorted(dim1*dim2*dim3*dim4)
        double precision unsorted(dim1*dim2*dim3*dim4)
        double precision factor
        do j1 = 1,dim1
         do j3 = 1,dim3
          do j2 = 1,dim2,4
           do j4 = 1,dim4,4
            sorted( 0+j2+dim2*(j1-1+dim1*(j4-1+dim4*(j3-1))) ) = factor*unsorted( 0+j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))) )
            sorted( 0+j2+dim2*(j1-1+dim1*(j4+0+dim4*(j3-1))) ) = factor*unsorted( 1+j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))) )
            sorted( 0+j2+dim2*(j1-1+dim1*(j4+1+dim4*(j3-1))) ) = factor*unsorted( 2+j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))) )
            sorted( 0+j2+dim2*(j1-1+dim1*(j4+2+dim4*(j3-1))) ) = factor*unsorted( 3+j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))) )
            
            sorted( 1+j2+dim2*(j1-1+dim1*(j4-1+dim4*(j3-1))) ) = factor*unsorted( 0+j4+dim4*(j3-1+dim3*(j2+0+dim2*(j1-1))) )
            sorted( 1+j2+dim2*(j1-1+dim1*(j4+0+dim4*(j3-1))) ) = factor*unsorted( 1+j4+dim4*(j3-1+dim3*(j2+0+dim2*(j1-1))) )
            sorted( 1+j2+dim2*(j1-1+dim1*(j4+1+dim4*(j3-1))) ) = factor*unsorted( 2+j4+dim4*(j3-1+dim3*(j2+0+dim2*(j1-1))) )
            sorted( 1+j2+dim2*(j1-1+dim1*(j4+2+dim4*(j3-1))) ) = factor*unsorted( 3+j4+dim4*(j3-1+dim3*(j2+0+dim2*(j1-1))) )
            
            sorted( 2+j2+dim2*(j1-1+dim1*(j4-1+dim4*(j3-1))) ) = factor*unsorted( 0+j4+dim4*(j3-1+dim3*(j2+1+dim2*(j1-1))) )
            sorted( 2+j2+dim2*(j1-1+dim1*(j4+0+dim4*(j3-1))) ) = factor*unsorted( 1+j4+dim4*(j3-1+dim3*(j2+1+dim2*(j1-1))) )
            sorted( 2+j2+dim2*(j1-1+dim1*(j4+1+dim4*(j3-1))) ) = factor*unsorted( 2+j4+dim4*(j3-1+dim3*(j2+1+dim2*(j1-1))) )
            sorted( 2+j2+dim2*(j1-1+dim1*(j4+2+dim4*(j3-1))) ) = factor*unsorted( 3+j4+dim4*(j3-1+dim3*(j2+1+dim2*(j1-1))) )
            
            sorted( 3+j2+dim2*(j1-1+dim1*(j4-1+dim4*(j3-1))) ) = factor*unsorted( 0+j4+dim4*(j3-1+dim3*(j2+2+dim2*(j1-1))) )
            sorted( 3+j2+dim2*(j1-1+dim1*(j4+0+dim4*(j3-1))) ) = factor*unsorted( 1+j4+dim4*(j3-1+dim3*(j2+2+dim2*(j1-1))) )
            sorted( 3+j2+dim2*(j1-1+dim1*(j4+1+dim4*(j3-1))) ) = factor*unsorted( 2+j4+dim4*(j3-1+dim3*(j2+2+dim2*(j1-1))) )
            sorted( 3+j2+dim2*(j1-1+dim1*(j4+2+dim4*(j3-1))) ) = factor*unsorted( 3+j4+dim4*(j3-1+dim3*(j2+2+dim2*(j1-1))) )
           enddo
          enddo
         enddo
        enddo
        return
        end
