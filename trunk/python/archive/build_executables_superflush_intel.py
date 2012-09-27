#!/usr/bin/python

import fileinput
import string
import sys
import os

mpi = True
if ( mpi ):
    print 'Using MPI'
else:
    print 'Not using MPI'

#OpenMP = True
OpenMP = False
if ( OpenMP ):
    print 'Using OpenMP'
else:
    print 'Not using OpenMP'

fortran_compiler = 'ifort'
if (OpenMP):
        fortran_opt_flags = '-g -i8 -O3 -openmp -xSSE4.2 -opt-prefetch -funroll-loops'
else:
        fortran_opt_flags = '-g -i8 -O3 -xSSE4.2 -opt-prefetch -funroll-loops'

if ( mpi ):
    fortran_linker = 'mpif77'
else:
    fortran_linker = 'ifort'

fortran_link_flags = fortran_opt_flags

src_dir = '~/spaghetty/python/archive/src/'
exe_dir = '~/spaghetty/python/archive/exe/'

if (OpenMP):
        lib_name = 'tce_sort_intel_omp.a'
else:
        lib_name = 'tce_sort_intel.a'

flush_rank='1000'

count = '100'
rank  = '40'
ranks = [rank,rank,rank,rank]
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])
sizechar = str(size)

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['4','3','2','1']

#transpose_list = [['1','3','2','4']]
transpose_list = perm(indices)
loop_list = perm(indices)

print fortran_compiler+' '+fortran_opt_flags+' -c tce_sort_hirata.F'
os.system(fortran_compiler+' '+fortran_opt_flags+' -c tce_sort_hirata.F')
os.system('ar -r '+lib_name+' tce_sort_hirata.o')

#timer = 'jeff'
#timer_call = "jefftime()"
#print fortran_compiler+' '+fortran_opt_flags+' -c jefftime.F'
#os.system(fortran_compiler+' '+fortran_opt_flags+' -c jefftime.F')
#os.system('ar -r '+lib_name+' jefftime.o')

if ( mpi ):
    timer = 'mpi'
    timer_call = "mpi_wtime()"

#timer = 'ticks'
#timer_call = "getticks()"

#timer = 'time'
#timer_call = "gettime()"
#print 'icc -c getticks_linux.c'
#os.system('icc -c getticks_linux.c')
#os.system('ar -r '+lib_name+' getticks_linux.o')

