import fileinput
import string
import sys
import os

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

#indices = ['1','2','3','4']
indices = ['3','4','1','2']

all_permutations = [indices]
for transpose_order in all_permutations:
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
	all_permutations = perm(indices)
        for loop_order in all_permutations:
                a = loop_order[0]
                b = loop_order[1]
                c = loop_order[2]
                d = loop_order[3]
                subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d
		#print subroutine_name
		os.system('./exe/'+subroutine_name+'.x')

