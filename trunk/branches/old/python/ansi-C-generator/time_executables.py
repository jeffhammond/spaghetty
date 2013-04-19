import fileinput
import string
import sys
import os

#project_name = '-A 2008LeapToPetaScaleWS'
project_name = ''

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['1','2','3','4']
#indices = ['3','4','1','2']

sort_list = [indices]
#sort_list = [['1','2','3','4'],['1','2','4','3'],['1','3','2','4'],['1','3','4','2'],['1','4','2','3'],['1','4','3','2']]
#sort_list = perm(indices)

for transpose_order in sort_list:
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
        driver_name = 'transpose_'+A+B+C+D
        os.system('qsub '+project_name+' -n 1 -t 5 --mode smp exe/'+driver_name+'.x')