for transpose_order in transpose_list:
    dummy = 0
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    driver_name = 'transpose_'+A+B+C+D+'superflush_intel'
    print driver_name
    source_name = driver_name+'_driver.F'
    source_file = open(source_name,'w')
    source_file.write('        PROGRAM ARRAYTEST4\n')
    if ( mpi ):
        source_file.write('#include "mpif.h"\n')

    source_file.write('        double precision before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
    source_file.write('        double precision after_jeff('+sizechar+')\n')
    source_file.write('        double precision after_hirata('+sizechar+')\n')
    source_file.write('        double precision factor\n')
    source_file.write('        double precision X('+flush_rank+','+flush_rank+'),Y('+flush_rank+','+flush_rank+')\n')
    if ( timer == "ticks" ):
        source_file.write('        integer Tstart,Tfinish\n')
        source_file.write('        integer Thirata,Thirata2,Tjeff\n')
        source_file.write('        integer Tbest\n')
    else:
        source_file.write('        double precision Tstart,Tfinish\n')
        source_file.write('        double precision Thirata,Thirata2,Tjeff\n')
        source_file.write('        double precision Tbest\n')

    source_file.write('        double precision Tspeedup\n')
    source_file.write('        integer i,j,k,l\n')
    source_file.write('        integer ii,jj\n')
    source_file.write('        integer aSize(4)\n')
    source_file.write('        integer perm(4)\n')
    source_file.write('        integer fastest(4)\n')
    if ( mpi ):
        source_file.write('        integer ierror\n')
        source_file.write('        call mpi_init(ierror)\n')

    source_file.write('        factor = 1.0d0\n')
    source_file.write('        aSize(1) = '+ranks[0]+'\n')
    source_file.write('        aSize(2) = '+ranks[1]+'\n')
    source_file.write('        aSize(3) = '+ranks[2]+'\n')
    source_file.write('        aSize(4) = '+ranks[3]+'\n')
    source_file.write('        perm(1) = '+A+'\n')
    source_file.write('        perm(2) = '+B+'\n')
    source_file.write('        perm(3) = '+C+'\n')
    source_file.write('        perm(4) = '+D+'\n')
    source_file.write('        DO 70 i = 1, '+ranks[0]+'\n')
    source_file.write('          DO 60 j = 1, '+ranks[1]+'\n')
    source_file.write('            DO 50 k = 1, '+ranks[2]+'\n')
    source_file.write('              DO 40 l = 1, '+ranks[3]+'\n')
    source_file.write('                before(i,j,k,l) = l + k*10 + j*100 + i*1000\n')
    source_file.write('40            CONTINUE\n')
    source_file.write('50          CONTINUE\n')
    source_file.write('60        CONTINUE\n')
    source_file.write('70      CONTINUE\n')
    # THIS PART FLUSHES THE CACHE
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            X(jj,ii) = 1d0/(ii+jj)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            Y(jj,ii) = 1d0/(ii+jj)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            X(jj,ii) = 7d0*X(ii,jj)+X(jj,ii)-3d0*Y(ii,jj)+2d0*Y(jj,ii)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    # END CACHE FLUSH
    if ( timer == "ticks" ):
        source_file.write('        Tbest=999999\n')
        source_file.write('        Tstart=0\n')
        source_file.write('        Tfinish=0\n')
    else:
        source_file.write('        Tbest=999999.0d0\n')
        source_file.write('        Tstart=0.0d0\n')
        source_file.write('        Tfinish=0.0d0\n')

    source_file.write('        Tstart='+timer_call+'\n')
    source_file.write('        DO 30 i = 1, '+count+'\n')
    if (OpenMP):
            source_file.write('          CALL tce_sort_4(before, after_hirata,\n')
    else:
            source_file.write('          CALL tce_sort_4_omp(before, after_hirata,\n')

    source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
    source_file.write('     &                    perm(1), perm(2), perm(3), perm(4),factor)\n')
    source_file.write('30      CONTINUE\n')
    source_file.write('        Tfinish='+timer_call+'\n')
    source_file.write('        Thirata=(Tfinish-Tstart)\n')
    # THIS PART FLUSHES THE CACHE
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            X(jj,ii) = 1d0/(ii+jj)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            Y(jj,ii) = 1d0/(ii+jj)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            X(jj,ii) = 7d0*X(ii,jj)+X(jj,ii)-3d0*Y(ii,jj)+2d0*Y(jj,ii)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    # END CACHE FLUSH
    source_file.write('        write(6,*) "TESTING TRANPOSE TYPE '+A+B+C+D+'"\n')
    source_file.write('        write(6,*) "FOR 4D ARRAY OF RANK '+rank+'"\n')
    source_file.write('        write(6,*) "==================="\n')
    source_file.write('        write(6,*) "The compilation flags were:"\n')
    for option in range(0,len(fortran_opt_flags.split())):
        source_file.write('        write(6,*) "'+fortran_opt_flags.split()[option]+'"\n')
        
    source_file.write('        write(6,*) "==================="\n')
    source_file.write('        write(6,1030) "Hirata Ref. #1 = ",Thirata\n')
    source_file.write('        write(6,1001) "Algorithm","Jeff","Speedup","Best","Best Speedup"\n')
    for loop_order in loop_list:
        dummy = dummy+1
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        if (OpenMP):
            subroutine_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d+'_intel_omp'
        else:
            subroutine_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d+'_intel'

        # THIS PART FLUSHES THE CACHE
        source_file.write('        do ii=1,'+flush_rank+'\n')
        source_file.write('          do jj=1,'+flush_rank+'\n')
        source_file.write('            X(jj,ii) = 1d0/(ii+jj)\n')
        source_file.write('          enddo \n')
        source_file.write('        enddo \n')
        source_file.write('        do ii=1,'+flush_rank+'\n')
        source_file.write('          do jj=1,'+flush_rank+'\n')
        source_file.write('            Y(jj,ii) = 1d0/(ii+jj)\n')
        source_file.write('          enddo \n')
        source_file.write('        enddo \n')
        source_file.write('        do ii=1,'+flush_rank+'\n')
        source_file.write('          do jj=1,'+flush_rank+'\n')
        source_file.write('            X(jj,ii) = 7d0*X(ii,jj)+X(jj,ii)-3d0*Y(ii,jj)+2d0*Y(jj,ii)\n')
        source_file.write('          enddo \n')
        source_file.write('        enddo \n')
        # END CACHE FLUSH
        if ( timer == "ticks" ):
            source_file.write('        Tstart=0\n')
            source_file.write('        Tfinish=0\n')
            source_file.write('        Tjeff=0\n')
        else:
            source_file.write('        Tstart=0.0d0\n')
            source_file.write('        Tfinish=0.0d0\n')
            source_file.write('        Tjeff=0.0d0\n')

        source_file.write('        DO '+str(100+dummy)+' i = 1, '+count+'\n')
        # THIS PART FLUSHES THE CACHE
        source_file.write('          do ii=1,'+flush_rank+'\n')
        source_file.write('            do jj=1,'+flush_rank+'\n')
        source_file.write('              X(jj,ii) = 1d0/(ii+jj)\n')
        source_file.write('            enddo \n')
        source_file.write('          enddo \n')
        source_file.write('          do ii=1,'+flush_rank+'\n')
        source_file.write('            do jj=1,'+flush_rank+'\n')
        source_file.write('              Y(jj,ii) = 1d0/(ii+jj)\n')
        source_file.write('            enddo \n')
        source_file.write('          enddo \n')
        source_file.write('          do ii=1,'+flush_rank+'\n')
        source_file.write('            do jj=1,'+flush_rank+'\n')
        source_file.write('              X(jj,ii) = 7d0*X(ii,jj)+X(jj,ii)-3d0*Y(ii,jj)+2d0*Y(jj,ii)\n')
        source_file.write('            enddo \n')
        source_file.write('          enddo \n')
        # END CACHE FLUSH
        source_file.write('          Tstart='+timer_call+'\n')
        source_file.write('          CALL '+subroutine_name+'(before, after_jeff,\n')
        source_file.write('     &        aSize(1), aSize(2), aSize(3), aSize(4), factor)\n')
        source_file.write('          Tfinish='+timer_call+'\n')
        source_file.write('          Tjeff=Tjeff+(Tfinish-Tstart)\n')
        source_file.write(str(100+dummy)+'     CONTINUE\n')
        source_file.write('        Tspeedup=(1d0*Thirata)/(1d0*Tjeff)\n')
        source_file.write('        if (Tjeff<Tbest) then\n')
        source_file.write('          Tbest=Tjeff\n')
        source_file.write('          fastest(1)='+a+'\n')
        source_file.write('          fastest(2)='+b+'\n')
        source_file.write('          fastest(3)='+c+'\n')
        source_file.write('          fastest(4)='+d+'\n')
        source_file.write('        endif\n')
        if 0 < dummy < 10:
            nice_dummy='  '+str(dummy)
        
        if 9 < dummy < 100:
            nice_dummy=' '+str(dummy)
            
        if 99 < dummy < 999:
            nice_dummy=''+str(dummy)
            
        source_file.write('        write(6,1100) "'+nice_dummy+' Loop '+a+b+c+d+' ",\n')
        source_file.write('     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest\n')
        source_file.write('        DO '+str(500+dummy)+' i = 1, '+sizechar+'\n')
        source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
        source_file.write('            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)\n')
        source_file.write('          ENDIF\n')
        source_file.write(str(500+dummy)+'     CONTINUE\n')

    if ( timer == "ticks" ):
        source_file.write('        Tstart=0\n')
        source_file.write('        Tfinish=0\n')
        source_file.write('        Thirata2=0\n')
    else:
        source_file.write('        Tstart=0.0d0\n')
        source_file.write('        Tfinish=0.0d0\n')
        source_file.write('        Thirata2=0.0d0\n')

    source_file.write('        DO 34 i = 1, '+count+'\n')
    # THIS PART FLUSHES THE CACHE
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            X(jj,ii) = 1d0/(ii+jj)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            Y(jj,ii) = 1d0/(ii+jj)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    source_file.write('        do ii=1,'+flush_rank+'\n')
    source_file.write('          do jj=1,'+flush_rank+'\n')
    source_file.write('            X(jj,ii) = 7d0*X(ii,jj)+X(jj,ii)-3d0*Y(ii,jj)+2d0*Y(jj,ii)\n')
    source_file.write('          enddo \n')
    source_file.write('        enddo \n')
    # END CACHE FLUSH
    source_file.write('        Tstart='+timer_call+'\n')
    if (OpenMP):
            source_file.write('          CALL tce_sort_4(before, after_hirata,\n')
    else:
            source_file.write('          CALL tce_sort_4_omp(before, after_hirata,\n')

    source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
    source_file.write('     &                    perm(1), perm(2), perm(3), perm(4),factor)\n')
    source_file.write('        Tfinish='+timer_call+'\n')
    source_file.write('        Thirata2=Thirata2+(Tfinish-Tstart)\n')
    source_file.write('34      CONTINUE\n')
    source_file.write('        write(6,1030) "Hirata Ref. #2 = ",Thirata2\n')
    source_file.write('        write(6,1020) "The best loop order is:",\n')
    source_file.write('     &             fastest(1),fastest(2),fastest(3),fastest(4)\n')
    source_file.write('        write(6,1030) "The best time is:",Tbest\n')
    source_file.write('        write(6,1030) "Best speedup (#1) is:",(1d0*Thirata)/(1d0*Tbest)\n')
    source_file.write('        write(6,1030) "Best speedup (#2) is:",(1d0*Thirata2)/(1d0*Tbest)\n')
    if ( mpi ):
        source_file.write('        call mpi_finalize(ierror)\n')

    #source_file.write('        STOP\n')
    source_file.write(' 1001 format(1x,a13,a12,a15,a9,a18)\n')
    source_file.write(' 1020 format(1x,a30,8x,4i1)\n')
    source_file.write(' 1030 format(1x,a30,f12.6)\n')
    source_file.write(' 1100 format(1x,a16,4f12.6)\n')
    source_file.write('      END\n')
    source_file.close()
    print fortran_linker+' '+fortran_link_flags+' '+' '+source_name+' '+lib_name+' '+' -o '+exe_dir+driver_name+'.x'
    os.system(fortran_linker+' '+fortran_link_flags+' '+' '+source_name+' '+lib_name+' '+' -o '+exe_dir+driver_name+'.x')
    os.system('mv '+source_name+' '+src_dir)



    
