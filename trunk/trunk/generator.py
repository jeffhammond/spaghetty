#!/usr/bin/python

import fileinput
import string
import sys
import os

#Debug=True
Debug=False


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


def generate_subroutine(ofile, name, description, OpenMP, Factor, transpose_order, loop_order):
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    a = loop_order[0]
    b = loop_order[1]
    c = loop_order[2]
    d = loop_order[3]
    ofile.write(description)
    ofile.write('        subroutine '+name+'(unsorted,sorted,\n')
    if Factor not in [1.0,-1.0]:
        ofile.write('     &                dim1,dim2,dim3,dim4,factor)\n')
    else:
        ofile.write('     &                dim1,dim2,dim3,dim4)\n')
    ofile.write('        implicit none\n')
    ofile.write('        integer dim1,dim2,dim3,dim4\n')
    ofile.write('        integer j1,j2,j3,j4\n')
    ofile.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
    if Factor not in [1.0,-1.0]:
        ofile.write('        double precision factor\n')
    if OpenMP:
        ofile.write('!$omp parallel do collapse(4)\n')
        ofile.write('!$omp& private(j1,j2,j3,j4)\n')
        if Factor not in [1.0,-1.0]:
            ofile.write('!$omp& firstprivate(dim1,dim2,dim3,dim4,factor)\n')
        else:
            ofile.write('!$omp& firstprivate(dim1,dim2,dim3,dim4)\n')
        ofile.write('!$omp& shared(sorted,unsorted)\n')
        ofile.write('!$omp& schedule(static)\n')
    ofile.write('        do j'+a+' = 1,dim'+a+'\n')
    ofile.write('         do j'+b+' = 1,dim'+b+'\n')
    ofile.write('          do j'+c+' = 1,dim'+c+'\n')
    ofile.write('           do j'+d+' = 1,dim'+d+'\n')
    if (Factor==1.0):
        ofile.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
        ofile.write('     &    unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
    elif (Factor==-1.0):
        ofile.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
        ofile.write('     &    -unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
    else:
        ofile.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
        ofile.write('     &    factor*unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')

    ofile.write('           enddo\n')
    ofile.write('          enddo\n')
    ofile.write('         enddo\n')
    ofile.write('        enddo\n')
    if OpenMP:
        ofile.write('!$omp end parallel do\n')
    ofile.write('        return\n')
    ofile.write('        end\n\n')
    return


def generate_tester(ofile, transpose_order):
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    test_name = 'trans_'+perm_to_string(transpose_order)
    ofile.write('        subroutine test_'+test_name+'(dt,\n')
    ofile.write('     &                reference, unsorted, sorted,\n')
    ofile.write('     &                dim1, dim2, dim3, dim4)\n')
    ofile.write('        implicit none\n')
    ofile.write('        integer dim1, dim2, dim3, dim4\n')
    ofile.write('        integer errors, omp, fac, loop\n')
    ofile.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('        double precision reference(dim1*dim2*dim3*dim4)\n')
    ofile.write('        double precision factor\n')
    ofile.write('        double precision t0, t1, dt0, dt(24,3,2) \n')
    ofile.write('        double precision wtime\n')
    ofile.write('        external wtime\n')
    ofile.write('        loop = 0 \n')
    ofile.write('        factor = 1.0\n')
    ofile.write('        call init_4d_array(dim1,dim2,dim3,dim4,unsorted)\n')
    ofile.write('        call zero_1d_array(dim1*dim2*dim3*dim4,reference)\n')
    # flush cache routine belongs here if we want to do that
    ofile.write('        t0  = wtime() \n')
    ofile.write('        call old_sort4(unsorted,reference,\n')
    ofile.write('     &                dim1,dim2,dim3,dim4,factor)\n')
    ofile.write('        t1  = wtime() \n')
    ofile.write('        dt0 = t1-t0 \n')
    for loop_order in generate_permutation_list(Debug):
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)
        ofile.write('        loop = loop+1 \n')
        for OpenMP in [True,False]:
            (omp_name,omp_text) = get_omp_info(OpenMP)
            if OpenMP:
                ofile.write('        omp = 1 \n')
            else:
                ofile.write('        omp = 2 \n')
            for Factor in [1.0,-1.0,37.0]:
                (fac_name,fac_text) = get_fac_info(Factor)
                variant = omp_name+'_'+fac_name
                subroutine_name = source_name+'_'+variant
                ofile.write('        call zero_1d_array(dim1*dim2*dim3*dim4,sorted)\n')
                # flush cache routine belongs here if we want to do that
                ofile.write('        t0 = wtime() \n')
                if Factor==1.0:
                    ofile.write('        fac = 1 \n')
                    ofile.write('        call '+subroutine_name+'(unsorted,sorted,\n')
                    ofile.write('     &                dim1,dim2,dim3,dim4)\n')
                elif Factor==-1.0:
                    ofile.write('        fac = 2 \n')
                    ofile.write('        call '+subroutine_name+'(unsorted,sorted,\n')
                    ofile.write('     &                dim1,dim2,dim3,dim4)\n')
                else:
                    ofile.write('        fac = 3 \n')
                    ofile.write('        factor = '+str(Factor)+'\n')
                    ofile.write('        call '+subroutine_name+'(unsorted,sorted,\n')
                    ofile.write('     &                dim1,dim2,dim3,dim4,factor)\n')
                ofile.write('        t1 = wtime() \n')
                ofile.write('        call compare_1d_array(dim1*dim2*dim3*dim4,\n')
                ofile.write('     &                        sorted,reference,errors) \n')
                ofile.write('        if (errors.eq.0) then\n')
                ofile.write('          dt(loop,fac,omp) = t1-t0\n')
                ofile.write('        else\n')
                ofile.write('          dt(loop,fac,omp) = 10000000.0\n')
                ofile.write('        endif\n')
    ofile.write('        return\n')
    ofile.write('        end\n')
    return


def generate_all_subroutines(Debug):
    for transpose_order in generate_permutation_list(Debug):
        source_name = 'test_trans_'+perm_to_string(transpose_order)
        source_file = open('src/'+source_name+'.f','w')
        generate_tester(source_file, transpose_order)
        source_file.close()
        for loop_order in generate_permutation_list(Debug):

            source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)
            source_file = open('src/'+source_name+'.f','w')

            for OpenMP in [True,False]:
                (omp_name,omp_text) = get_omp_info(OpenMP)

                for Factor in [1.0,-1.0,37.0]:
                    (fac_name,fac_text) = get_fac_info(Factor)

                    variant = omp_name+'_'+fac_name
                    subroutine_name = source_name+'_'+variant
                    print subroutine_name
                    description = '! '+omp_text+', '+fac_text+'\n'

                    generate_subroutine(source_file, subroutine_name, description, OpenMP, Factor, transpose_order, loop_order)

            source_file.close()

