        subroutine transpose_2d_kernel(before,after,dimX,dimY,factor)
        implicit none
        integer dimX,dimY
        integer I,J,i,j
        double precision before(dimX,dimY)
        double precision after(dimY,dimX)
        double precision factor
        do I = 1,dimX,8
         do J = 1,dimY,8
          do i = 1,8,1
           do j = 1,8,1
           after(J+j,I+i) = before(I+i,J+j)*factor
c           after(J+1,I+0) = before(I+0,J+1)*factor
c           after(J+2,I+0) = before(I+0,J+2)*factor
c           after(J+3,I+0) = before(I+0,J+3)*factor
c           after(J+4,I+0) = before(I+0,J+4)*factor
c           after(J+5,I+0) = before(I+0,J+5)*factor
c           after(J+6,I+0) = before(I+0,J+6)*factor
c           after(J+7,I+0) = before(I+0,J+7)*factor
c           after(J+0,I+1) = before(I+1,J+0)*factor
c           after(J+1,I+1) = before(I+1,J+1)*factor
c           after(J+2,I+1) = before(I+1,J+2)*factor
c           after(J+3,I+1) = before(I+1,J+3)*factor
c           after(J+4,I+1) = before(I+1,J+4)*factor
c           after(J+5,I+1) = before(I+1,J+5)*factor
c           after(J+6,I+1) = before(I+1,J+6)*factor
c           after(J+7,I+1) = before(I+1,J+7)*factor
c           after(J+0,I+2) = before(I+2,J+0)*factor
c           after(J+1,I+2) = before(I+2,J+1)*factor
c           after(J+2,I+2) = before(I+2,J+2)*factor
c           after(J+3,I+2) = before(I+2,J+3)*factor
c           after(J+4,I+2) = before(I+2,J+4)*factor
c           after(J+5,I+2) = before(I+2,J+5)*factor
c           after(J+6,I+2) = before(I+2,J+6)*factor
c           after(J+7,I+2) = before(I+2,J+7)*factor
c           after(J+0,I+3) = before(I+3,J+0)*factor
c           after(J+1,I+3) = before(I+3,J+1)*factor
c           after(J+2,I+3) = before(I+3,J+2)*factor
c           after(J+3,I+3) = before(I+3,J+3)*factor
c           after(J+4,I+3) = before(I+3,J+4)*factor
c           after(J+5,I+3) = before(I+3,J+5)*factor
c           after(J+6,I+3) = before(I+3,J+6)*factor
c           after(J+7,I+3) = before(I+3,J+7)*factor
           enddo
          enddo
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
