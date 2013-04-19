        PROGRAM ARRAYTEST
        REAL*8 before(32,32,32,32)
        REAL*8 after_jeff(32,32,32,32)
        REAL*8 after_hirata(32,32,32,32)
        REAL*8 factor
        REAL*8 Tstart,Tfinish,Thirata,Tjeff
        REAL*8 Tspeedup,Tbest
        INTEGER*4 i,j,k,l
        INTEGER*4 aSize(4)
        INTEGER*4 perm(4)
        INTEGER*4 fastest(4)
        aSize(1) = 32
        aSize(2) = 32
        aSize(3) = 32
        aSize(4) = 32
        perm(1) = 1
        perm(2) = 2
        perm(3) = 3
        perm(4) = 4
        DO 70 i = 1, 32
          DO 60 j = 1, 32
            DO 50 k = 1, 32
              DO 40 l = 1, 32
                before(i,j,k,l) = l + k*10 + j*100 + i*1000
40            CONTINUE
50          CONTINUE
60        CONTINUE
70      CONTINUE
        factor = 1.0
        Tbest=999999.0
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 30 i = 1, 20
          CALL tce_sort_4(before, after_hirata,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    perm(1), perm(2), perm(3), perm(4), factor)
30      CONTINUE
        CALL CPU_TIME(Tfinish)
        Thirata=(Tfinish-Tstart)
        write(6,*) "TESTING TRANPOSE TYPE 1234"
        write(6,*) "==================="
        write(6,*) "The compilation flags were:"
        write(6,*) "-g"
        write(6,*) "-O3"
        write(6,*) "-xT"
        write(6,*) "-march=core2"
        write(6,*) "-mtune=core2"
        write(6,*) "-funroll-loops"
        write(6,*) "-align"
        write(6,*) "-c"
        write(6,*) "==================="
        write(6,*) "Hirata Reference = ",Thirata,"seconds"
        write(6,1001) "Algorithm","Jeff","Speedup","Best","Best Speedup"
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        write(6,*) "*** START TIMING THE SUBROUTINE ***"
        DO 101 i = 1, 20
          CALL trans_a4d_1234_loop_1234(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
101     CONTINUE
        write(6,*) "*** FINISHED TIMING THE SUBROUTINE ***"
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=1
          fastest(2)=2
          fastest(3)=3
          fastest(4)=4
        endif
        write(6,1100) "  1 Loop 1234 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 9970 i = 1, 32
          DO 9960 j = 1, 32
            DO 9950 k = 1, 32
              DO 9940 l = 1, 32
          IF (after_jeff(i,j,k,l).ne.after_hirata(i,j,k,l)) THEN
            PRINT*,"jeff error ",i,j,k,l,after_jeff(i,j,k,l),after_hirata(i,j,k,l)
          ENDIF
9940            CONTINUE
9950          CONTINUE
9960        CONTINUE
9970      CONTINUE
        write(6,1020) "The best loop order is:",
     &             fastest(1),fastest(2),fastest(3),fastest(4)
        write(6,1030) "The best time is:",Tbest
        write(6,1030) "The best speedup is:",Thirata/Tbest
        STOP
 1001 format(1x,a13,a12,a15,a9,a18)
 1020 format(1x,a30,8x,4i1)
 1030 format(1x,a30,1f12.5)
 1100 format(1x,a16,4f12.5)
      END
