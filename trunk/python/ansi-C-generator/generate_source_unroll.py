import fileinput
import string
import sys
import os

c_compiler = 'icc'
c_link_flags = '-O1 -xT -march=core2 -mtune=core2 -align -strict-ansi'
c_opt_flags = '-O3 -xT -march=core2 -mtune=core2 -funroll-loops -align -strict-ansi'
fortran_compiler = 'ifort'
fortran_link_flags = '-O1 -xT -march=core2 -mtune=core2 -align '
fortran_opt_flags = '-O3 -xT -march=core2 -mtune=core2 -funroll-loops -align '
src_dir = '/home/jeff/code/spaghetty/trunk/source/ansi-C/'
obj_dir = '/home/jeff/code/spaghetty/trunk/object/ansi-C/'
exe_dir = '/home/jeff/code/spaghetty/trunk/binary/ansi-C/'

modlabel = 'unroll'
unrolling = 4

lib_name = 'tce_sort_'+modlabel+'.a'

cind = '    '
ctab = '    '
def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['1','2','3','4']
#indices = ['4','3','2','1']
all_permutations = perm(['1','2','3','4'])

#transpose_list = [indices]
#transpose_list = perm(indices)
transpose_list = all_permutations
#transpose_list = [['2','1','3','4'],['1','2','4','3']]

#loop_list = [indices]
#loop_list = perm(indices)
loop_list = all_permutations

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
      if d is '4' and D is '4':
        subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d+'_'
        source_name = subroutine_name+'.c'
        source_file = open(source_name,'w')
        source_file.write(cind+'#include <math.h>\n\n')
        source_file.write(cind+'void '+subroutine_name+'( double *unsorted, double *sorted,\n')
        source_file.write(cind+8*ctab+'int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4, double *p_factor ) {\n\n')
        source_file.write(cind+'int dim1,dim2,dim3,dim4;\n')
        source_file.write(cind+'int dim1mod,dim2mod,dim3mod,dim4mod;\n')
        #source_file.write(cind+'int dim1rem,dim2rem,dim3rem,dim4rem;\n')
        source_file.write(cind+'unsigned int old_offset,new_offset;\n')
        source_file.write(cind+'unsigned int j1,j2,j3,j4;\n')
        source_file.write(cind+'double factor;\n')
        source_file.write(cind+'factor = *p_factor;\n\n')
        source_file.write(cind+'dim1 = *p_dim1;\n')
        source_file.write(cind+'dim2 = *p_dim2;\n')
        source_file.write(cind+'dim3 = *p_dim3;\n')
        source_file.write(cind+'dim4 = *p_dim4;\n\n')
        source_file.write(cind+'dim1mod = (int) floor( (float)dim1 / (float) '+str(unrolling)+');\n')
        source_file.write(cind+'dim2mod = (int) floor( (float)dim2 / (float) '+str(unrolling)+');\n')
        source_file.write(cind+'dim3mod = (int) floor( (float)dim3 / (float) '+str(unrolling)+');\n')
        source_file.write(cind+'dim4mod = (int) floor( (float)dim4 / (float) '+str(unrolling)+');\n\n')
        #source_file.write(cind+'dim1rem = dim1 - dim1mod;\n')
        #source_file.write(cind+'dim2rem = dim2 - dim2mod;\n')
        #source_file.write(cind+'dim3rem = dim3 - dim3mod;\n')
        #source_file.write(cind+'dim4rem = dim4 - dim4mod;\n\n')
        source_file.write(cind+'/* pluto start (dim1,dim2,dim3,dim4) */\n')
        source_file.write(cind+0*ctab+'#pragma ivdep\n')
        source_file.write(cind+0*ctab+'#pragma parallel\n')
        source_file.write(cind+0*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
        source_file.write(cind+0*ctab+'#pragma unroll\n')
        source_file.write(cind+0*ctab+'for( j'+a+' = 0; j'+a+'<dim'+a+'; j'+a+'++) {\n')
        source_file.write(cind+1*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
        source_file.write(cind+1*ctab+'#pragma unroll\n')
        source_file.write(cind+1*ctab+'for( j'+b+' = 0; j'+b+'<dim'+b+'; j'+b+'++) {\n')
        source_file.write(cind+2*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
        source_file.write(cind+2*ctab+'#pragma unroll\n')
        source_file.write(cind+2*ctab+'#pragma vector always\n')
        source_file.write(cind+2*ctab+'for( j'+c+' = 0; j'+c+'<dim'+c+'; j'+c+'++) {\n')
        if d is '4' and D is '4':
                source_file.write(cind+3*ctab+'#pragma loop count min(4) max(20) avg(10)\n')
                source_file.write(cind+3*ctab+'#pragma unroll\n')
	        source_file.write(cind+3*ctab+'#pragma vector always\n')
                source_file.write(cind+3*ctab+'for( j'+d+' = 0; j'+d+'<dim'+d+'mod; j'+d+'+='+str(unrolling)+') {\n')
	        for offset in range(0,unrolling):
		        source_file.write(cind+4*ctab+'sorted['+str(offset)+'+j'+D+'+dim'+D+'*(j'+C+'+dim'+C+'*(j'+B+'+dim'+B+'*j'+A+'))] = unsorted['+str(offset)+'+j4+dim4*(j3+dim3*(j2+dim2*j1))] * factor;\n')

                source_file.write(cind+3*ctab+'}\n')
                source_file.write(cind+3*ctab+'#pragma loop count min(0) max(8) avg(2)\n')
                source_file.write(cind+3*ctab+'#pragma unroll\n')
	        source_file.write(cind+3*ctab+'#pragma vector always\n')
                source_file.write(cind+3*ctab+'for( j'+d+' = dim'+d+'mod; j'+d+'<dim'+d+'; j'+d+'++) {\n')
		source_file.write(cind+4*ctab+'sorted[j'+D+'+dim'+D+'*(j'+C+'+dim'+C+'*(j'+B+'+dim'+B+'*j'+A+'))] = unsorted[j4+dim4*(j3+dim3*(j2+dim2*j1))] * factor;\n')
                source_file.write(cind+3*ctab+'}\n')

        if d is not '4' or D is not '4':
                source_file.write(cind+3*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
                source_file.write(cind+3*ctab+'#pragma unroll\n')
	        source_file.write(cind+3*ctab+'#pragma vector always\n')
                source_file.write(cind+3*ctab+'for( j'+d+' = 0; j'+d+'<dim'+d+'; j'+d+'++) {\n')
		source_file.write(cind+4*ctab+'sorted[j'+D+'+dim'+D+'*(j'+C+'+dim'+C+'*(j'+B+'+dim'+B+'*j'+A+'))] = unsorted[j4+dim4*(j3+dim3*(j2+dim2*j1))] * factor;\n')
                source_file.write(cind+3*ctab+'}\n')

        source_file.write(cind+2*ctab+'}\n')
        source_file.write(cind+1*ctab+'}\n')
        source_file.write(cind+'}\n')
        source_file.write(cind+'/* pluto end */\n')
        source_file.write(cind+'return;\n')
        source_file.write(cind+'}\n\n')
        source_file.close()
        print c_compiler+' '+c_opt_flags+' -c '+source_name
        os.system(c_compiler+' '+c_opt_flags+' -c '+source_name)
        os.system('ar -r '+lib_name+' '+subroutine_name+'.o')
        os.system('mv '+subroutine_name+'.o '+obj_dir)
        os.system('mv '+subroutine_name+'.c '+src_dir)

