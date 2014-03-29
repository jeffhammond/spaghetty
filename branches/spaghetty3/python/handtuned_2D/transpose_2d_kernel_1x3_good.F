        subroutine transpose_2d_kernel(before,after,dimX,dimY,factor)
        implicit none
        integer dimX,dimY
        integer i,j
        double precision before(dimX,dimY)
        double precision after(dimY,dimX)
        double precision factor
        do i = 1,dimX,1
         do j = 1,dimY,3
           after(j+0,i+0) = before(i+0,j+0)*factor
           after(j+1,i+0) = before(i+0,j+1)*factor
           after(j+2,i+0) = before(i+0,j+2)*factor
c           after(j+3,i+0) = before(i+0,j+3)*factor
c           after(j+0,i+1) = before(i+1,j+0)*factor
c           after(j+1,i+1) = before(i+1,j+1)*factor
c           after(j+2,i+1) = before(i+1,j+2)*factor
c           after(j+3,i+1) = before(i+1,j+3)*factor
c           after(j+0,i+2) = before(i+2,j+0)*factor
c           after(j+1,i+2) = before(i+2,j+1)*factor
c           after(j+2,i+2) = before(i+2,j+2)*factor
c           after(j+3,i+2) = before(i+2,j+3)*factor
         enddo
        enddo
        return
        end

c
c    NOTES
c
c    (X,Y) notation
c
c    (1,3) blocking works very well
c    (3,1) blocking works almost as well as (1,3)
c
c
c
c
c
c
c
c
c
