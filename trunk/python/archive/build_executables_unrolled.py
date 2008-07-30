import fileinput
import string
import sys
import os

fortran_compiler = '/bgsys/drivers/ppcfloor/comm/bin/mpixlf77_r'
fortran_link_flags = '-O3 -qnoipa -qnounroll -qmaxmem=8192 -qnoextname -qnosmp'
fortran_opt_flags = '-O5 -qunroll=yes -qmaxmem=8192 -qnoextname -qnosmp -c'
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

def generate_driver(inVec,outVec,blkVec):
        dummy = 0
        inA=str(inVec[0]+1)
        inB=str(inVec[1]+1)
        inC=str(inVec[2]+1)
        inD=str(inVec[3]+1)
	driver_name = 'transpose_'+inA+inB+inC+inD
	print driver_name
	source_name = driver_name+'_driver.F'
        outA=str(inVec[outVec[0]]+1)
        outB=str(inVec[outVec[1]]+1)
        outC=str(inVec[outVec[2]]+1)
        outD=str(inVec[outVec[3]]+1)
        blkAin=str(blkVec[0])
        blkBin=str(blkVec[1])
        blkCin=str(blkVec[2])
        blkDin=str(blkVec[3])
        blocking='_blk'+blkAin+blkBin+blkCin+blkDin
	source_file = open(source_name,'w')
	source_file.write('        PROGRAM ARRAYTEST\n')
        source_file.write('        REAL*8 before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
        source_file.write('        REAL*8 after_jeff('+sizechar+')\n')
        source_file.write('        REAL*8 after_hirata('+sizechar+')\n')
        source_file.write('        REAL*8 factor\n')
        source_file.write('        REAL*8 Tstart,Tfinish,Thirata,Tjeff,Tspeedup\n')
        source_file.write('        INTEGER*4 i,j,k,l\n')
        source_file.write('        INTEGER*4 aSize(4)\n')
        source_file.write('        INTEGER*4 perm(4)\n')
        source_file.write('        aSize(1) = '+ranks[0]+'\n')
        source_file.write('        aSize(2) = '+ranks[1]+'\n')
        source_file.write('        aSize(3) = '+ranks[2]+'\n')
        source_file.write('        aSize(4) = '+ranks[3]+'\n')
        source_file.write('        perm(1) = '+inA+'\n')
        source_file.write('        perm(2) = '+inB+'\n')
        source_file.write('        perm(3) = '+inC+'\n')
        source_file.write('        perm(4) = '+inD+'\n')
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
        source_file.write('        Tfinish=rtc()\n')
        source_file.write('        Thirata=(Tfinish-Tstart)\n')
        source_file.write('        PRINT*,"TESTING TRANPOSE TYPE '+inA+inB+inC+inD+'"\n')
        source_file.write('        PRINT*,"Hirata Reference = ",Thirata,"seconds"\n')
        source_file.write('        PRINT*,"Algorithm         Jeff           "\n')
	for loop_order in [outVec]:
                dummy = dummy+1
		a = loop_order[0]
		b = loop_order[1]
		c = loop_order[2]
		d = loop_order[3]
	        subroutine_name = 'transpose_in'+inA+inB+inC+inD+'_out'+outA+outB+outC+outD+blocking
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
                source_file.write('        Tspeedup=Thirata/Tjeff\n')
                source_file.write('        PRINT*,"Loop '+outA+outB+outC+outD+'     ",Tjeff,Tspeedup\n')
	        source_file.write('        DO '+str(500+dummy)+' i = 1, '+sizechar+'\n')
	        source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
        	source_file.write('            PRINT*,"error at position ",i,after_jeff(i),after_hirata(i)\n')
                source_file.write('          ENDIF\n')
	        source_file.write(str(500+dummy)+'     CONTINUE\n')

        source_file.write('        STOP\n')
        source_file.write('      END\n')
	source_file.close()
	print fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' tce_sort_jeff.a '+' -o '+exe_dir+driver_name+'.x'
	os.system(fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' tce_sort_jeff.a '+' -o '+exe_dir+driver_name+'.x')
	os.system('mv '+source_name+' '+src_dir)


generate_driver([0,1,2,3],[0,1,2,3],[1,1,1,1])

