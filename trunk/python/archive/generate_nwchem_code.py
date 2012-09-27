#!/usr/bin/python

import fileinput
import string
import sys
import os

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

machine='fusion'
n=1 # column of indices[][n][] to use

# [TRANSPOSE,FUSION-BEST,HOPPER-BEST]
indices = [['1234','1234','1234'],
           ['1243','1243','1234'],
           ['1324','1234','1234'],
           ['1342','1342','1342'],
           ['1423','1234','1234'],
           ['1432','1432','1342'],
           ['2134','1234','1234'],
           ['2143','2143','1234'],
           ['2314','2314','2314'],
           ['2341','2314','2341'],
           ['2413','2134','1234'],
           ['2431','2431','2341'],
           ['3124','1234','1234'],
           ['3142','1342','1234'],
           ['3214','2134','2134'],
           ['3241','2314','2341'],
           ['3412','1342','1324'],
           ['3421','2341','3241'],
           ['4123','1243','1234'],
           ['4132','1432','1234'],
           ['4213','2143','1234'],
           ['4231','2431','2341'],
           ['4312','3142','1324'],
           ['4321','2431','3241']]

source_file = open('tce_sort4_spagetty_'+machine+'.F','w')

source_file.write('       subroutine tce_sort_4(unsorted,sorted,a,b,c,d,i,j,k,l,factor)\n')
source_file.write('       implicit none                                                \n')
source_file.write('       integer version                                              \n')
source_file.write('       integer a,b,c,d                                              \n')
source_file.write('       integer i,j,k,l                                              \n')
source_file.write('       double precision sorted(a*b*c*d)                             \n')
source_file.write('       double precision unsorted(a*b*c*d)                           \n')
source_file.write('       double precision factor                                      \n')
source_file.write('       version = 1000*i+100*j+10*k+l                                \n')

for i in range(24):
    A = indices[i][0][0]
    B = indices[i][0][1]
    C = indices[i][0][2]
    D = indices[i][0][3]
    a = indices[i][n][0]
    b = indices[i][n][1]
    c = indices[i][n][2]
    d = indices[i][n][3]
    subroutine_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d
    if (i==0):
        source_file.write('       if (version.eq.'+A+B+C+D+') then \n')
        source_file.write('         call '+subroutine_name+'(unsorted,sorted,a,b,c,d,factor)   \n')
    else:
        source_file.write('       elseif (version.eq.'+A+B+C+D+') then \n')
        source_file.write('         call '+subroutine_name+'(unsorted,sorted,a,b,c,d,factor)   \n')
source_file.write('       endif                     \n')

for i in range(24):
    A = indices[i][0][0]
    B = indices[i][0][1]
    C = indices[i][0][2]
    D = indices[i][0][3]
    a = indices[i][n][0]
    b = indices[i][n][1]
    c = indices[i][n][2]
    d = indices[i][n][3]
    subroutine_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d
    source_file.write('        subroutine '+subroutine_name+'(unsorted,sorted,\n')
    source_file.write('     &                           dim1,dim2,dim3,dim4,factor)\n')
    source_file.write('        implicit none\n')
    source_file.write('        integer dim1,dim2,dim3,dim4\n')
    source_file.write('        integer old_offset,new_offset\n')
    source_file.write('        integer j1,j2,j3,j4\n')
    source_file.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
    source_file.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
    source_file.write('        double precision factor\n')
    source_file.write('        do j'+a+' = 1,dim'+a+'\n')
    source_file.write('         do j'+b+' = 1,dim'+b+'\n')
    source_file.write('          do j'+c+' = 1,dim'+c+'\n')
    source_file.write('           do j'+d+' = 1,dim'+d+'\n')
    source_file.write('            old_offset = j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1)))\n')
    source_file.write('            new_offset = j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))\n')
    source_file.write('            sorted(new_offset) = unsorted(old_offset) * factor\n')
    source_file.write('           enddo\n')
    source_file.write('          enddo\n')
    source_file.write('         enddo\n')
    source_file.write('        enddo\n')
    source_file.write('        return\n')
    source_file.write('        end\n')

source_file.close()

