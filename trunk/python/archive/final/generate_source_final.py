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

indices = ['4','3','2','1']

Debug=True
#Debug=False

if Debug:
    all_permutations = [indices]
    transpose_list   = [indices]
    loop_list        = [indices]
else:
    all_permutations = perm(indices)
    transpose_list   = perm(indices)
    loop_list        = perm(indices)

makefile = open('Makefile','w')
makefile.write('FC      = gfortran \n')
makefile.write('FFLAGS  = -O3 -fopenmp  \n\n')
makefile.write('OBJECTS = \\\n')

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

        source_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d
        makefile.write(source_name+'.o \\\n')
        source_file = open(source_name+'.f','w')

        for OpenMP in [True,False]:
            if OpenMP:
                omp_name = 'omp'
                omp_text = 'with OpenMP'
            else:
                omp_name = 'nomp'
                omp_text = 'without OpenMP'

            for Factor in [1.0,-1.0,37.0]:
                if (Factor==1.0):
                    fac_name = 'copy'
                    fac_text = 'scale by 1.0'
                elif (Factor==-1.0):
                    fac_name = 'neg'
                    fac_text = 'scale by -1.0'
                else:
                    fac_name = 'any'
                    fac_text = 'scale by any value'

                variant = omp_name+'_'+fac_name
                subroutine_name = source_name+'_'+variant
                print subroutine_name

                source_file.write('! '+omp_text+', '+fac_text+'\n')
                source_file.write('        subroutine '+subroutine_name+'(unsorted,sorted,\n')
                if Factor == 37.0:
                    source_file.write('     &                dim1,dim2,dim3,dim4,factor)\n')
                else:
                    source_file.write('     &                dim1,dim2,dim3,dim4)\n')
                source_file.write('        implicit none\n')
                source_file.write('        integer dim1,dim2,dim3,dim4\n')
                source_file.write('        integer j1,j2,j3,j4\n')
                source_file.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
                source_file.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
                if Factor == 37.0:
                    source_file.write('        double precision factor\n')
                if OpenMP:
                    source_file.write('!$omp parallel do collapse(4)\n')
                    source_file.write('!$omp& private(j1,j2,j3,j4)\n')
                    if Factor == 37.0:
                        source_file.write('!$omp& firstprivate(dim1,dim2,dim3,dim4,factor)\n')
                    else:
                        source_file.write('!$omp& firstprivate(dim1,dim2,dim3,dim4)\n')
                    source_file.write('!$omp& shared(sorted,unsorted)\n')
                    source_file.write('!$omp& schedule(static)\n')
                source_file.write('        do j'+a+' = 1,dim'+a+'\n')
                source_file.write('         do j'+b+' = 1,dim'+b+'\n')
                source_file.write('          do j'+c+' = 1,dim'+c+'\n')
                source_file.write('           do j'+d+' = 1,dim'+d+'\n')
                if (Factor==1.0):
                    source_file.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
                    source_file.write('     &    unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
                elif (Factor==-1.0):
                    source_file.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
                    source_file.write('     &    -unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
                elif Factor == 37.0:
                    source_file.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
                    source_file.write('     &    factor*unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')

                source_file.write('           enddo\n')
                source_file.write('          enddo\n')
                source_file.write('         enddo\n')
                source_file.write('        enddo\n')
                if OpenMP:
                    source_file.write('!$omp end parallel do\n')
                source_file.write('        return\n')
                source_file.write('        end\n\n')

        source_file.close()

makefile.write('\n\n')
makefile.write('all: libspaghetty.a \n\n')
makefile.write('libspaghetty.a: $(OBJECTS) \n')
makefile.write('\t$(AR) $(ARFLAGS) $@ $< \n\n')
makefile.write('%.o: %.f \n')
makefile.write('\t$(FC) $(FFLAGS) -c $< -o $@ \n\n')
makefile.write('clean: \n')
makefile.write('\t$(RM) $(RMFLAGS) $(OBJECTS) \n\n')
makefile.write('realclean: clean \n')
makefile.write('\t$(RM) $(RMFLAGS) libspaghetty.a \n\n')

makefile.close()
