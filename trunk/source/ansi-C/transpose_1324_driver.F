        PROGRAM ARRAYTEST
        REAL*8 before(32,32,32,32)
        REAL*8 after_jeff(1048576)
        REAL*8 after_hirata(1048576)
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
        perm(2) = 3
        perm(3) = 2
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
        write(6,*) "TESTING TRANPOSE TYPE 1324"
        write(6,*) "==================="
        write(6,*) "The compilation flags were:"
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
        DO 101 i = 1, 20
          CALL transpose_1324_loop_1234(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
101     CONTINUE
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
        DO 501 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
501     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 102 i = 1, 20
          CALL transpose_1324_loop_1243(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
102     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=1
          fastest(2)=2
          fastest(3)=4
          fastest(4)=3
        endif
        write(6,1100) "  2 Loop 1243 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 502 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
502     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 103 i = 1, 20
          CALL transpose_1324_loop_1324(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
103     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=1
          fastest(2)=3
          fastest(3)=2
          fastest(4)=4
        endif
        write(6,1100) "  3 Loop 1324 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 503 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
503     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 104 i = 1, 20
          CALL transpose_1324_loop_1423(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
104     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=1
          fastest(2)=4
          fastest(3)=2
          fastest(4)=3
        endif
        write(6,1100) "  4 Loop 1423 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 504 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
504     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 105 i = 1, 20
          CALL transpose_1324_loop_1342(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
105     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=1
          fastest(2)=3
          fastest(3)=4
          fastest(4)=2
        endif
        write(6,1100) "  5 Loop 1342 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 505 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
505     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 106 i = 1, 20
          CALL transpose_1324_loop_1432(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
106     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=1
          fastest(2)=4
          fastest(3)=3
          fastest(4)=2
        endif
        write(6,1100) "  6 Loop 1432 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 506 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
506     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 107 i = 1, 20
          CALL transpose_1324_loop_2134(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
107     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=2
          fastest(2)=1
          fastest(3)=3
          fastest(4)=4
        endif
        write(6,1100) "  7 Loop 2134 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 507 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
507     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 108 i = 1, 20
          CALL transpose_1324_loop_2143(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
108     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=2
          fastest(2)=1
          fastest(3)=4
          fastest(4)=3
        endif
        write(6,1100) "  8 Loop 2143 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 508 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
508     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 109 i = 1, 20
          CALL transpose_1324_loop_3124(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
109     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=3
          fastest(2)=1
          fastest(3)=2
          fastest(4)=4
        endif
        write(6,1100) "  9 Loop 3124 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 509 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
509     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 110 i = 1, 20
          CALL transpose_1324_loop_4123(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
110     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=4
          fastest(2)=1
          fastest(3)=2
          fastest(4)=3
        endif
        write(6,1100) " 10 Loop 4123 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 510 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
510     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 111 i = 1, 20
          CALL transpose_1324_loop_3142(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
111     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=3
          fastest(2)=1
          fastest(3)=4
          fastest(4)=2
        endif
        write(6,1100) " 11 Loop 3142 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 511 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
511     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 112 i = 1, 20
          CALL transpose_1324_loop_4132(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
112     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=4
          fastest(2)=1
          fastest(3)=3
          fastest(4)=2
        endif
        write(6,1100) " 12 Loop 4132 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 512 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
512     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 113 i = 1, 20
          CALL transpose_1324_loop_2314(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
113     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=2
          fastest(2)=3
          fastest(3)=1
          fastest(4)=4
        endif
        write(6,1100) " 13 Loop 2314 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 513 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
513     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 114 i = 1, 20
          CALL transpose_1324_loop_2413(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
114     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=2
          fastest(2)=4
          fastest(3)=1
          fastest(4)=3
        endif
        write(6,1100) " 14 Loop 2413 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 514 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
514     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 115 i = 1, 20
          CALL transpose_1324_loop_3214(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
115     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=3
          fastest(2)=2
          fastest(3)=1
          fastest(4)=4
        endif
        write(6,1100) " 15 Loop 3214 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 515 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
515     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 116 i = 1, 20
          CALL transpose_1324_loop_4213(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
116     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=4
          fastest(2)=2
          fastest(3)=1
          fastest(4)=3
        endif
        write(6,1100) " 16 Loop 4213 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 516 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
516     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 117 i = 1, 20
          CALL transpose_1324_loop_3412(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
117     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=3
          fastest(2)=4
          fastest(3)=1
          fastest(4)=2
        endif
        write(6,1100) " 17 Loop 3412 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 517 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
517     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 118 i = 1, 20
          CALL transpose_1324_loop_4312(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
118     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=4
          fastest(2)=3
          fastest(3)=1
          fastest(4)=2
        endif
        write(6,1100) " 18 Loop 4312 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 518 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
518     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 119 i = 1, 20
          CALL transpose_1324_loop_2341(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
119     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=2
          fastest(2)=3
          fastest(3)=4
          fastest(4)=1
        endif
        write(6,1100) " 19 Loop 2341 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 519 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
519     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 120 i = 1, 20
          CALL transpose_1324_loop_2431(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
120     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=2
          fastest(2)=4
          fastest(3)=3
          fastest(4)=1
        endif
        write(6,1100) " 20 Loop 2431 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 520 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
520     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 121 i = 1, 20
          CALL transpose_1324_loop_3241(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
121     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=3
          fastest(2)=2
          fastest(3)=4
          fastest(4)=1
        endif
        write(6,1100) " 21 Loop 3241 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 521 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
521     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 122 i = 1, 20
          CALL transpose_1324_loop_4231(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
122     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=4
          fastest(2)=2
          fastest(3)=3
          fastest(4)=1
        endif
        write(6,1100) " 22 Loop 4231 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 522 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
522     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 123 i = 1, 20
          CALL transpose_1324_loop_3421(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
123     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=3
          fastest(2)=4
          fastest(3)=2
          fastest(4)=1
        endif
        write(6,1100) " 23 Loop 3421 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 523 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
523     CONTINUE
        Tstart=0.0
        Tfinish=0.0
        CALL CPU_TIME(Tstart)
        DO 124 i = 1, 20
          CALL transpose_1324_loop_4321(before, after_jeff,
     &                    aSize(1), aSize(2), aSize(3), aSize(4),
     &                    factor)
124     CONTINUE
        CALL CPU_TIME(Tfinish)
        Tjeff=(Tfinish-Tstart)
        Tspeedup=Thirata/Tjeff
        Tbest=min(Tjeff,Tbest)
        if(Tjeff.eq.Tbest) then 
          fastest(1)=4
          fastest(2)=3
          fastest(3)=2
          fastest(4)=1
        endif
        write(6,1100) " 24 Loop 4321 ",
     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest
        DO 524 i = 1, 1048576
          IF (after_jeff(i).ne.after_hirata(i)) THEN
            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)
          ENDIF
524     CONTINUE
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
