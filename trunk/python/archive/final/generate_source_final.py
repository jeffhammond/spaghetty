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


def generate_permutation_list(Debug):
    indices = ['4','3','2','1']
    if Debug:
        permlist        = [indices]
    else:
        permlist        = perm(indices)
    return permlist


def get_omp_info(OpenMP):
    if OpenMP:
        name = 'omp'
        text = 'with OpenMP'
    else:
        name = 'nomp'
        text = 'without OpenMP'
    return (name,text)


def get_fac_info(Factor):
    if (Factor==1.0):
        name = 'copy'
        text = 'scale by 1.0'
    elif (Factor==-1.0):
        name = 'neg'
        text = 'scale by -1.0'
    else:
        name = 'any'
        text = 'scale by any value'
    return (name,text)


#Debug=True
Debug=False


makefile = open('Makefile','w')
makefile.write('FC      = gfortran \n')
makefile.write('FFLAGS  = -O3 -fopenmp  \n\n')
makefile.write('OBJECTS = \\\n')

for transpose_order in generate_permutation_list(Debug):
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    for loop_order in generate_permutation_list(Debug):
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]

        source_name = 'trans_'+A+B+C+D+'_loop_'+a+b+c+d
        makefile.write(source_name+'.o \\\n')
        source_file = open(source_name+'.f','w')

        for OpenMP in [True,False]:
            (omp_name,omp_text) = get_omp_info(OpenMP)

            for Factor in [1.0,-1.0,37.0]:
                (fac_name,fac_text) = get_fac_info(Factor)

                variant = omp_name+'_'+fac_name
                subroutine_name = source_name+'_'+variant
                print subroutine_name
                description = '! '+omp_text+', '+fac_text+'\n'

                source_file.write(description)
                source_file.write('        subroutine '+subroutine_name+'(unsorted,sorted,\n')
                if Factor not in [1.0,-1.0]:
                    source_file.write('     &                dim1,dim2,dim3,dim4,factor)\n')
                else:
                    source_file.write('     &                dim1,dim2,dim3,dim4)\n')
                source_file.write('        implicit none\n')
                source_file.write('        integer dim1,dim2,dim3,dim4\n')
                source_file.write('        integer j1,j2,j3,j4\n')
                source_file.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
                source_file.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
                if Factor not in [1.0,-1.0]:
                    source_file.write('        double precision factor\n')
                if OpenMP:
                    source_file.write('!$omp parallel do collapse(4)\n')
                    source_file.write('!$omp& private(j1,j2,j3,j4)\n')
                    if Factor not in [1.0,-1.0]:
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
                else:
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
makefile.write('\t$(AR) $(ARFLAGS) $@ $(OBJECTS) \n\n')
makefile.write('%.o: %.f \n')
makefile.write('\t$(FC) $(FFLAGS) -c $< -o $@ \n\n')
makefile.write('clean: \n')
makefile.write('\t$(RM) $(RMFLAGS) $(OBJECTS) \n\n')
makefile.write('realclean: clean \n')
makefile.write('\t$(RM) $(RMFLAGS) libspaghetty.a *.f \n\n')

makefile.close()
