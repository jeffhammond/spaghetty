#!/usr/bin/python

import fileinput
import string
import sys
import os

def perm_to_string(perm):
    A = perm[0]
    B = perm[1]
    C = perm[2]
    D = perm[3]
    return A+B+C+D


def get_omp_info(OpenMP):
    if OpenMP:
        name = 'omp'
        text = 'with OpenMP'
    else:
        name = 'ser'
        text = 'without OpenMP'
    return (name,text)


def get_fac_info(Factor):
    if (Factor==1.0):
        name = 'cpy'
        text = 'scale by 1.0'
    elif (Factor==-1.0):
        name = 'neg'
        text = 'scale by -1.0'
    else:
        name = 'any'
        text = 'scale by any value'
    return (name,text)


knight = [['4321','3241'],
          ['4312','3142'],
          ['4231','2341'],
          ['4132','1342'],
          ['4213','2134'],
          ['4123','1234'],
          ['3421','3241'],
          ['3412','3142'],
          ['2431','2341'],
          ['1432','1342'],
          ['2413','2143'],
          ['1423','1243'],
          ['3241','3214'],
          ['3142','3124'],
          ['2341','2314'],
          ['1342','1324'],
          ['2143','2143'],
          ['1243','1234'],
          ['3214','2134'],
          ['3124','1243'],
          ['2314','2341'],
          ['1324','1234'],
          ['2134','2143'],
          ['1234','1243']]

def generate_library_driver(subdir, machine, bestlist, suffix):
    oname = 'tce_sort4_'+machine
    file = open(subdir+'/'+oname+'.F','w')
    file.write('c u = unsorted\n')
    file.write('c s = sorted\n')
    file.write('c a,b,c,d = array dimensions\n')
    file.write('c i,j,k,l = permutation\n')
    file.write('      subroutine tce_sort_4(u,s,a,b,c,d,i,j,k,l,factor)\n')
    file.write('      implicit none\n')
    file.write('      integer version\n')
    file.write('      integer a,b,c,d\n')
    file.write('      integer i,j,k,l\n')
    file.write('      double precision s(a*b*c*d)\n')
    file.write('      double precision u(a*b*c*d)\n')
    file.write('      double precision factor\n')
    file.write('      version = 1000*i+100*j+10*k+l\n')
    count = 0
    for (transpose,best) in bestlist:
        if (count==0):
            logic = 'if'
        else:
            logic = 'else if'
   
        file.write('      '+logic+' (version.eq.'+transpose+') then \n')
        file.write('        call trans_'+transpose+'_loop_'+best+'_'+suffix+'(u,s,a,b,c,d,factor)\n')
        count = count + 1
    file.write('      else\n')
    file.write('        print*,\'something is wrong...\'\n')
    file.write('      endif\n')
    file.write('      return\n')
    file.write('      end\n')
    file.close()

generate_library_driver('Intel','knight',knight,'omp_any_f')