def generate_makefile(Debug):
    makefile = open('src/Makefile','w')
    makefile.write('CC      = gcc \n')
    makefile.write('FC      = gfortran \n')
    if (Debug):
        makefile.write('CFLAGS  = -g -O0 -Wall -fopenmp -std=c99  \n')
        makefile.write('FFLAGS  = -g -O0 -Wall -fopenmp  \n\n')
    else:
        makefile.write('CFLAGS  = -O2 -fopenmp -std=c99  \n')
        makefile.write('FFLAGS  = -O2 -fopenmp  \n\n')

    makefile.write('SOURCES = \\\n')
    for transpose_order in generate_permutation_list(Debug):
        for loop_order in generate_permutation_list(Debug):
            source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)
            makefile.write(source_name+'.f \\\n')

    for transpose_order in generate_permutation_list(Debug):
        source_name = 'test_trans_'+perm_to_string(transpose_order)
        makefile.write(source_name+'.f \\\n')

    makefile.write('\n\n')
    makefile.write('OBJECTS = \\\n')
    for transpose_order in generate_permutation_list(Debug):
        for loop_order in generate_permutation_list(Debug):
            source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)
            makefile.write(source_name+'.o \\\n')

    for transpose_order in generate_permutation_list(Debug):
        source_name = 'test_trans_'+perm_to_string(transpose_order)
        makefile.write(source_name+'.o \\\n')

    makefile.write('\n\n')
    makefile.write('TESTOBJ = tester_cutil.o tester_futil.o old_sort.o \n\n')
    makefile.write('all: libspaghetty.a libtestutil.a \n\n')
    makefile.write('libspaghetty.a: $(OBJECTS) \n')
    makefile.write('\t$(AR) $(ARFLAGS) $@ $(OBJECTS) \n\n')
    makefile.write('libtestutil.a: $(TESTOBJ) \n')
    makefile.write('\t$(AR) $(ARFLAGS) $@ $(TESTOBJ) \n\n')
    makefile.write('%.o: %.f \n')
    makefile.write('\t$(FC) $(FFLAGS) -c $< -o $@ \n\n')
    makefile.write('clean: \n')
    makefile.write('\t$(RM) $(RMFLAGS) $(OBJECTS) $(TESTOBJ) \n\n')
    makefile.write('realclean: clean \n')
    makefile.write('\t$(RM) $(RMFLAGS) libspaghetty.a libtestutil.a \n\n')
    makefile.write('srcclean: realclean \n')
    makefile.write('\t$(RM) $(RMFLAGS) $(SOURCES) \n\n')
    makefile.close()
    return


generate_all_subroutines(Debug)
generate_makefile(Debug)
