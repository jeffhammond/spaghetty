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
#fortran_compiler = 'ifort'
#fortran_opt_flags = '-O3 -mtune=core2 -msse3 -align -c'
#src_dir = '/home/jeff/code/spaghetty/trunk/python/archive/src/'

fortran_compiler = 'ifort'
fortran_link_flags = '-O1 -xT -mtune=core2 -align -pad'
opt_set = [[],[],[],[],[],[],[],[],[]]
opt_set[0] = '-O3 -xT -mtune=core2 -align -pad'# -unroll-aggressive -vec-guard-write -opt-streaming-stores always'
opt_set[1] = '-O1'
opt_set[2] = '-O2'
opt_set[3] = '-O3 -align -pad'
opt_set[4] = '-O3 -unroll-aggressive'
opt_set[5] = '-O3 -parallel'
opt_set[6] = '-O3 -xT -mtune=core2'
opt_set[7] = '-O3 -vec-guard-write'
opt_set[8] = '-O3 -opt-streaming-stores always'
#opt_set_num = 3
#fortran_opt_flags = opt_set[opt_set_num]
#src_dir = '/home/jeff/code/spaghetty/trunk/python/archive/src_optset'+str(opt_set_num)+'/'
#lib_name = 'tce_sort_optset'+str(opt_set_num)+'.a'

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

#indices = ['1','2','3','4']
indices = ['4','3','2','1']

#all_permutations = perm(indices)
#all_permutations = [indices]

transpose_list = [indices]
#transpose_list = perm(indices)
#loop_list = [indices]
loop_list = perm(indices)

for opt_set_num in range(0,1):
    print 'opt_set_num = '+str(opt_set_num)
    fortran_opt_flags = opt_set[opt_set_num]
    src_dir = '/home/jeff/code/spaghetty/trunk/python/archive/src_optset'+str(opt_set_num)+'_unroll/'
    os.system('mkdir '+src_dir)    
    exe_dir = '/home/jeff/code/spaghetty/trunk/python/archive/exe_optset'+str(opt_set_num)+'_unroll/'
    os.system('mkdir '+exe_dir)
    lib_name = 'tce_sort_optset'+str(opt_set_num)+'_unroll.a'
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
            print fortran_compiler+' '+fortran_opt_flags+' -c '+src_dir+source_name
            os.system(fortran_compiler+' '+fortran_opt_flags+' -c '+src_dir+source_name)
            os.system('ar -r '+lib_name+' '+subroutine_name+'.o')
            os.system('rm '+subroutine_name+'.o')
            #os.system('mv '+subroutine_name+'.lst '+lst_dir)
    
