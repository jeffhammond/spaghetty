#!/usr/bin/python

import fileinput
import string
import sys
import os

# SYSTEM SETTINGS

fortran_compiler = 'bgxlf_r'
fortran_opt_flags = '-O5 -qhot -qprefetch -qcache=auto -qalign=4k -qunroll=yes -qmaxmem=-1 -qalias=noaryovrlp:nopteovrlp -qnoextname -qsmp=omp -qreport=hotlist -c'
src_dir = '/gpfs/home/jhammond/spaghetty/python/archive/src/'
lst_dir = '/gpfs/home/jhammond/spaghetty/python/archive/lst/'

# TUNING SETTINGS

blocking_step =  2
max_blocking  = 3

# FORTRAN SHORTCUTS

f5 = 5*' '
f8 = 8*' '
f9 = 9*' '
f10 = 10*' '
f11 = 11*' '
f12 = 12*' '

# HELPER ROUTINE

def perm(l):
	sz = len(l)
	if sz <= 1:
		return [l]
	return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

# SUBROUTINE GENERATOR

def generate_subroutine(inVec,outVec,blkVec):
	inA=inVec[0]
	inB=inVec[1]
	inC=inVec[2]
	inD=inVec[3]
	outA=inVec[outVec[0]]
	outB=inVec[outVec[1]]
	outC=inVec[outVec[2]]
	outD=inVec[outVec[3]]
	blkAin=blkVec[0]
	blkBin=blkVec[1]
	blkCin=blkVec[2]
	blkDin=blkVec[3]
	blkAout=blkVec[outVec[0]]
	blkBout=blkVec[outVec[1]]
	blkCout=blkVec[outVec[2]]
	blkDout=blkVec[outVec[3]]
	SinA = str(inA+1)
	SinB = str(inB+1)
	SinC = str(inC+1)
	SinD = str(inD+1)
	SoutA = str(outA+1)	
	SoutB = str(outB+1)
	SoutC = str(outC+1)
	SoutD = str(outD+1)
	SblkAin = str(blkAin)
	SblkBin = str(blkBin)
	SblkCin = str(blkCin)
	SblkDin = str(blkDin)
	SblkAout = str(blkAout)
	SblkBout = str(blkBout)
	SblkCout = str(blkCout)
	SblkDout = str(blkDout)
	subroutine_name = 'transpose_in'+SinA+SinB+SinC+SinD+'_out'+SoutA+SoutB+SoutC+SoutD+'_blk'+SblkAin+SblkBin+SblkCin+SblkDin
	source_name = subroutine_name+'.F'
	source_file = open(source_name,'w')
	source_file.write(f8+'subroutine '+subroutine_name+'(unsorted,sorted,\n')
	source_file.write(f5+'&'+2*f8+'dim'+SinA+',dim'+SinB+',dim'+SinC+',dim'+SinD+',factor)\n')
	source_file.write(f8+'implicit none\n')
	source_file.write(f8+'integer dim'+SinA+',dim'+SinB+',dim'+SinC+',dim'+SinD+'\n')
	source_file.write(f8+'integer j'+SinA+',j'+SinB+',j'+SinC+',j'+SinD+'\n')
	source_file.write(f8+'double precision sorted(dim'+SinA+'*dim'+SinB+'*dim'+SinC+'*dim'+SinD+')\n')
	source_file.write(f8+'double precision unsorted(dim'+SinA+'*dim'+SinB+'*dim'+SinC+'*dim'+SinD+')\n')
	source_file.write(f8+'double precision factor\n')
	source_file.write('!$omp parallel do if(dim'+SoutA+'>12) private(j1,j2,j3,j4) schedule(static) \n')
	source_file.write(f8+'do j'+SoutA+' = 1,dim'+SoutA+','+SblkAin+'\n')
	source_file.write(f9+'do j'+SoutB+' = 1,dim'+SoutB+','+SblkBin+'\n')
	source_file.write(f10+'do j'+SoutC+' = 1,dim'+SoutC+','+SblkCin+'\n')
	source_file.write(f11+'do j'+SoutD+' = 1,dim'+SoutD+','+SblkDin+'\n')
	for bA in range(0,blkAin):
		for bB in range(0,blkBin):
			for bC in range(0,blkCin):
				for bD in range(0,blkDin):
					SbVec = [str(bA),str(bB),str(bC),str(bD)]
	    			SbAi = SbVec[0];
	    			SbBi = SbVec[1];
	    			SbCi = SbVec[2];
	    			SbDi = SbVec[3];
	    			SbAo = SbVec[outVec[0]];
	    			SbBo = SbVec[outVec[1]];
	    			SbCo = SbVec[outVec[2]];
	    			SbDo = SbVec[outVec[3]];
	    			source_file.write(f12+'sorted('+SbDi+'+j'+SinD+'+dim'+SinD+'*('+SbCi+'+j'+SinC+'-1+dim'+SinC+'*\n')
	    			source_file.write(f5+'&'+f8+'('+SbBi+'+j'+SinB+'-1+dim'+SinB+'*('+SbAi+'+j'+SinA+'-1)))) = factor*\n')
	    			source_file.write(f5+'&'+f8+'unsorted('+SbDo+'+j'+SoutD+'+dim'+SoutD+'*('+SbCo+'+j'+SoutC+'-1+dim'+SoutC+'*\n')
	    			source_file.write(f5+'&'+f8+'('+SbBo+'+j'+SoutB+'-1+dim'+SoutB+'*('+SbAo+'+j'+SoutA+'-1))))\n')
	    			
					
					
					
	source_file.write(f11+'enddo\n')
	source_file.write(f10+'enddo\n')
	source_file.write(f9+'enddo\n')
	source_file.write(f8+'enddo\n')
	source_file.write('!$omp end parallel do \n')
	source_file.write(f8+'return\n')
	source_file.write(f8+'end\n')
	source_file.close()
	os.system(fortran_compiler+' '+fortran_opt_flags+' '+source_name)
	os.system('ar -r tce_sort_jeff.a '+subroutine_name+'.o')
	os.system('mv '+subroutine_name+'.F '+src_dir)
	os.system('mv '+subroutine_name+'.lst '+lst_dir)
	os.system('rm '+subroutine_name+'.o')


# TESTER

#generate_subroutine([0,1,2,3],[0,1,2,3],[1,1,1,1])
#generate_subroutine([0,1,2,3],[0,1,2,3],[1,1,1,2])
#generate_subroutine([0,1,2,3],[0,1,2,3],[1,1,2,1])
#generate_subroutine([0,1,2,3],[0,1,2,3],[1,1,2,2])

inVec = [2,3,0,1]
for permVec in perm(inVec):
	for block3 in range(1,2,2):
		for block4 in range(2,17,2):
                	print 'blocking = '+str(block3)+' '+str(block4)
			generate_subroutine(inVec,permVec,[1,1,block3,block4])



