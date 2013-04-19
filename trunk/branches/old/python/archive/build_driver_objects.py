import fileinput
import string
import sys
import os

fortran_compiler = '/bgsys/drivers/ppcfloor/comm/bin/mpixlf77_r'
fortran_no_opt_flags = '-O3 -qnoipa -qnounroll -qmaxmem=8192 -qnoextname -qnosmp -c'
fortran_opt_flags = '-O3 -qunroll=yes -qmaxmem=8192 -qnoextname -qnosmp -c'
src_dir = '/gpfs/home/jhammond/spaghetty/python/archive/src/'
exe_dir = '/gpfs/home/jhammond/spaghetty/python/archive/exe/'

count = '100'
ranks = ['32','32','32','32']
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])
sizechar = str(size)

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['1','2','3','4']

#all_permutations = perm(indices)
#all_permutations = [indices]

transpose_list = perm(indices)
loop_list = perm(indices)

print fortran_compiler+fortran_opt_flags+' tce_sort_hirata.F'
os.system(fortran_compiler+' '+fortran_opt_flags+' tce_sort_hirata.F')
os.system('ar -r tce_sort_jeff.a tce_sort_hirata.o')

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
#	source_file.write('        PROGRAM ARRAYTEST\n')
#	source_file.write('        DOUBLE PRECISION FUNCTION '+driver_name+'()\n')
	source_file.write('        SUBROUTINE '+driver_name+'_driver()\n')
        source_file.write('        REAL*8 before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
        source_file.write('        REAL*8 after_jeff('+sizechar+')\n')
        source_file.write('        REAL*8 after_hirata('+sizechar+')\n')
        source_file.write('        REAL*8 factor\n')
        source_file.write('        REAL*4 Tstart,Tfinish,Thirata,Tjeff,Tspeedup\n')
        source_file.write('        INTEGER*4 i,j,k,l\n')
        source_file.write('        INTEGER*4 aSize(4)\n')
        source_file.write('        INTEGER*4 perm(4)\n')
#        source_file.write('        EXTERNAL tce_sort_4\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_1234\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_1243\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_1324\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_1342\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_1423\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_1432\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_2134\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_2143\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_2314\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_2341\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_2413\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_2431\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_3124\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_3142\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_3214\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_3241\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_3412\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_3421\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_4123\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_4132\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_4213\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_4231\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_4312\n')
#        source_file.write('        EXTERNAL '+driver_name+'_loop_4321\n')
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
#        source_file.write('        CALL CPU_TIME(Tstart)\n')
        source_file.write('        Tstart=rtc()\n')
        source_file.write('        DO 30 i = 1, '+count+'\n')
        source_file.write('          CALL tce_sort_4(before, after_hirata,\n')
        source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
        source_file.write('     &                    perm(1), perm(2), perm(3), perm(4), factor)\n')
        source_file.write('30      CONTINUE\n')
#        source_file.write('        CALL CPU_TIME(Tfinish)\n')
        source_file.write('        Tfinish=rtc()\n')
        source_file.write('        Thirata=(Tfinish-Tstart)\n')
        source_file.write('        PRINT*,"TESTING TRANPOSE TYPE '+A+B+C+D+'"\n')
        source_file.write('        PRINT*,"Hirata Reference = ",Thirata,"seconds"\n')
        source_file.write('        PRINT*,"Algorithm         Jeff           "\n')
	for loop_order in loop_list:
                dummy = dummy+1
		a = loop_order[0]
		b = loop_order[1]
		c = loop_order[2]
		d = loop_order[3]
	        subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d
                source_file.write('        Tstart=0.0\n')
                source_file.write('        Tfinish=0.0\n')
#                source_file.write('        CALL CPU_TIME(Tstart)\n')
                source_file.write('        Tstart=rtc()\n')
                source_file.write('        DO '+str(100+dummy)+' i = 1, '+count+'\n')
                source_file.write('          CALL '+subroutine_name+'(before, after_jeff,\n')
                source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
                source_file.write('     &                    factor)\n')
                source_file.write(str(100+dummy)+'     CONTINUE\n')
#                source_file.write('        CALL CPU_TIME(Tfinish)\n')
                source_file.write('        Tfinish=rtc()\n')
                source_file.write('        Tjeff=(Tfinish-Tstart)\n')
                source_file.write('        Tspeedup=Tjeff/Thirata\n')
                source_file.write('        PRINT*,"Loop '+a+b+c+d+'     ",Tjeff,Tspeedup\n')
	        source_file.write('        DO '+str(500+dummy)+' i = 1, '+sizechar+'\n')
#                if a==A and b==B and c==C and d==D:
#	                source_file.write('        PRINT*,"             Jeff        Hirata"\n')
#        	        source_file.write('          write(6,1),i,after_jeff(i),after_hirata(i)\n')
#                	source_file.write('    1     format(1x,i8,2f12.5)\n')
#
	        source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
        	source_file.write('            PRINT*,"transpose is wrong for element = ",i\n')
                source_file.write('          ENDIF\n')
	        source_file.write(str(500+dummy)+'     CONTINUE\n')

#        source_file.write('        RETURN Tjeff\n')
        source_file.write('        STOP\n')
        source_file.write('      END\n')
	source_file.close()
	os.system('mv '+driver_name+'_driver.F '+src_dir)
	print fortran_compiler+' '+fortran_no_opt_flags+' src/'+driver_name+'_driver.F'
	os.system(fortran_compiler+' '+fortran_no_opt_flags+' src/'+driver_name+'_driver.F')
	os.system('ar -r tce_sort_jeff.a '+driver_name+'_driver.o')
	os.system('rm '+driver_name+'_driver.o')




