import fileinput
import string
import sys
import os

c_compiler = 'icc'
c_link_flags = '-g -O1 -xT -march=core2 -mtune=core2 -align'# -strict-ansi'
c_opt_flags = '-g -O3 -xT -march=core2 -mtune=core2 -funroll-loops -align'# -strict-ansi'
fortran_compiler = 'ifort'
fortran_link_flags = '-g -O1 -xT -march=core2 -mtune=core2 -align '
fortran_opt_flags = '-g -O3 -xT -march=core2 -mtune=core2 -funroll-loops -align '
src_dir = '/home/jeff/code/spaghetty/trunk/source/ansi-C/'
exe_dir = '/home/jeff/code/spaghetty/trunk/binary/ansi-C/'

modlabel = 'a4d'

lib_name = 'tce_sort_'+modlabel+'.a'

cind = '    '
ctab = '    '
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
        subroutine_name = 'trans_a4d_'+A+B+C+D+'_loop_'+a+b+c+d+'_'
        source_name = subroutine_name+'.c'
        source_file = open(source_name,'w')
        source_file.write(cind+'#include <stdlib.h>\n')
        source_file.write(cind+'#include <stdio.h>\n\n')
        source_file.write(cind+'void '+subroutine_name+'( double ****unsorted, double ****sorted,\n')
        source_file.write(cind+8*ctab+'int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4, double *p_factor ) {\n\n')
        source_file.write(cind+'int dim1,dim2,dim3,dim4;\n')
        source_file.write(cind+'int j1,j2,j3,j4;\n')
        source_file.write(cind+'int i,j,k,l;\n')
        source_file.write(cind+'double factor;\n')
#        source_file.write(cind+'double**** _sorted;\n\n')
        source_file.write(cind+'factor = *p_factor;\n\n')
        source_file.write(cind+'dim1 = *p_dim1;\n')
        source_file.write(cind+'dim2 = *p_dim2;\n')
        source_file.write(cind+'dim3 = *p_dim3;\n')
        source_file.write(cind+'dim4 = *p_dim4;\n\n')
#        source_file.write(cind+'_sorted = (double ****) malloc (dim1*sizeof(double ***));\n\n')
#        source_file.write(cind+0*ctab+'for (i=0; i<dim1; i++) {\n')
#        source_file.write(cind+1*ctab+'_sorted[i] = (double ***) malloc (dim2*sizeof(double **));\n')
#        source_file.write(cind+0*ctab+'}\n\n')
#        source_file.write(cind+0*ctab+'for (i=0; i<dim1; i++) {\n')
#        source_file.write(cind+1*ctab+'for (j=0; j<dim2; j++) {\n')
#        source_file.write(cind+2*ctab+'_sorted[i][j] = (double **) malloc (dim3*sizeof(double *));\n')
#        source_file.write(cind+1*ctab+'}\n')
#        source_file.write(cind+0*ctab+'}\n\n')
#        source_file.write(cind+0*ctab+'for (i=0; i<dim1; i++) {\n')
#        source_file.write(cind+1*ctab+'for (j=0; j<dim2; j++) {\n')
#        source_file.write(cind+2*ctab+'for (k=0; k<dim3; k++) {\n')
#        source_file.write(cind+3*ctab+'_sorted[i][j][k] = sorted[dim1*dim2*dim3*i + dim2*dim3*j + dim3*k];\n')
#        source_file.write(cind+2*ctab+'}\n')
#        source_file.write(cind+1*ctab+'}\n')
#        source_file.write(cind+0*ctab+'}\n\n')
        #source_file.write(cind+'printf(" ****** BEFORE LOOPS ******\\n");\n')
        source_file.write(cind+'/* pluto start (dim1,dim2,dim3,dim4) */\n')
        source_file.write(cind+0*ctab+'for( j'+a+' = 0; j'+a+'<dim'+a+'; j'+a+'++) {\n')
        source_file.write(cind+1*ctab+'for( j'+b+' = 0; j'+b+'<dim'+b+'; j'+b+'++) {\n')
        source_file.write(cind+2*ctab+'for( j'+c+' = 0; j'+c+'<dim'+c+'; j'+c+'++) {\n')
        source_file.write(cind+3*ctab+'for( j'+d+' = 0; j'+d+'<dim'+d+'; j'+d+'++) {\n')
        #source_file.write(cind+4*ctab+'printf("j'+a+'=%d j'+b+'=%d j'+c+'=%d j'+d+'=%d\\n",j'+a+', j'+b+', j'+c+', j'+d+');\n')
        #source_file.write(cind+4*ctab+'sorted[j4][j3][j2][j1] = unsorted[j1][j2][j3][j4] * factor;\n')
        source_file.write(cind+4*ctab+'sorted[j1][j2][j3][j4] = unsorted[j'+a+'][j'+b+'][j'+c+'][j'+d+'] * factor;\n')
        source_file.write(cind+3*ctab+'}\n')
        source_file.write(cind+2*ctab+'}\n')
        source_file.write(cind+1*ctab+'}\n')
        source_file.write(cind+0*ctab+'}\n')
        source_file.write(cind+'/* pluto end */\n')
        #source_file.write(cind+'printf(" ****** AFTER LOOPS ******\\n");\n')
        source_file.write(cind+'return;\n')
        source_file.write(cind+'}\n\n')
        source_file.close()
        print c_compiler+' '+c_opt_flags+' -c '+source_name
        os.system(c_compiler+' '+c_opt_flags+' -c '+source_name)
        os.system('ar -r '+lib_name+' '+subroutine_name+'.o')
        os.system('rm '+subroutine_name+'.o')
        os.system('mv '+subroutine_name+'.c '+src_dir)

