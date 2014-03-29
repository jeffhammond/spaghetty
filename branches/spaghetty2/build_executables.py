import fileinput
import string
import sys
import os

# Goldstone old
#fortran_compiler = '/bgsys/drivers/ppcfloor/comm/bin/mpixlf77_r'
#fortran_link_flags = '-O3 -qnoipa -qnounroll -qmaxmem=8192 -qnoextname -qnosmp'
#fortran_opt_flags = '-O5 -qunroll=yes -qmaxmem=8192 -qnoextname -qnosmp -c'
#src_dir = '/gpfs/home/jhammond/spaghetty/python/archive/src/'
#exe_dir = '/gpfs/home/jhammond/spaghetty/python/archive/exe/'

fortran_compiler = 'ifort'
fortran_link_flags = '-O1 -xT -mtune=core2 -align -pad'
opt_set = [[],[],[],[],[],[],[],[],[]]
opt_set[0] = '-O3 -xT -mtune=core2 -align -pad'# -unroll-aggressive -vec-guard-write -opt-streaming-stores always'
opt_set[1] = '-O1'
opt_set[2] = '-O2'
opt_set[3] = '-O3 -align -pad'
opt_set[4] = '-O3 -unroll-aggressive'
opt_set[5] = '-O3 -parallel'
opt_set[6] = '-O3 -xT -mtune=core2'
opt_set[7] = '-O3 -vec-guard-write'
opt_set[8] = '-O3 -opt-streaming-stores always'
#opt_set_num = 3
#fortran_opt_flags = opt_set[opt_set_num]
#src_dir = '/home/jeff/code/spaghetty/trunk/python/archive/src_optset'+str(opt_set_num)+'/'
#exe_dir = '/home/jeff/code/spaghetty/trunk/python/archive/exe_optset'+str(opt_set_num)+'/'
#lib_name = 'tce_sort_optset'+str(opt_set_num)+'.a'

count = '100'
rank  = '25'
ranks = [rank,rank,rank,rank]
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])
sizechar = str(size)

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

#indices = ['1','2','3','4']
indices = ['4','3','2','1']

#all_permutations = perm(indices)
#all_permutations = [indices]

transpose_list = [indices]
#transpose_list = perm(indices)
#loop_list = [indices]
loop_list = perm(indices)

loop_list = ['3421','3412','2431','2413','3241','3142','2341','1342','2143','1243','3214','3124','2314','1324','2134','1234'] 

#print fortran_compiler+' '+fortran_opt_flags+' -c tce_sort_hirata.F'
#os.system(fortran_compiler+' '+fortran_opt_flags+' -c tce_sort_hirata.F')
#os.system('ar -r '+lib_name+' tce_sort_hirata.o')

for opt_set_num in range(0,1):
    print 'opt_set_num = '+str(opt_set_num)
    fortran_opt_flags = opt_set[opt_set_num]
    src_dir = '/home/jeff/code/spaghetty/trunk/python/archive/src_optset'+str(opt_set_num)+'_unroll/'
    exe_dir = '/home/jeff/code/spaghetty/trunk/python/archive/exe_optset'+str(opt_set_num)+'_unroll/'
    lib_name = 'tce_sort_optset'+str(opt_set_num)+'_unroll.a'
    print fortran_compiler+' '+fortran_opt_flags+' -c tce_sort_hirata.F'
    os.system(fortran_compiler+' '+fortran_opt_flags+' -c tce_sort_hirata.F')
    os.system('ar -r '+lib_name+' tce_sort_hirata.o')
    for transpose_order in transpose_list:
        dummy = 0
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
        driver_name = 'transpose_'+A+B+C+D
        print driver_name
        source_name = driver_name+'_driver.F'
        source_file = open(source_name,'w')
        source_file.write('        PROGRAM ARRAYTEST\n')
        source_file.write('        REAL*8 before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
        source_file.write('        REAL*8 after_jeff('+sizechar+')\n')
        source_file.write('        REAL*8 after_hirata('+sizechar+')\n')
        source_file.write('        REAL*8 factor\n')
        source_file.write('        REAL*8 Tstart,Tfinish,Thirata,Tjeff,Tspeedup,Tbest\n')
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
        #source_file.write('        Tstart=rtc()\n')
        source_file.write('        DO 30 i = 1, '+count+'\n')
        source_file.write('          CALL tce_sort_4(before, after_hirata,\n')
        source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
        source_file.write('     &                    perm(1), perm(2), perm(3), perm(4), factor)\n')
        source_file.write('30      CONTINUE\n')
        #source_file.write('        Tfinish=rtc()\n')
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
            subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d
            source_file.write('        Tstart=0.0\n')
            source_file.write('        Tfinish=0.0\n')
            source_file.write('        CALL CPU_TIME(Tstart)\n')
            #source_file.write('        Tstart=rtc()\n')
            source_file.write('        DO '+str(100+dummy)+' i = 1, '+count+'\n')
            source_file.write('          CALL '+subroutine_name+'(before, after_jeff,\n')
            source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
            source_file.write('     &                    factor)\n')
            source_file.write(str(100+dummy)+'     CONTINUE\n')
            source_file.write('        CALL CPU_TIME(Tfinish)\n')
            #source_file.write('        Tfinish=rtc()\n')
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
                
            #source_file.write('        PRINT*,"Loop '+a+b+c+d+'     ",Tjeff,Tspeedup\n')
            source_file.write('        write(6,1100) "'+nice_dummy+' Loop '+a+b+c+d+' ",\n')
            source_file.write('     &                 Tjeff,Tspeedup,Tbest,Thirata/Tbest\n')
            #source_file.write('        DO '+str(500+dummy)+' i = 1, '+sizechar+'\n')
            #source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
            #source_file.write('            write(6,*),"transpose is wrong for element = ",i\n')
            #source_file.write('          ENDIF\n')
            #source_file.write(str(500+dummy)+'     CONTINUE\n')
            source_file.write('        DO '+str(500+dummy)+' i = 1, '+sizechar+'\n')
            source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
            source_file.write('            PRINT*,"error at position ",i,after_jeff(i),after_hirata(i)\n')
            source_file.write('          ENDIF\n')
            source_file.write(str(500+dummy)+'     CONTINUE\n')
            
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
    
    
    
    
