c#define ONE y
#define TWO y

#if defined(ONE)
        subroutine transpose_2d_kernel_omp(before,after,dimX,dimY,fac)
        implicit none
        integer dimX,dimY
        integer iii,jjj
        double precision before(dimX,dimY)
        double precision after(dimY,dimX)
        double precision fac
!$OMP PARALLEL DO SHARED(after,before) PRIVATE(iii,jjj)
        do iii = 1,dimX
         do jjj = 1,dimY
            after(jjj,iii) = before(iii,jjj)*fac
         enddo
        enddo
!$OMP END PARALLEL DO
        return
        end
#endif



#if defined(TWO)
        subroutine transpose_2d_kernel_omp(before,after,dimX,dimY,fac)
        implicit none
        integer dimX,dimY
        integer iii,jjj
        double precision before(dimX,dimY)
        double precision after(dimY,dimX)
        double precision fac
!$OMP DO SCHEDULE(STATIC,1)
        do iii = 1,dimX
         do jjj = 1,dimY
            after(jjj,iii) = before(iii,jjj)*fac
         enddo
        enddo
!$OMP END DO NOWAIT
        return
        end
#endif
