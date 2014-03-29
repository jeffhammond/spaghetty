c----------------------------------------------------------------------c
#define DIM_X 600
#define DIM_Y 600
#define TIMINGS 200
c----------------------------------------------------------------------c
        PROGRAM TRANSPOSE
c----------------------------------------------------------------------c
        REAL*8 before(DIM_X,DIM_Y)
        REAL*8 after_jeff(DIM_X,DIM_Y)
        REAL*8 after_omp(DIM_X,DIM_Y)
        REAL*8 after_hirata(DIM_X,DIM_Y)
        REAL*8 after_saday(DIM_X,DIM_Y)
        REAL*8 fac
        REAL*4 Tstart,Tfinish,Thirata,Tjeff,Tomp,Tsaday,Tspeedup
        INTEGER*4 i,j
        LOGICAL correct
c----------------------------------------------------------------------c
c       Initialize the array to be transposed
c----------------------------------------------------------------------c
        DO 10 j = 1, DIM_X
          DO 20 i = 1, DIM_Y
            before(i,j) = i+1000*j
20        CONTINUE
10      CONTINUE
        fac = 1.0
c----------------------------------------------------------------------c
c       Hirata's basic version
c----------------------------------------------------------------------c
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 30 i = 1, TIMINGS
          CALL tce_sort_2(before,after_hirata,DIM_X,DIM_Y,2,1,fac)
30      CONTINUE
        CALL CPU_TIME(Tfinish)
        Thirata=(Tfinish-Tstart)
        PRINT*,"Hirata  = ",Thirata
c----------------------------------------------------------------------c
c       Saday's blocked, SSE2 version
c----------------------------------------------------------------------c
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 40 i = 1, TIMINGS
          CALL saday_sort_2(before,after_saday,DIM_X,DIM_Y,2,1,fac)
40      CONTINUE
        CALL CPU_TIME(Tfinish)
        Tsaday=(Tfinish-Tstart)
        PRINT*,"Saday   = ",Tsaday
c----------------------------------------------------------------------c
c       Jeff's blocked version
c----------------------------------------------------------------------c
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 50 i = 1, TIMINGS
          CALL transpose_2d_kernel(before,after_jeff,DIM_X,DIM_Y,fac)
50      CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        PRINT*,"Jeff    = ",Tjeff
c----------------------------------------------------------------------c
c       OpenMP version
c----------------------------------------------------------------------c
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 60 i = 1, TIMINGS
          CALL transpose_2d_kernel_omp(before,after_omp,DIM_X,DIM_Y,fac)
60      CONTINUE
        CALL CPU_TIME(Tfinish)
        Tomp=(Tfinish-Tstart)
        PRINT*,"OpenMP  = ",Tomp
c----------------------------------------------------------------------c
c       Check Saday's version for correctness
c----------------------------------------------------------------------c
        write(6,2000) "Saday's"
        DO 200 j = 1, DIM_X
          DO 210 i = 1, DIM_Y
            IF (after_saday(i,j).ne.after_hirata(i,j)) THEN
              write(6,1000) "error at",i,j,after_saday(i,j),
     &                                     after_hirata(i,j)
            ELSE
              correct=.true.
            ENDIF
210       CONTINUE
200     CONTINUE
        if (correct) write(6,3000)
c----------------------------------------------------------------------c
c       Check Jeff's version for correctness
c----------------------------------------------------------------------c
        write(6,2000) "Jeff's"
        DO 300 j = 1, DIM_X
          DO 310 i = 1, DIM_Y
            IF (after_jeff(i,j).ne.after_hirata(i,j)) THEN
              write(6,1000) "error at",i,j,after_jeff(i,j),
     &                                     after_hirata(i,j)
            ELSE
              correct=.true.
            ENDIF
310       CONTINUE
300     CONTINUE
        if (correct) write(6,3000)
c----------------------------------------------------------------------c
c       Check OpenMP version for correctness
c----------------------------------------------------------------------c
        write(6,2000) "OpenMP"
        DO 400 j = 1, DIM_X
          DO 410 i = 1, DIM_Y
            IF (after_omp(i,j).ne.after_hirata(i,j)) THEN
              write(6,1000) "error at",i,j,after_omp(i,j),
     &                                     after_hirata(i,j)
            ELSE
              correct=.true.
            ENDIF
410       CONTINUE
400     CONTINUE
        if (correct) write(6,3000)
c----------------------------------------------------------------------c
1000    format(1x,a10,2i6,2f18.5)
2000    format("Checking for errors in ",a7," algorithm... ",\)
3000    format("None")
c----------------------------------------------------------------------c
        STOP
      END



#if defined(JEFF)
        subroutine transpose_2d_kernel(before,after,dimX,dimY,fac)
        implicit none
        integer dimX,dimY
        integer i,j
        double precision before(dimX,dimY)
        double precision after(dimY,dimX)
        double precision fac
        do i = 1,dimX,2
         do j = 1,dimY,2
           after(j,i) = before(i,j)*fac
           after(j+1,i) = before(i,j+1)*fac
           after(j,i+1) = before(i+1,j)*fac
           after(j+1,i+1) = before(i+1,j+1)*fac
         enddo
        enddo
        return
        end
#endif


#if defined(HIRATA)
      subroutine tce_sort_2(unsorted,sorted,a,b,i,j,fac)
      implicit none
      integer a,b
      integer i,j
      integer id(2),jd(2),ia,ib,j1,j2
      double precision sorted(a*b)
      double precision unsorted(a*b)
      double precision fac
      ia = 0
      jd(1) = a
      jd(2) = b
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        ia = ia + 1
        ib = id(j)+jd(j)*(id(i)-1)
        sorted(ib) = unsorted(ia) * fac
       enddo
      enddo
      return
      end
#endif
