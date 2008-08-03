import fileinput
import string
import sys
import os

#fortran_compiler = '/bgsys/drivers/ppcfloor/comm/bin/mpixlf77_r'
#fortran_link_flags = '-O3 -qnoipa -qnounroll -qmaxmem=8192 -qnoextname -qnosmp'
#fortran_opt_flags = '-O5 -qunroll=yes -qmaxmem=8192 -qnoextname -qnosmp -c'
#src_dir = '/gpfs/home/jhammond/spaghetty/python/archive/src/'
#exe_dir = '/gpfs/home/jhammond/spaghetty/python/archive/exe/'

fortran_compiler = 'ifort'
fortran_opt_flags = '-O3 -mtune=core2 -msse3 -align -c'
fortran_link_flags = '-O0'
src_dir = '/home/jeff/code/spaghetty/trunk/python/archive/src/'
exe_dir = '/home/jeff/code/spaghetty/trunk/python/archive/exe/'

count = '30'
rank = '8'
ranks = [rank,rank,rank,rank,rank,rank]
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])*int(ranks[4])*int(ranks[5])
sizechar = str(size)

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['1','2','3','4','5','6']

#all_permutations = perm(indices)
#all_permutations = [indices]

#transpose_list = perm(indices)
transpose_list = [indices]
loop_list = perm(indices)

#print fortran_compiler+' '+fortran_opt_flags+' tce_sort_hirata.F'
#os.system(fortran_compiler+' '+fortran_opt_flags+' tce_sort_hirata.F')
#os.system('ar -r tce_sort_jeff.a tce_sort_hirata.o')

