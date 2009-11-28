#!/usr/bin/python

import fileinput
import string
import sys
import os

OpenMP = False
#OpenMP = True

fortran_compiler = 'ifort'
if (OpenMP):
        fortran_opt_flags = '-g -i8 -O3 -openmp -xSSE2,SSE3,SSSE3,SSE4.1,SSE4.2 -opt-prefetch -funroll-loops -c'
else:
        fortran_opt_flags = '-g -i8 -O3 -xSSE2,SSE3,SSSE3,SSE4.1,SSE4.2 -opt-prefetch -funroll-loops -c'

src_dir = '/fusion/home/jhammond/spaghetty/python/archive/src/'

if (OpenMP):
        lib_name = 'tce_sort_intel_omp.a'
else:
        lib_name = 'tce_sort_intel.a'

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['4','3','2','1']

#transpose_list = [['1','3','4','2']]
#loop_list = [['2','4','3','1'],['1','4','3','2']]

transpose_list = perm(indices)
loop_list = perm(indices)

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
        if (OpenMP):
                subroutine_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d+'_intel_omp'
        else:
                subroutine_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d+'_intel'

        source_name = subroutine_name+'.F'
        print source_name
        source_file = open(source_name,'w')
        source_file.write('        subroutine '+subroutine_name+'(unsorted,sorted,\n')
        source_file.write('     &                dim1,dim2,dim3,dim4,factor)\n')
        source_file.write('        implicit none\n')
        source_file.write('        integer dim1,dim2,dim3,dim4\n')
        source_file.write('        integer j1,j2,j3,j4\n')
        source_file.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
        source_file.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
        source_file.write('        double precision factor\n')
        if (OpenMP):
                source_file.write('!$omp parallel do\n')
                source_file.write('!$omp& private(j1,j2,j3,j4)\n')
                source_file.write('!$omp& shared(sorted,unsorted)\n')
                source_file.write('!$omp& schedule(static)\n')

        source_file.write('        do j'+a+' = 1,dim'+a+'\n')
        source_file.write('         do j'+b+' = 1,dim'+b+'\n')
        source_file.write('          do j'+c+' = 1,dim'+c+'\n')
        source_file.write('           do j'+d+' = 1,dim'+d+'\n')
        source_file.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
        source_file.write('     &    unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1)))) * factor\n')
        source_file.write('           enddo\n')
        source_file.write('          enddo\n')
        source_file.write('         enddo\n')
        source_file.write('        enddo\n')
        if (OpenMP):
                source_file.write('!$omp end parallel do\n')

        source_file.write('        return\n')
        source_file.write('        end\n')
        source_file.close()
        os.system(fortran_compiler+' '+fortran_opt_flags+' -c '+source_name)
        os.system('ar -r '+lib_name+' '+subroutine_name+'.o')
        os.system('rm '+subroutine_name+'.o')
        os.system('mv '+subroutine_name+'.F '+src_dir)

