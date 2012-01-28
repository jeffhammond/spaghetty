#!/usr/bin/python

import fileinput
import string
import sys
import os

# BGP
#fortran_compiler = '/bgsys/drivers/ppcfloor/comm/bin/mpixlf77_r'
fortran_compiler = 'bgxlf_r'
fortran_opt_flags = '-O5 -g -qsmp=omp -qhot -qipa -qarch=450d -qtune=450 -qprefetch -qunroll=yes -qmaxmem=-1 -qalias=noaryovrlp:nopteovrlp -qreport=smplist:hotlist -qsource -c'
src_dir = '/gpfs/home/jhammond/spaghetty/python/archive/src/'
lst_dir = '/gpfs/home/jhammond/spaghetty/python/archive/lst/'

lib_name = 'tce_sort_f77_omp.a'

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['4','3','2','1']
indices = ['1','2','3','4']

transpose_list = perm(indices)
#transpose_list = [indices]

loop_list = perm(indices)
#loop_list = [indices]

for transpose_order in transpose_list:
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    source_name = 'trans_'+A+B+C+D+'_omp_'
    print source_name
    source_file = open(source_name+'.F','w')
    for loop_order in loop_list:
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        subroutine_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d+'_omp_'
        source_file.write('        subroutine '+subroutine_name+'(unsorted,sorted,\n')
        source_file.write('     &                           dim1,dim2,dim3,dim4)\n')
        source_file.write('        implicit none\n')
        source_file.write('        integer dim1,dim2,dim3,dim4\n')
        source_file.write('        integer j1,j2,j3,j4\n')
        source_file.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
        source_file.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
        if not (a=='1' and A=='1' and b=='2' and B=='2' and c=='3' and C=='3' and d=='4' and D=='4'):
            source_file.write('!$omp parallel do \n')
            source_file.write('!$omp& private(j1,j2,j3,j4)\n')
            source_file.write('!$omp& shared(sorted,unsorted)\n')
            source_file.write('!$omp& schedule(static)\n')

        if (a=='1' and A=='1' and b=='2' and B=='2' and c=='3' and C=='3' and d=='4' and D=='4'):
            source_file.write('c        do j'+a+' = 1,dim'+a+'\n')
            source_file.write('c         do j'+b+' = 1,dim'+b+'\n')
            source_file.write('c          do j'+c+' = 1,dim'+c+'\n')
            source_file.write('c           do j'+d+' = 1,dim'+d+'\n')
            source_file.write('c              sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
            source_file.write('c     1      unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
            source_file.write('c           enddo\n')
            source_file.write('c          enddo\n')
            source_file.write('c         enddo\n')
            source_file.write('c        enddo\n')
            source_file.write('           call f_memcpy(\n')
            source_file.write('     1          sorted(1),\n')
            source_file.write('     2        unsorted(1),\n')
            source_file.write('     3        dim'+d+'*dim'+c+'*dim'+b+'*dim'+a+')\n')
        elif (b=='2' and B=='2' and c=='3' and C=='3' and d=='4' and D=='4'):
            source_file.write('        do j'+a+' = 1,dim'+a+'\n')
            source_file.write('c         do j'+b+' = 1,dim'+b+'\n')
            source_file.write('c          do j'+c+' = 1,dim'+c+'\n')
            source_file.write('c           do j'+d+' = 1,dim'+d+'\n')
            source_file.write('c              sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
            source_file.write('c     1      unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
            source_file.write('c           enddo\n')
            source_file.write('c          enddo\n')
            source_file.write('c         enddo\n')
            source_file.write('           call f_memcpy(\n')
            source_file.write('     1          sorted(dim'+B+'*(j'+A+'-1)),\n')
            source_file.write('     2        unsorted(dim2*(j1-1)),\n')
            source_file.write('     3        dim'+d+'*dim'+c+'*dim'+b+')\n')
            source_file.write('        enddo\n')
        elif (c=='3' and C=='3' and d=='4' and D=='4'):
            source_file.write('        do j'+a+' = 1,dim'+a+'\n')
            source_file.write('         do j'+b+' = 1,dim'+b+'\n')
            source_file.write('c          do j'+c+' = 1,dim'+c+'\n')
            source_file.write('c           do j'+d+' = 1,dim'+d+'\n')
            source_file.write('c              sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
            source_file.write('c     1      unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
            source_file.write('c           enddo\n')
            source_file.write('c          enddo\n')
            source_file.write('           call f_memcpy(\n')
            source_file.write('     1          sorted(dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1))),\n')
            source_file.write('     2        unsorted(dim3*(j2-1+dim2*(j1-1))),\n')
            source_file.write('     3        dim'+d+'*dim'+c+')\n')
            source_file.write('         enddo\n')
            source_file.write('        enddo\n')
        elif (d=='4' and D=='4'):
            source_file.write('        do j'+a+' = 1,dim'+a+'\n')
            source_file.write('         do j'+b+' = 1,dim'+b+'\n')
            source_file.write('          do j'+c+' = 1,dim'+c+'\n')
            source_file.write('c           do j'+d+' = 1,dim'+d+'\n')
            source_file.write('c              sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
            source_file.write('c     1      unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
            source_file.write('c           enddo\n')
            source_file.write('           call f_memcpy(\n')
            source_file.write('     1          sorted(dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))),\n')
            source_file.write('     2        unsorted(dim4*(j3-1+dim3*(j2-1+dim2*(j1-1)))),\n')
            source_file.write('     3        dim'+d+')\n')
            source_file.write('          enddo\n')
            source_file.write('         enddo\n')
            source_file.write('        enddo\n')
        else:                          
            source_file.write('        do j'+a+' = 1,dim'+a+'\n')
            source_file.write('         do j'+b+' = 1,dim'+b+'\n')
            source_file.write('          do j'+c+' = 1,dim'+c+'\n')
            source_file.write('           do j'+d+' = 1,dim'+d+'\n')
            source_file.write('              sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
            source_file.write('     1      unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
            source_file.write('           enddo\n')
            source_file.write('          enddo\n')
            source_file.write('         enddo\n')
            source_file.write('        enddo\n')

        if not (a=='1' and A=='1' and b=='2' and B=='2' and c=='3' and C=='3' and d=='4' and D=='4'):
            source_file.write('!$omp end parallel do\n')

        source_file.write('        return\n')
        source_file.write('        end\n')

    source_file.close()
    rc = os.system(fortran_compiler+' '+fortran_opt_flags+' -c '+source_name+'.F')
    if not rc==0:
        print 'FAILED: '+fortran_compiler+' '+fortran_opt_flags+' -c '+source_name+'.F'
        exit(rc)

    else:
        os.system('powerpc-bgp-linux-ar -r '+lib_name+' '+source_name+'.o')
        os.system('rm '+source_name+'.o')
        os.system('mv '+source_name+'.F '+src_dir)
        os.system('mv '+source_name+'.lst '+lst_dir)

