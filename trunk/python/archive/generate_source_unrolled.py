import fileinput
import string
import sys
import os

blocking_step =  2
max_blocking  = 10

fortran_compiler = 'ifort'
fortran_opt_flags = '-O1 -unroll0 -pad -mtune=core2 -msse3 -c'
src_dir = '/home/jeff/code/Transpose/autotune/autofiles/src/'

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['3','4','1','2']
loopsA = ['1','3','2','4']
loopsB = ['3','1','4','2']

transpose  = [indices]
loop_order = [loopsA]#,loopsB]

for transpose_order in transpose:
	A = transpose_order[0]
	B = transpose_order[1]
	C = transpose_order[2]
	D = transpose_order[3]
	for loop_order in loop_order:
		a = loop_order[0]
		b = loop_order[1]
		c = loop_order[2]
		d = loop_order[3]
		for first_blocking in range(2,max_blocking,blocking_step):
			for second_blocking in range(2,max_blocking,blocking_step):
				subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d+'_blocked_'+str(first_blocking)+'x'+str(second_blocking)
				source_name = subroutine_name+'.F'
				#print source_name
				source_file = open(source_name,'w')
				source_file.write('        subroutine '+subroutine_name+'(unsorted,sorted,\n')
				source_file.write('     &                           dim1,dim2,dim3,dim4,factor)\n')
				source_file.write('        implicit none\n')
				source_file.write('        integer dim1,dim2,dim3,dim4\n')
				#source_file.write('        integer old_offset,new_offset\n')
				source_file.write('        integer j1,j2,j3,j4\n')
				source_file.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
				source_file.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
				source_file.write('        double precision factor\n')
				source_file.write('        do j'+a+' = 1,dim'+a+'\n')
				source_file.write('         do j'+b+' = 1,dim'+b+'\n')
				source_file.write('          do j'+c+' = 1,dim'+c+','+str(first_blocking)+'\n')
				source_file.write('           do j'+d+' = 1,dim'+d+','+str(second_blocking)+'\n')
				for first_block in range(0,first_blocking):
					for second_block in range(0,second_blocking): 
						source_file.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = factor*\n')
						source_file.write('     &         unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')


				source_file.write('           enddo\n')
				source_file.write('          enddo\n')
				source_file.write('         enddo\n')
				source_file.write('        enddo\n')
				source_file.write('        return\n')
				source_file.write('        end\n')
				source_file.close()
				os.system(fortran_compiler+' '+fortran_opt_flags+' '+source_name)
				os.system('ar -r tce_sort_jeff.a '+subroutine_name+'.o')
				os.system('rm '+subroutine_name+'.o')
				os.system('mv '+subroutine_name+'.F '+src_dir)
                
                
                
                

