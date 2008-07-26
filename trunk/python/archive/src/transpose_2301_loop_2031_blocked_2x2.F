        subroutine transpose_2301_loop_2031_blocked_2x2(unsorted,sorted,
     &                dim2,dim3,dim0,dim1,factor)
        implicit none
        integer dim2,dim3,dim0,dim1
        integer j2,j3,j0,j1
        double precision sorted(dim2*dim3*dim0*dim1)
        double precision unsorted(dim2*dim3*dim0*dim1)
        double precision factor
        do j2 = 1,dim2
         do j0 = 1,dim0
          do j3 = 1,dim3,2
           do j1 = 1,dim1,2
            sorted(j1+dim1*(j0-1+dim0*(j3-1+dim3*(j2-1)))) = factor*
     &        unsorted(j1+dim1*(j3-1+dim3*(j0-1+dim0*(j2-1))))
            sorted(j1+dim1*(j0-1+dim0*(j3-1+dim3*(j2-1)))) = factor*
     &        unsorted(j1+dim1*(j3-1+dim3*(j0-1+dim0*(j2-1))))
            sorted(j1+dim1*(j0-1+dim0*(j3-1+dim3*(j2-1)))) = factor*
     &        unsorted(j1+dim1*(j3-1+dim3*(j0-1+dim0*(j2-1))))
            sorted(j1+dim1*(j0-1+dim0*(j3-1+dim3*(j2-1)))) = factor*
     &        unsorted(j1+dim1*(j3-1+dim3*(j0-1+dim0*(j2-1))))
           enddo
          enddo
         enddo
        enddo
        return
        end
