import fileinput
import string
import sys
import os

c_compiler = 'icc'
c_link_flags = '-O1 -xT -march=core2 -mtune=core2 -align'
c_opt_flags = '-O3 -xT -march=core2 -mtune=core2 -align -funroll-loops -prefetch -ssp'
#c_compiler = 'gcc'
#c_link_flags = '-O1 -march=pentium4 -mtune=pentium4 '
#c_opt_flags = '-O3 -march=pentium4 -mtune=pentium4 -funroll-loops '
fortran_compiler = 'ifort'
fortran_link_flags = '-O1 -xT -march=core2 -mtune=core2 -align'
fortran_opt_flags = '-O3 -xT -march=core2 -mtune=core2 -funroll-loops -align'
#fortran_compiler = 'gfortran'
#fortran_link_flags = '-O1 -march=pentium4 -mtune=pentium4 '
#fortran_opt_flags = '-O3 -march=pentium4 -mtune=pentium4 -funroll-loops '
src_dir = '/home/jeff/code/spaghetty/trunk/source/ansi-C/'
exe_dir = '/home/jeff/code/spaghetty/trunk/binary/ansi-C/'

#modlabel = 'gcc'
#modlabel = 'new'
modlabel = 'realA'
#modlabel = 'unroll'
#modlabel = 'opt'

lib_name = 'tce_sort_'+modlabel+'.a'

num = ''

count = '20'
rank  = '40'
#rank  = '5'
ranks = [rank,rank,rank,rank]
#ranks = ['41','17','24','39']
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])
sizechar = str(size)

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

#indices = ['1','2','3','4']
#indices = ['4','3','2','1']
all_permutations = perm(['1','2','3','4'])

#transpose_list = [indices]
#transpose_list = perm(indices)
#transpose_list = [['2','1','3','4'],['1','2','4','3']]
#transpose_list = ['1243','1432','2143','2413','2431','3124','3214','3241','4123','4132','4231','4321']
transpose_list = all_permutations

#loop_list = [indices]
#loop_list = perm(indices)
#loop_list = ['2134','2143','3124','3142','2314','2413','3214','3412','2341','2431','3241','3421']
loop_list = all_permutations

print fortran_compiler+' '+fortran_opt_flags+' -c tce_sort_hirata.F'
os.system(fortran_compiler+' '+fortran_opt_flags+' -c tce_sort_hirata.F')
os.system('ar -r '+lib_name+' tce_sort_hirata.o')

print c_compiler+' '+c_opt_flags+' -c tce_sort_4kg.c'
os.system(c_compiler+' '+c_opt_flags+' -c tce_sort_4kg.c')
os.system('ar -r '+lib_name+' tce_sort_4kg.o')

#print c_compiler+' '+c_opt_flags+' -c tce_sort_saday.c'
#os.system(c_compiler+' '+c_opt_flags+' -c tce_sort_saday.c')
#os.system('ar -r '+lib_name+' tce_sort_saday.o')

print c_compiler+' '+c_opt_flags+' -c tce_sort_4_saday.c'
os.system(c_compiler+' '+c_opt_flags+' -c tce_sort_4_saday.c')
os.system('ar -r '+lib_name+' tce_sort_4_saday.o')

