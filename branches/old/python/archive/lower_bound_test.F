        PROGRAM THROUGHPUT
#include "mpif.h"
        REAL*8 before(40,40,40,40)
        REAL*8 after(40,40,40,40)
        REAL*8 X(1000,1000),Y(1000,1000)
        REAL*8 factor
        REAL*8 Tstart,Tfinish,Timing
        INTEGER*4 i,j,k,l,count
        INTEGER*4 ii,jj
        INTEGER ierror
        call mpi_init(ierror)
        call hpm_init()
        DO 70 i = 1, 40
          DO 60 j = 1, 40
            DO 50 k = 1, 40
              DO 40 l = 1, 40
                before(i,j,k,l) = l + k*10 + j*100 + i*1000
40            CONTINUE
50          CONTINUE
60        CONTINUE
70      CONTINUE
        factor = 1.0
        Tstart=0.0d0
        Tfinish=0.0d0
        DO 30 count = 1, 100
! flush cache
                do ii=1,1000
                  do jj=1,1000
                    X(jj,ii) = 1d0/(ii+jj)
                  enddo 
                enddo 
                do ii=1,1000
                  do jj=1,1000
                    Y(jj,ii) = 1d0/(ii+jj)
                  enddo 
                enddo 
                do ii=1,1000
                  do jj=1,1000
                    X(jj,ii) = 7d0*X(ii,jj)+X(jj,ii)
     &                       - 3d0*Y(ii,jj)+2d0*Y(jj,ii)
                  enddo 
                enddo 
! time throughput
        call hpm_start("throughput test")
        Tstart=rtc()
                DO 71 i = 1, 40
                DO 61 j = 1, 40
                DO 51 k = 1, 40
                DO 41 l = 1, 40
                        after(l,k,j,i) = factor*before(l,k,j,i)
41              CONTINUE
51              CONTINUE
61              CONTINUE
71              CONTINUE
        Tfinish=rtc()
        call hpm_stop("throughput test")
        Timing=Timing+(Tfinish-Tstart)
!
30      CONTINUE

        write(6,*) "throughput timing = ",Timing,"seconds"
        call hpm_print()
        call hpm_print_flops()
        call mpi_finalize(ierror)
        STOP
        END