for transpose_order in transpose_list:
    dummy = 0
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    E = transpose_order[4]
    F = transpose_order[5]
    driver_name = 'transpose_'+A+B+C+D+E+F
    print driver_name
    source_name = driver_name+'_driver.F'
    source_file = open(source_name,'w')
    source_file.write('        PROGRAM ARRAYTEST\n')
    source_file.write('        REAL*8 before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
    source_file.write('        REAL*8 after_jeff('+sizechar+')\n')
    source_file.write('        REAL*8 after_hirata('+sizechar+')\n')
    source_file.write('        REAL*8 factor\n')
    source_file.write('        REAL*4 Tstart,Tfinish,Thirata,Tjeff,Tspeedup,Tbest\n')
    source_file.write('        INTEGER*4 i,j,k,l,m,n\n')
    source_file.write('        INTEGER*4 aSize(6)\n')
    source_file.write('        INTEGER*4 perm(6)\n')
    source_file.write('        aSize(1) = '+ranks[0]+'\n')
    source_file.write('        aSize(2) = '+ranks[1]+'\n')
    source_file.write('        aSize(3) = '+ranks[2]+'\n')
    source_file.write('        aSize(4) = '+ranks[3]+'\n')
    source_file.write('        aSize(5) = '+ranks[4]+'\n')
    source_file.write('        aSize(6) = '+ranks[5]+'\n')        
    source_file.write('        perm(1) = '+A+'\n')
    source_file.write('        perm(2) = '+B+'\n')
    source_file.write('        perm(3) = '+C+'\n')
    source_file.write('        perm(4) = '+D+'\n')
    source_file.write('        perm(5) = '+E+'\n')
    source_file.write('        perm(6) = '+F+'\n')
    source_file.write('        DO 70 i = 1, '+ranks[0]+'\n')
    source_file.write('         DO 65 j = 1, '+ranks[1]+'\n')
    source_file.write('          DO 60 k = 1, '+ranks[2]+'\n')
    source_file.write('           DO 55 l = 1, '+ranks[3]+'\n')
    source_file.write('            DO 50 m = 1, '+ranks[4]+'\n')
    source_file.write('             DO 45 n = 1, '+ranks[5]+'\n')
    source_file.write('                before(i,j,k,l,m,n) = n + m*10 + l*100 + k*1000 \n')
    source_file.write('     &                              + j*10000 + i*100000 \n')
    source_file.write('45           CONTINUE\n')
    source_file.write('50          CONTINUE\n')
    source_file.write('55         CONTINUE\n')
    source_file.write('60        CONTINUE\n')
    source_file.write('65       CONTINUE\n')
    source_file.write('70      CONTINUE\n')
    source_file.write('        factor = 1.0\n')
    source_file.write('        Tbest=999999.0\n')
    source_file.write('        Tstart=0.0\n')    
    source_file.write('        Tfinish=0.0\n')
    source_file.write('        CALL CPU_TIME(Tstart)\n')
    #source_file.write('        Tstart=rtc()\n')
    source_file.write('        DO 30 i = 1, '+count+'\n')
    source_file.write('          CALL tce_sort_6(before, after_hirata,\n')
    source_file.write('     &    aSize(1), aSize(2), aSize(3), aSize(4), aSize(5), aSize(6),\n')
    source_file.write('     &    perm(1), perm(2), perm(3), perm(4), perm(5), perm(6), factor)\n')
    source_file.write('30      CONTINUE\n')
    source_file.write('        CALL CPU_TIME(Tfinish)\n')
    #source_file.write('        Tfinish=rtc()\n')
    source_file.write('        Thirata=(Tfinish-Tstart)\n')
    source_file.write('        PRINT*,"TESTING TRANPOSE TYPE '+A+B+C+D+E+F+'"\n')
    source_file.write('        PRINT*,"Hirata Reference = ",Thirata,"seconds"\n')
    source_file.write('        PRINT*,"Algorithm         Jeff           Speedup          Best"\n')
    for loop_order in loop_list:
        dummy = dummy+1
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        e = loop_order[4]
        f = loop_order[5]
        subroutine_name = 'transpose_'+A+B+C+D+E+F+'_loop_'+a+b+c+d+e+f
        source_file.write('        Tstart=0.0\n')
        source_file.write('        Tfinish=0.0\n')
        source_file.write('        CALL CPU_TIME(Tstart)\n')
        #source_file.write('        Tstart=rtc()\n')
        source_file.write('        DO '+str(1000+dummy)+' i = 1, '+count+'\n')
        source_file.write('          CALL '+subroutine_name+'(before, after_jeff,\n')
        source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4), \n')
        source_file.write('     &                    aSize(5), aSize(6), factor)\n')
        source_file.write(str(1000+dummy)+'     CONTINUE\n')
        source_file.write('        CALL CPU_TIME(Tfinish)\n')
        #source_file.write('        Tfinish=rtc()\n')
        source_file.write('        Tjeff=(Tfinish-Tstart)\n')
        source_file.write('        Tspeedup=Thirata/Tjeff\n')
        source_file.write('        Tbest=min(Tjeff,Tbest)\n')
        if 0 < dummy < 10:
            nice_dummy='  '+str(dummy)
        
        if 9 < dummy < 100:
            nice_dummy=' '+str(dummy)
            
        if 99 < dummy < 999:
            nice_dummy=''+str(dummy)
            
        #source_file.write('        PRINT*,"'+nice_dummy+' Loop '+a+b+c+d+e+f+'     ",Tjeff,Tspeedup,Tbest\n')
        source_file.write('        write(6,1) "'+nice_dummy+' Loop '+a+b+c+d+e+f+' ",Tjeff,Tspeedup,Tbest,Thirata/Tbest\n')
        source_file.write('        DO '+str(2000+dummy)+' i = 1, '+sizechar+'\n')
        source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
        source_file.write('            PRINT*,"error at position ",i,after_jeff(i),after_hirata(i)\n')
        source_file.write('          ENDIF\n')
        source_file.write(str(2000+dummy)+'     CONTINUE\n')

    source_file.write('        PRINT*,"The best time is: ",Tbest\n')
    source_file.write('        PRINT*,"The speedup is:   ",Thirata/Tbest\n')
    source_file.write('        STOP\n')
    source_file.write('    1     format(1x,1a20,4f12.5)\n')
    source_file.write('      END\n')
    source_file.close()
    print fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' tce_sort_jeff.a tce_sort_hirata.o '+' -o '+exe_dir+driver_name+'.x'
    os.system(fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' tce_sort_jeff.a tce_sort_hirata.o '+' -o '+exe_dir+driver_name+'.x')
    os.system('mv '+source_name+' '+src_dir)




