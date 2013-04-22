import fileinput
import string
import sys
import os

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['1','2','3','4']

transpose_list = perm(indices)

exe_dir = '/home/jeff/code/spaghetty/trunk/binary/fortran77/'
for transpose_order in transpose_list:
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    driver_name = 'transpose_'+A+B+C+D
    print driver_name
    os.system(exe_dir+driver_name+'.x > '+exe_dir+driver_name+'.log')
    
    
    
    