for transpose_order in transpose_list:
    dummy = 0
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    driver_name = 'transpose_'+A+B+C+D+'_'+modlabel+num
    print driver_name
    source_name = driver_name+'_driver.F'
    source_file = open(source_name,'w')
    source_file.write('        PROGRAM ARRAYTEST\n')
    source_file.write('        REAL*8 before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
    source_file.write('        REAL*8 after_jeff('+sizechar+')\n')
    source_file.write('        REAL*8 after_hirata('+sizechar+')\n')
    source_file.write('        REAL*8 after_dummy('+sizechar+')\n')
    source_file.write('        REAL*8 after_glass('+sizechar+')\n')
    source_file.write('        REAL*8 after_saday('+sizechar+')\n')
    source_file.write('        REAL*8 factor\n')
    source_file.write('        REAL*8 Tstart,Tfinish,Tspeedup,Tbest\n')
    source_file.write('        REAL*8 Thirata,Tglass,Tsaday,Tjeff\n')
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
    source_file.write('          CALL tce_sort_4(before, after_dummy,\n')
    source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
    source_file.write('     &                    1,2,3,4, 1.0d0)\n')
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
    source_file.write('        Tstart=0.0\n')
    source_file.write('        Tfinish=0.0\n')
    source_file.write('        CALL CPU_TIME(Tstart)\n')
    source_file.write('        DO 37 i = 1, '+count+'\n')
    source_file.write('          CALL saday_sort_4(before, after_saday,\n')
    source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
    source_file.write('     &                    perm(1), perm(2), perm(3), perm(4), factor)\n')
    source_file.write('37      CONTINUE\n')
    source_file.write('        CALL CPU_TIME(Tfinish)\n')
    source_file.write('        Tsaday=(Tfinish-Tstart)\n')
    source_file.write('        DO 38 i = 1, '+sizechar+'\n')
    source_file.write('          IF (after_saday(i).ne.after_hirata(i)) THEN\n')
    source_file.write('            PRINT*,"saday error ",i,after_saday(i),after_hirata(i)\n')
    source_file.write('          ENDIF\n')
    source_file.write('38      CONTINUE\n')
    #source_file.write('        Tstart=0.0\n')
    #source_file.write('        Tfinish=0.0\n')
    #source_file.write('        CALL CPU_TIME(Tstart)\n')
    #source_file.write('        DO 31 i = 1, '+count+'\n')
    #source_file.write('          CALL tce_sort_4kg_(before, after_glass,\n')
    #source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
    #source_file.write('     &                    perm(1), perm(2), perm(3), perm(4), factor)\n')
    #source_file.write('31      CONTINUE\n')
    #source_file.write('        CALL CPU_TIME(Tfinish)\n')
    #source_file.write('        Tglass=(Tfinish-Tstart)\n')
    #source_file.write('        DO 32 i = 1, '+sizechar+'\n')
    #source_file.write('          IF (after_glass(i).ne.after_hirata(i)) THEN\n')
    #source_file.write('          IF (after_glass(i).ne.after_dummy(i)) THEN\n')
    #source_file.write('            PRINT*,"glass error ",i,after_glass(i),after_hirata(i)\n')
    #source_file.write('            PRINT*,"glass error ",i,after_glass(i),after_dummy(i)\n')
    #source_file.write('          ENDIF\n')
    #source_file.write('32      CONTINUE\n')
    source_file.write('        write(6,*) "TESTING TRANPOSE TYPE '+A+B+C+D+'"\n')
    source_file.write('        write(6,*) "==================="\n')
    source_file.write('        write(6,*) "The compilation flags were:"\n')
    for option in range(0,len(fortran_opt_flags.split())):
        source_file.write('        write(6,*) "'+fortran_opt_flags.split()[option]+'"\n')
        
    source_file.write('        write(6,*) "==================="\n')
    source_file.write('        write(6,*) "Hirata Reference = ",Thirata,"seconds"\n')
    source_file.write('        write(6,*) "Saday Reference = ",Tsaday,"seconds"\n')
    #source_file.write('        write(6,*) "Glass Reference = ",Tglass,"seconds"\n')
    source_file.write('        write(6,1001) "Algorithm","Jeff","Speedup","Best",\n')
    source_file.write('     &                    "Best Speedup","Best Speedup"\n')
    source_file.write('        write(6,1001) " "," "," "," "," vs. Hirata "," vs. Saday  "\n')
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
        source_file.write('        DO '+str(100+dummy)+' i = 1, '+count+'\n')
        source_file.write('          CALL '+subroutine_name+'(before, after_jeff,\n')
        source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
        source_file.write('     &                    factor)\n')
        source_file.write(str(100+dummy)+'     CONTINUE\n')
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
            
        #source_file.write('        PRINT*,"Loop '+a+b+c+d+'     ",Tjeff,Tspeedup\n')
        source_file.write('        write(6,1100) "'+nice_dummy+' Loop '+a+b+c+d+' ",\n')
        source_file.write('     &        Tjeff,Tspeedup,Tbest,Thirata/Tbest,Tsaday/Tbest\n')
        #source_file.write('        DO '+str(500+dummy)+' i = 1, '+sizechar+'\n')
        #source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
        #source_file.write('            write(6,*),"transpose is wrong for element = ",i\n')
        #source_file.write('          ENDIF\n')
        #source_file.write(str(500+dummy)+'     CONTINUE\n')
        #source_file.write('        PRINT*,"       i, after_jeff(i),after_hirata(i)"\n')
        source_file.write('        DO '+str(500+dummy)+' i = 1, '+sizechar+'\n')
        source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
        source_file.write('            PRINT*,"jeff error ",i,after_jeff(i),after_hirata(i)\n')
        source_file.write('          ENDIF\n')
        source_file.write(str(500+dummy)+'     CONTINUE\n')
        
    source_file.write('        write(6,1020) "The best loop order is:",\n')
    source_file.write('     &             fastest(1),fastest(2),fastest(3),fastest(4)\n')
    source_file.write('        write(6,1030) "The best time is:",Tbest\n')
    source_file.write('        write(6,1030) "The best speedup is:",Thirata/Tbest\n')
    #source_file.write('        DO 33 i = 1, '+sizechar+'\n')
    #source_file.write('          write(6,1200) "d/h/g/j ",after_dummy(i),after_hirata(i),\n')
    #source_file.write('     &                        after_glass(i),after_jeff(i)\n')
    #source_file.write('33      CONTINUE\n')
    source_file.write('        STOP\n')
    source_file.write(' 1001 format(1x,a13,a12,a15,a9,a18,a18)\n')
    source_file.write(' 1020 format(1x,a30,8x,4i1)\n')
    source_file.write(' 1030 format(1x,a30,1f12.5)\n')
    source_file.write(' 1100 format(1x,a16,5f12.5)\n')
    source_file.write(' 1200 format(1x,a8,4f12.5)\n')
    source_file.write('      END\n')
    source_file.close()
    print fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' '+lib_name+' '+' -o '+exe_dir+driver_name+'.x'
    os.system(fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' '+lib_name+' '+' -o '+exe_dir+driver_name+'.x')
    os.system('mv '+source_name+' '+src_dir)



    
