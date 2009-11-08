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

#indices = ['3','4','1','2']
indices = ['4','3','2','1']

#transpose_list = [indices]
#loop_list = [indices]

transpose_list = perm(indices)
loop_list = perm(indices)

for transpose_order in transpose_list:
    dummy = 0
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    script_name = 'transpose_'+A+B+C+D
    script = open(script_name,'w')
    script.write('#!/bin/sh\n')
    for loop_order in loop_list:
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        driver_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d
        script.write('cobalt-mpirun -np 1 -mode smp /gpfs/home/jhammond/spaghetty/python/archive/exe/'+driver_name+'.x\n')

    script.close()
    os.system('chmod +x '+script_name)
    #os.system('cqsub -n 1 -t 60 -m script  '+script_name)
    print 'cqsub -n 1 -t 60 -m script  '+script_name



