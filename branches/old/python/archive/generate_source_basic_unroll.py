import fileinput
import string
import sys
import os

# BGP
#fortran_compiler = '/bgsys/drivers/ppcfloor/comm/bin/mpixlf77_r'
#fortran_opt_flags = '-O5 -qhot -qprefetch -qcache=auto -qalign=4k -qunroll=yes -qmaxmem=-1 -qalias=noaryovrlp:nopteovrlp -qnoextname -qnosmp -qreport=hotlist -c'
#src_dir = '/gpfs/home/jhammond/spaghetty/python/archive/src/'
#lst_dir = '/gpfs/home/jhammond/spaghetty/python/archive/lst/'

# Goldstone old
fortran_compiler = 'ifort'
fortran_opt_flags = '-O3 -mtune=core2 -march=core2 -align'# -pad -unroll-aggressive'
src_dir = '/home/jeff/code/spaghetty/trunk/source/fortran77/unroll_34/'

lib_name = 'tce_sort_f77_unroll34.a'

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['4','3','2','1']

all_permutations = perm(indices)

#transpose_list = [indices]
transpose_list = all_permutations
#loop_list = [indices]
loop_list = all_permutations
#loop_list = [['3','2','4','1'],['3','2','1','4'],['2','3','4','1'],['2','3','1','4'],['3','4','2','1'],['3','4','2','1'],['2','3','4','1']]

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
        subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d
        source_name = subroutine_name+'.F'
        #print source_name
        source_file = open(source_name,'w')
        source_file.write('        subroutine '+subroutine_name+'(unsorted,sorted,\n')
        source_file.write('     &                           dim1,dim2,dim3,dim4,factor)\n')
        source_file.write('        implicit none\n')
        source_file.write('        integer dim1,dim2,dim3,dim4\n')
        source_file.write('        integer old_offset,new_offset\n')
        source_file.write('        integer j1,j2,j3,j4\n')
        source_file.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
        source_file.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
        source_file.write('        double precision factor\n')
        source_file.write('!DEC$ prefetch sorted\n')
        source_file.write('!DEC$ prefetch unsorted\n')
        source_file.write('!DEC$ ivdep\n')
        source_file.write('!DEC$ loop count min(24), max(40), avg(32)\n')
        source_file.write('!DEC$ unroll(1)\n') 
        source_file.write('        do j'+a+' = 1,dim'+a+'\n')
        source_file.write('!DEC$ loop count min(24), max(40), avg(32)\n')
        source_file.write('!DEC$ unroll(1)\n') 
        source_file.write('         do j'+b+' = 1,dim'+b+'\n')
        source_file.write('!DEC$ loop count min(24), max(40), avg(32)\n')
        source_file.write('!DEC$ unroll(4)\n') 
        source_file.write('          do j'+c+' = 1,dim'+c+'\n')
        source_file.write('!DEC$ loop count min(24), max(40), avg(32)\n')
        source_file.write('!DEC$ unroll(4)\n') 
        source_file.write('!DEC$ vector always\n') 
        source_file.write('           do j'+d+' = 1,dim'+d+'\n')
        if ((c is 3) and (d is 4)) or ((c is 4) and (d is 3)):
            if (D is 4):
            source_file.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = factor*\n')
            source_file.write('     &    unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
        else:
            source_file.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = factor*\n')
            source_file.write('     &    unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')

        source_file.write('           enddo\n')
        source_file.write('          enddo\n')
        source_file.write('         enddo\n')
        source_file.write('        enddo\n')
        source_file.write('        return\n')
        source_file.write('        end\n')
        source_file.close()
        print fortran_compiler+' '+fortran_opt_flags+' -c '+source_name
        os.system(fortran_compiler+' '+fortran_opt_flags+' -c '+source_name)
        os.system('ar -r '+lib_name+' '+subroutine_name+'.o')
        os.system('rm '+subroutine_name+'.o')
        os.system('mv '+subroutine_name+'.F '+src_dir)
        #os.system('mv '+subroutine_name+'.lst '+lst_dir)

