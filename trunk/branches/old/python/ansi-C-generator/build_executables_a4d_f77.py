import fileinput
import string
import sys
import os

c_compiler = 'icc'
c_link_flags = '-g -O1 -xT -march=core2 -mtune=core2 -align -strict-ansi'
c_opt_flags = '-g -O3 -xT -march=core2 -mtune=core2 -funroll-loops -align -strict-ansi'
fortran_compiler = 'ifort'
fortran_link_flags = '-g -O1 -xT -march=core2 -mtune=core2 -align '
fortran_opt_flags = '-g -O3 -xT -march=core2 -mtune=core2 -funroll-loops -align -c '
src_dir = '/home/jeff/code/spaghetty/trunk/source/ansi-C/'
exe_dir = '/home/jeff/code/spaghetty/trunk/binary/ansi-C/'

modlabel = 'a4d'

lib_name = 'tce_sort_'+modlabel+'.a'

count = '20'
rank  = '32'
ranks = [rank,rank,rank,rank]
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])
sizechar = str(size)

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['1','2','3','4']
#indices = ['4','3','2','1']

transpose_list = [indices]
#transpose_list = perm(indices)
loop_list = [indices]
#loop_list = perm(indices)

#loop_list = ['2431','3241','3142','2341','3214','3124','2314'] 
#loop_list = ['2314'] 

print fortran_compiler+' '+fortran_opt_flags+'-c tce_sort_hirata.F'
os.system(fortran_compiler+' '+fortran_opt_flags+'-c tce_sort_hirata.F')
os.system('ar -r '+lib_name+' tce_sort_hirata.o')

for transpose_order in transpose_list:
    dummy = 0
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    driver_name = 'transpose_'+A+B+C+D+'_'+modlabel
    print driver_name
    source_name = driver_name+'_driver.F'
    source_file = open(source_name,'w')
    source_file.write('        PROGRAM ARRAYTEST\n')
    source_file.write('        REAL*8 before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
    source_file.write('        REAL*8 after_jeff('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
    source_file.write('        REAL*8 after_hirata('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
#    source_file.write('        REAL*8 after_jeff('+sizechar+')\n')
#    source_file.write('        REAL*8 after_hirata('+sizechar+')\n')
    source_file.write('        REAL*8 factor\n')
    source_file.write('        REAL*8 Tstart,Tfinish,Thirata,Tjeff\n')
    source_file.write('        REAL*8 Tspeedup,Tbest\n')
    source_file.write('        INTEGER*4 i,j,k,l\n')
    source_file.write('        INTEGER*4 aSize(4)\n')
    source_file.write('        INTEGER*4 perm(4)\n')
    source_file.write('        INTEGER*4 fastest(4)\n')
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
    source_file.write('        factor = 1.0\n')
    source_file.write('        Tbest=999999.0\n')
    source_file.write('        Tstart=0.0\n')
    source_file.write('        Tfinish=0.0\n')
    source_file.write('        CALL CPU_TIME(Tstart)\n')
    source_file.write('        DO 30 i = 1, '+count+'\n')
    source_file.write('          CALL tce_sort_4(before, after_hirata,\n')
    source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
    source_file.write('     &                    perm(1), perm(2), perm(3), perm(4), factor)\n')
    source_file.write('30      CONTINUE\n')
    source_file.write('        CALL CPU_TIME(Tfinish)\n')
    source_file.write('        Thirata=(Tfinish-Tstart)\n')
    source_file.write('        write(6,*) "TESTING TRANPOSE TYPE '+A+B+C+D+'"\n')
    source_file.write('        write(6,*) "==================="\n')
    source_file.write('        write(6,*) "The compilation flags were:"\n')
    for option in range(0,len(fortran_opt_flags.split())):
        source_file.write('        write(6,*) "'+fortran_opt_flags.split()[option]+'"\n')
        
    source_file.write('        write(6,*) "==================="\n')
    source_file.write('        write(6,*) "Hirata Reference = ",Thirata,"seconds"\n')
    source_file.write('        write(6,1001) "Algorithm","Jeff","Speedup","Best","Best Speedup"\n')
    for loop_order in loop_list:
        dummy = dummy+1
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        subroutine_name = 'trans_a4d_'+A+B+C+D+'_loop_'+a+b+c+d
        source_file.write('        Tstart=0.0\n')
        source_file.write('        Tfinish=0.0\n')
        source_file.write('        CALL CPU_TIME(Tstart)\n')
        source_file.write('        write(6,*) "*** START TIMING THE SUBROUTINE ***"\n')
        source_file.write('        DO '+str(100+dummy)+' i = 1, '+count+'\n')
        source_file.write('          CALL '+subroutine_name+'(before, after_jeff,\n')
        source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
        source_file.write('     &                    factor)\n')
        source_file.write(str(100+dummy)+'     CONTINUE\n')
        source_file.write('        write(6,*) "*** FINISHED TIMING THE SUBROUTINE ***"\n')
        source_file.write('        CALL CPU_TIME(Tfinish)\n')
        source_file.write('        Tjeff=(Tfinish-Tstart)\n')
        source_file.write('        Tspeedup=Thirata/Tjeff\n')
        source_file.write('        Tbest=min(Tjeff,Tbest)\n')
        source_file.write('        if(Tjeff.eq.Tbest) then \n')
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
        source_file.write('        DO 9970 i = 1, '+ranks[0]+'\n')
        source_file.write('          DO 9960 j = 1, '+ranks[1]+'\n')
        source_file.write('            DO 9950 k = 1, '+ranks[2]+'\n')
        source_file.write('              DO 9940 l = 1, '+ranks[3]+'\n')
        source_file.write('          IF (after_jeff(i,j,k,l).ne.after_hirata(i,j,k,l)) THEN\n')
        source_file.write('            PRINT*,"jeff error ",i,j,k,l,after_jeff(i,j,k,l),after_hirata(i,j,k,l)\n')
        source_file.write('          ENDIF\n')
        source_file.write('9940            CONTINUE\n')
        source_file.write('9950          CONTINUE\n')
        source_file.write('9960        CONTINUE\n')
        source_file.write('9970      CONTINUE\n')
        
    source_file.write('        write(6,1020) "The best loop order is:",\n')
    source_file.write('     &             fastest(1),fastest(2),fastest(3),fastest(4)\n')
    source_file.write('        write(6,1030) "The best time is:",Tbest\n')
    source_file.write('        write(6,1030) "The best speedup is:",Thirata/Tbest\n')
    source_file.write('        STOP\n')
    source_file.write(' 1001 format(1x,a13,a12,a15,a9,a18)\n')
    source_file.write(' 1020 format(1x,a30,8x,4i1)\n')
    source_file.write(' 1030 format(1x,a30,1f12.5)\n')
    source_file.write(' 1100 format(1x,a16,4f12.5)\n')
    source_file.write('      END\n')
    source_file.close()
    print fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' '+lib_name+' '+' -o '+exe_dir+driver_name+'.x'
    os.system(fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' '+lib_name+' '+' -o '+exe_dir+driver_name+'.x')
    os.system('mv '+source_name+' '+src_dir)



    
