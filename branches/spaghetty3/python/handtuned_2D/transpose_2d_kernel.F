#define XBLOCK 8
#define YBLOCK 8 
        subroutine transpose_2d_kernel(before,after,dimX,dimY,factor)
        implicit none
        integer dimX,dimY
        integer iii,jjj,ii,jj
        double precision before(dimX,dimY)
        double precision after(dimY,dimX)
        double precision factor
        do iii = 1,dimX,XBLOCK
         do jjj = 1,dimY,YBLOCK
          do ii = 1,XBLOCK,1
           do jj = 1,YBLOCK,1
            after(jjj+jj-1,iii+ii-1) = before(iii+ii-1,jjj+jj-1)*factor
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
