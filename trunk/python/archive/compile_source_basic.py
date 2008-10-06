import fileinput
import string
import sys
import os

# Goldstone old
fortran_compiler = 'ifort'
fortran_link_flags = '-O1 -mtune=core2 -march=core2 -align'
fortran_opt_flags = '-O3 -mtune=core2 -march=core2 -align'
src_dir = '/home/jeff/code/spaghetty/trunk/source/fortran77/'
lib_name = 'tce_sort_f77.a'

modlabel = '_tuned'

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['4','3','2','1']

#all_permutations = perm(indices)
#all_permutations = [indices]

transpose_list = [indices]
#transpose_list = perm(indices)
#loop_list = [indices]
#loop_list = perm(indices)
loop_list = [['3','2','4','1']]

for transpose_order in transpose_list:
	A = transpose_order[0]
	B = transpose_order[1]
	C = transpose_order[2]
	D = transpose_order[3]
	for loop_order in loop_list:
		a = loop_order[0]
		b = loop_order[1]
		c = loop_order[2]
		d = loop_order[3]
		subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d+modlabel
		source_name = subroutine_name+'.F'
		print fortran_compiler+' '+fortran_opt_flags+' -c '+src_dir+source_name
		os.system(fortran_compiler+' '+fortran_opt_flags+' -c '+src_dir+source_name)
		os.system('ar -r '+lib_name+' '+subroutine_name+'.o')
		os.system('rm '+subroutine_name+'.o')
		#os.system('mv '+subroutine_name+'.F '+src_dir)

