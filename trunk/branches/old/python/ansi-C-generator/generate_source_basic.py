import fileinput
import string
import sys
import os

#c_compiler = 'icc'
#c_link_flags = '-O1 -xT -march=core2 -mtune=core2 -align'
#c_opt_flags = '-O3 -xT -march=core2 -mtune=core2 -align -funroll-loops -prefetch -ssp -vec-report3 -opt-report 3'
#c_opt_flags = '-O3 -xT -march=core2 -mtune=core2 -align -funroll-loops -prefetch -ssp'
#c_compiler = 'gcc'
#c_link_flags = '-O1 -march=pentium4 -mtune=pentium4 '
#c_opt_flags = '-O3 -march=pentium4 -mtune=pentium4 -funroll-loops '
#fortran_compiler = 'ifort'
#fortran_link_flags = '-O1 -xT -march=core2 -mtune=core2 -align'
#fortran_opt_flags = '-O3 -xT -march=core2 -mtune=core2 -funroll-loops -align'
#fortran_compiler = 'gfortran'
#fortran_link_flags = '-O1 -march=pentium4 -mtune=pentium4 '
#fortran_opt_flags = '-O3 -march=pentium4 -mtune=pentium4 -funroll-loops '

c_compiler = 'gcc'
c_opt_flags = '-g -O3'
c_link_flags = '-g -O3'
fortran_compiler = 'gfortran'
fortran_opt_flags = '-g -O3'
fortran_link_flags = '-g -O3'

src_dir = '/home/jeff/eclipse/SPAGHETTY/source/ansi-C/'
obj_dir = '/home/jeff/eclipse/SPAGHETTY/object/ansi-C/'
exe_dir = '/home/jeff/eclipse/SPAGHETTY/binary/ansi-C/'

#modlabel = 'realA'
modlabel = 'gcc'

factor_version = '_plus'
#factor_version = '_minus'
#factor_version = '_phalf'
#factor_version = '_mhalf'
#factor_version = '_frac'

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
#transpose_list = ['1243','1432','2143','2413','2431','3124','3214','3241','4123','4132','4231','4321']
transpose_list = all_permutations

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
        subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d+factor_version+'_'
        source_name = subroutine_name+'.c'
        source_file = open(source_name,'w')
        source_file.write(cind+'void '+subroutine_name+'( double *unsorted, double *sorted,\n')
        if (factor_version == '_plus') or (factor_version == '_minus'):
            source_file.write(cind+8*ctab+'int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4 ) {\n\n')
        elif (factor_version == '_phalf') or (factor_version == '_mhalf'):
            source_file.write(cind+8*ctab+'int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4 ) {\n\n')
        else:
            source_file.write(cind+8*ctab+'int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4, double *p_factor ) {\n\n')
            source_file.write(cind+'double factor = *p_factor;\n\n')
        source_file.write(cind+'int dim1,dim2,dim3,dim4;\n')
        source_file.write(cind+'unsigned int old_offset,new_offset;\n')
        source_file.write(cind+'unsigned int j1,j2,j3,j4;\n')
        source_file.write(cind+'dim1 = *p_dim1;\n')
        source_file.write(cind+'dim2 = *p_dim2;\n')
        source_file.write(cind+'dim3 = *p_dim3;\n')
        source_file.write(cind+'dim4 = *p_dim4;\n\n')
        #source_file.write(cind+'/* pluto start (dim1,dim2,dim3,dim4) */\n')
        source_file.write(cind+0*ctab+'#pragma ivdep\n')
        source_file.write(cind+0*ctab+'#pragma prefetch\n')
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
        source_file.write(cind+3*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
        source_file.write(cind+3*ctab+'#pragma unroll\n')
        source_file.write(cind+3*ctab+'#pragma vector always\n')
        source_file.write(cind+3*ctab+'for( j'+d+' = 0; j'+d+'<dim'+d+'; j'+d+'++) {\n')
        source_file.write(cind+4*ctab+'old_offset = j4+dim4*(j3+dim3*(j2+dim2*(j1)));\n')
        source_file.write(cind+4*ctab+'new_offset = j'+D+'+dim'+D+'*(j'+C+'+dim'+C+'*(j'+B+'+dim'+B+'*(j'+A+')));\n')
        if (factor_version == '_plus'):
            source_file.write(cind+4*ctab+'sorted[new_offset] = unsorted[old_offset];\n')
        elif (factor_version == '_minus'):
            source_file.write(cind+4*ctab+'sorted[new_offset] = -unsorted[old_offset];\n')
        elif (factor_version == '_phalf'):
            source_file.write(cind+4*ctab+'sorted[new_offset] = 0.5*unsorted[old_offset];\n')
        elif (factor_version == '_mhalf'):
            source_file.write(cind+4*ctab+'sorted[new_offset] = -0.5*unsorted[old_offset];\n')
        else:
            source_file.write(cind+4*ctab+'sorted[new_offset] = factor*unsorted[old_offset];\n')
        source_file.write(cind+3*ctab+'}\n')
        source_file.write(cind+2*ctab+'}\n')
        source_file.write(cind+1*ctab+'}\n')
        source_file.write(cind+'}\n')
        #source_file.write(cind+'/* pluto end */\n')
        source_file.write(cind+'return;\n')
        source_file.write(cind+'}\n\n')
        source_file.close()
        print c_compiler+' '+c_opt_flags+' -c '+source_name
        os.system(c_compiler+' '+c_opt_flags+' -c '+source_name)
        #os.system('ar -r '+lib_name+' '+subroutine_name+'.o')
        os.system('mv '+subroutine_name+'.o '+obj_dir)
        os.system('mv '+subroutine_name+'.c '+src_dir)

