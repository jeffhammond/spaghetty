import fileinput
import string
import sys
import os

blocking_step =  2
max_blocking  = 3

fortran_compiler = 'ifort'
fortran_opt_flags = '-O1 -unroll0 -pad -mtune=core2 -msse3 -c'
#src_dir = '/home/jeff/code/Transpose/autotune/autofiles/src/'
src_dir = '/home/jeff/code/spaghetty/trunk/python/archive/src/'
f5 = 5*' '
f8 = 8*' '
f9 = 9*' '
f10 = 10*' '
f11 = 11*' '
f12 = 12*' '

def perm(l):
	sz = len(l)
	if sz <= 1:
		return [l]
	return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

transpose = [[2,3,0,1]]
looporder = [[0,2,1,3]]

for transpose_order in transpose:
	Ta = str(transpose_order[0])
	Tb = str(transpose_order[1])
	Tc = str(transpose_order[2])
	Td = str(transpose_order[3])
	It = ['j'+Ta,'j'+Tb,'j'+Tc,'j'+Td]
	for loop_order in looporder:
		La = str(transpose_order[loop_order[0]])
		Lb = str(transpose_order[loop_order[1]])
		Lc = str(transpose_order[loop_order[2]])
		Ld = str(transpose_order[loop_order[3]])
		Il = [ It[loop_order[0]], It[loop_order[1]], It[loop_order[2]], It[loop_order[3]] ]
		print '--------------------'
		print Ta,Tb,Tc,Td
		print La,Lb,Lc,Ld
		for first_blocking in range(2,max_blocking,blocking_step):
			for second_blocking in range(2,max_blocking,blocking_step):
				subroutine_name = 'transpose_'+Ta+Tb+Tc+Td+'_loop_'+La+Lb+Lc+Ld+'_blocked_'+str(first_blocking)+'x'+str(second_blocking)
				source_name = subroutine_name+'.F'
				#print source_name
				source_file = open(source_name,'w')
				source_file.write(f8+'subroutine '+subroutine_name+'(unsorted,sorted,\n')
				source_file.write(f5+'&'+2*f8+'dim'+Ta+',dim'+Tb+',dim'+Tc+',dim'+Td+',factor)\n')
				source_file.write(f8+'implicit none\n')
				source_file.write(f8+'integer dim'+Ta+',dim'+Tb+',dim'+Tc+',dim'+Td+'\n')
				source_file.write(f8+'integer j'+Ta+',j'+Tb+',j'+Tc+',j'+Td+'\n')
				source_file.write(f8+'double precision sorted(dim'+Ta+'*dim'+Tb+'*dim'+Tc+'*dim'+Td+')\n')
				source_file.write(f8+'double precision unsorted(dim'+Ta+'*dim'+Tb+'*dim'+Tc+'*dim'+Td+')\n')
				source_file.write(f8+'double precision factor\n')
				source_file.write(f8+'do j'+La+' = 1,dim'+La+'\n')
				source_file.write(f9+'do j'+Lb+' = 1,dim'+Lb+'\n')
				source_file.write(f10+'do j'+Lc+' = 1,dim'+Lc+','+str(first_blocking)+'\n')
				source_file.write(f11+'do j'+Ld+' = 1,dim'+Ld+','+str(second_blocking)+'\n')
				for first_block in range(0,first_blocking):
					for second_block in range(0,second_blocking):
						source_file.write(f12+'sorted('+'j'+Td+'+dim'+Td+'*(j'+Tc+'-1+dim'+Tc+'*(j'+Tb+'-1+dim'+Tb+'*(j'+Ta+'-1)))) = factor*\n')
						source_file.write(f5+'&'+f8+'unsorted(j'+Ld+'+dim'+Ld+'*(j'+Lc+'-1+dim'+Lc+'*(j'+Lb+'-1+dim'+Lb+'*(j'+La+'-1))))\n')


				source_file.write(f11+'enddo\n')
				source_file.write(f10+'enddo\n')
				source_file.write(f9+'enddo\n')
				source_file.write(f8+'enddo\n')
				source_file.write(f8+'return\n')
				source_file.write(f8+'end\n')
				source_file.close()
				os.system(fortran_compiler+' '+fortran_opt_flags+' '+source_name)
				os.system('ar -r tce_sort_jeff.a '+subroutine_name+'.o')
				os.system('rm '+subroutine_name+'.o')
				os.system('mv '+subroutine_name+'.F '+src_dir)
				
				
				
				
