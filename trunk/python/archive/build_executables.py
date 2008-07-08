import fileinput
import string
import sys
import os

fortran_compiler = 'ifort'
fortran_opt_flags = '-O3 -pad -unroll-aggressive -mtune=core2 -msse3 -c'
src_dir = '/home/jeff/code/Transpose/autotune/autofiles/src/'
exe_dir = '/home/jeff/code/Transpose/autotune/autofiles/exe/'

count = '50'
ranks = ['32','32','32','32']
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])
sizechar = str(size)

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['1','2','3','4']

all_permutations = perm(indices)
#all_permutations = [indices]

#os.system('ifort -O3 -pad -unroll-aggressive -mtune=core2 -msse3 -c tce_sort_hirata.F')
#os.system('icc -O3 -pad -unroll-aggressive -mtune=core2 -msse3 -c tce_sort_saday.c')

for transpose_order in all_permutations:
	A = transpose_order[0]
	B = transpose_order[1]
	C = transpose_order[2]
	D = transpose_order[3]
	print_header = 1
	for loop_order in all_permutations:
		a = loop_order[0]
		b = loop_order[1]
		c = loop_order[2]
		d = loop_order[3]
		subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d
		print subroutine_name
		source_name = subroutine_name+'_driver.F'
		source_file = open(source_name,'w')
		source_file.write('        PROGRAM ARRAYTEST\n')
                source_file.write('        REAL*8 before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
                source_file.write('        REAL*8 after_jeff('+sizechar+')\n')
                source_file.write('        REAL*8 after_hirata('+sizechar+')\n')
                source_file.write('        REAL*8 after_saday('+sizechar+')\n')
#                source_file.write('        REAL*8 factor,Atemp,Btemp\n')
                source_file.write('        REAL*8 factor\n')
                source_file.write('        REAL*4 Tstart,Tfinish,Tsaday,Thirata,Tjeff\n')
                source_file.write('        INTEGER*4 i,j,k,l\n')
#                source_file.write('        INTEGER*4 offset\n')
                source_file.write('        INTEGER*4 aSize(4)\n')
                source_file.write('        INTEGER*4 perm(4)\n')
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
                source_file.write('        Tstart=0.0\n')
                source_file.write('        Tfinish=0.0\n')
                source_file.write('        CALL CPU_TIME(Tstart)\n')
                source_file.write('        DO 30 i = 1, '+count+'\n')
                source_file.write('          CALL tce_sort_hirata(before, after_hirata,\n')
                source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
                source_file.write('     &                    perm(1), perm(2), perm(3), perm(4), factor)\n')
                source_file.write('30      CONTINUE\n')
                source_file.write('        CALL CPU_TIME(Tfinish)\n')
                source_file.write('        Thirata=(Tfinish-Tstart)\n')
                source_file.write('        Tstart=0.0\n')
                source_file.write('        Tfinish=0.0\n')
                source_file.write('        CALL CPU_TIME(Tstart)\n')
                source_file.write('        DO 31 i = 1, '+count+'\n')
                source_file.write('          CALL tce_sort_4(before, after_saday,\n')
                source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
                source_file.write('     &                    perm(1), perm(2), perm(3), perm(4), factor)\n')
                source_file.write('31      CONTINUE\n')
                source_file.write('        CALL CPU_TIME(Tfinish)\n')
                source_file.write('        Tsaday=(Tfinish-Tstart)\n')
                source_file.write('        Tstart=0.0\n')
                source_file.write('        Tfinish=0.0\n')
                source_file.write('        CALL CPU_TIME(Tstart)\n')
                source_file.write('        DO 32 i = 1, '+count+'\n')
                source_file.write('          CALL '+subroutine_name+'(before, after_jeff,\n')
                source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
                source_file.write('     &                    factor)\n')
                source_file.write('32      CONTINUE\n')
                source_file.write('        CALL CPU_TIME(Tfinish)\n')
                source_file.write('        Tjeff=(Tfinish-Tstart)\n')
                if print_header:
                	source_file.write('        PRINT*,"TESTING TRANPOSE TYPE '+A+B+C+D+'"\n')
	                source_file.write('        PRINT*,"Algorithm         Jeff           Saday        Hirata"\n')

                source_file.write('        PRINT*,"Loop '+a+b+c+d+'     ",Tjeff,Tsaday,Thirata\n')
	        source_file.write('        DO 200 i = 1, '+sizechar+'\n')
#                if a==A and b==B and c==C and d==D:
#	                source_file.write('        PRINT*,"             Jeff        Saday      Hirata"\n')
#        	        source_file.write('          write(6,1),i,after_jeff(i),after_saday(i),after_hirata(i)\n')
#                	source_file.write('    1     format(1x,i8,3f12.5)\n')
#
	        source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
        	source_file.write('            PRINT*,"transpose is wrong for element = ",i\n')
                source_file.write('          ENDIF\n')
	        source_file.write('200     CONTINUE\n')
                source_file.write('        STOP\n')
                source_file.write('      END\n')
		source_file.close()
		os.system(fortran_compiler+' '+' '+source_name+' tce_sort_jeff.a '+'tce_sort_saday.o tce_sort_hirata.o'+' -o '+exe_dir+subroutine_name+'.x')
		os.system('mv '+source_name+' '+src_dir)
		print_header = 0

