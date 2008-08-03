import fileinput
import string
import sys
import os

# BGP
#fortran_compiler = '/bgsys/drivers/ppcfloor/comm/bin/mpixlf77_r'
#fortran_opt_flags = '-O5 -qhot -qprefetch -qcache=auto -qalign=4k -qunroll=yes -qmaxmem=-1 -qalias=noaryovrlp:nopteovrlp -qnoextname -qnosmp -qreport=hotlist -c'
#src_dir = '/gpfs/home/jhammond/spaghetty/python/archive/src/'
#lst_dir = '/gpfs/home/jhammond/spaghetty/python/archive/lst/'

fortran_compiler = 'ifort'
fortran_opt_flags = '-O3 -mtune=core2 -msse3 -align -c'
src_dir = '/home/jeff/code/spaghetty/trunk/python/archive/src/'

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

##indices = ['1','2','3','4','5','6']
indices = ['3','2','6','1','5','4']
#indices = ['3','2','6','5','1','4']
#indices = ['3','2','6','5','4','1']
#indices = ['3','6','2','1','5','4']
#indices = ['3','6','2','5','1','4']
#indices = ['3','6','2','5','4','1']
#indices = ['3','6','5','2','4','1']
#indices = ['3','6','5','2','1','4']
#indices = ['3','6','5','4','2','1']
#indices = ['4','3','6','2','1','5']
#indices = ['4','3','6','2','5','1']
#indices = ['4','3','6','5','2','1']
#indices = ['4','6','3','2','1','5']
#indices = ['4','6','3','2','5','1']
#indices = ['4','6','3','5','2','1']
#indices = ['6','4','3','2','1','5']
#indices = ['6','4','3','2','5','1']
#indices = ['6','4','3','5','2','1']
#indices = ['6','5','3','2','1','4']
#indices = ['6','5','3','2','4','1']
#indices = ['6','5','3','4','2','1']
#indices = ['6','3','5','2','1','4']
#indices = ['6','3','5','2','4','1']
#indices = ['6','3','5','4','2','1']
#indices = ['6','3','2','1','5','4']
#indices = ['6','3','2','5','1','4']
#indices = ['6','3','2','5','4','1']

#all_permutations = perm(indices)
#all_permutations = [indices]

#transpose_list = perm(indices)
transpose_list = [indices]
loop_list = perm(indices)

for transpose_order in transpose_list:
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    E = transpose_order[4]
    F = transpose_order[5]    
    for loop_order in loop_list:
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        e = loop_order[4]
        f = loop_order[5] 
        subroutine_name = 'transaccu_'+A+B+C+D+E+F+'_loop_'+a+b+c+d+e+f
        source_name = subroutine_name+'.F'
        #print source_name
        source_file = open(source_name,'w')
        source_file.write('        subroutine '+subroutine_name+'(unsorted,sorted,\n')
        source_file.write('     &                           dim1,dim2,dim3,dim4,dim5,dim6,factor)\n')
        source_file.write('        implicit none\n')
        source_file.write('        integer dim1,dim2,dim3,dim4,dim5,dim6\n')
        source_file.write('        integer old_offset,new_offset\n')
        source_file.write('        integer j1,j2,j3,j4,j5,j6\n')
        source_file.write('        double precision sorted(dim1*dim2*dim3*dim4*dim5*dim6)\n')
        source_file.write('        double precision unsorted(dim1*dim2*dim3*dim4*dim5*dim6)\n')
        source_file.write('        double precision factor\n')
        #source_file.write('cdir$ ivdep\n') 
        source_file.write('        do j'+a+' = 1,dim'+a+'\n')
        source_file.write('         do j'+b+' = 1,dim'+b+'\n')
        source_file.write('          do j'+c+' = 1,dim'+c+'\n')
        source_file.write('           do j'+d+' = 1,dim'+d+'\n')
        source_file.write('            do j'+e+' = 1,dim'+e+'\n')
        source_file.write('             do j'+f+' = 1,dim'+f+'\n')
        source_file.write('              old_offset = j6+dim6*(j5-1+dim5*(j4-1+dim4*\n')
        source_file.write('     &                    (j3-1+dim3*(j2-1+dim2*(j1-1)))))\n')
        source_file.write('              new_offset = j'+F+'+dim'+F+'*(j'+E+'-1+dim'+E+'*(j'+D+'-1+dim'+D+'*\n')
        source_file.write('     &                    (j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))))\n')
        source_file.write('              sorted(new_offset) = sorted(new_offset)+unsorted(old_offset)*factor\n')
        source_file.write('             enddo\n')
        source_file.write('            enddo\n')
        source_file.write('           enddo\n')                
        source_file.write('          enddo\n')
        source_file.write('         enddo\n')
        source_file.write('        enddo\n')
        source_file.write('        return\n')
        source_file.write('        end\n')
        source_file.close()
        os.system(fortran_compiler+' '+fortran_opt_flags+' '+source_name)
        os.system('ar -r tce_sort_jeff.a '+subroutine_name+'.o')
        os.system('rm '+subroutine_name+'.o')
        os.system('mv '+subroutine_name+'.F '+src_dir)
        #os.system('mv '+subroutine_name+'.lst '+lst_dir)

