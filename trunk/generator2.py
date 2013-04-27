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


def generate_cfunction(ofile, name, description, OpenMP, transpose_order, loop_order):
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    a = loop_order[0]
    b = loop_order[1]
    c = loop_order[2]
    d = loop_order[3]
    ofile.write(description)
    ofile.write('void '+name+'(const double * restrict unsorted, double * restrict sorted, const int * const dim1, const int * const dim2, const int * const dim3, const int * const dim4, const double * const factor, const double * const acc_factor)\n')
    ofile.write('{\n')
    ofile.write('  const int d1 = *dim1;\n')
    ofile.write('  const int d2 = *dim2;\n')
    ofile.write('  const int d3 = *dim3;\n')
    ofile.write('  const int d4 = *dim4;\n')
    ofile.write('  const int f  = *factor;\n')
    ofile.write('  const int g  = *acc_factor;\n')
    ofile.write('  if (f==1.0 && g==0.0) {\n')
    if OpenMP:
        ofile.write('#pragma omp parallel for collapse(2) firstprivate(d1,d2,d3,d4) shared(sorted,unsorted) schedule(static)\n')
    ofile.write('    for (int j'+a+' = 0; j'+a+'<d'+a+'; j'+a+'++) {\n')
    ofile.write('     for (int j'+b+' = 0; j'+b+'<d'+b+'; j'+b+'++) \n')
    ofile.write('      for (int j'+c+' = 0; j'+c+'<d'+c+'; j'+c+'++) \n')
    ofile.write('       for (int j'+d+' = 0; j'+d+'<d'+d+'; j'+d+'++) \n')
    ofile.write('        sorted[j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))] = unsorted[j4+d4*(j3+d3*(j2+d2*(j1)))];\n')
    ofile.write('    }\n\n')
    ofile.write('  } else if (f!=1.0 && g==0.0) { \n\n')
    if OpenMP:
        ofile.write('#pragma omp parallel for collapse(2) firstprivate(d1,d2,d3,d4,f) shared(sorted,unsorted) schedule(static)\n')
    ofile.write('    for (int j'+a+' = 0; j'+a+'<d'+a+'; j'+a+'++) {\n')
    ofile.write('     for (int j'+b+' = 0; j'+b+'<d'+b+'; j'+b+'++) \n')
    ofile.write('      for (int j'+c+' = 0; j'+c+'<d'+c+'; j'+c+'++) \n')
    ofile.write('       for (int j'+d+' = 0; j'+d+'<d'+d+'; j'+d+'++) \n')
    ofile.write('        sorted[j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))] = f*unsorted[j4+d4*(j3+d3*(j2+d2*(j1)))];\n')
    ofile.write('    }\n\n')
    ofile.write('  } else if (f==1.0 && g==1.0) { \n\n')
    if OpenMP:
        ofile.write('#pragma omp parallel for collapse(2) firstprivate(d1,d2,d3,d4,f) shared(sorted,unsorted) schedule(static)\n')
    ofile.write('    for (int j'+a+' = 0; j'+a+'<d'+a+'; j'+a+'++) {\n')
    ofile.write('     for (int j'+b+' = 0; j'+b+'<d'+b+'; j'+b+'++) \n')
    ofile.write('      for (int j'+c+' = 0; j'+c+'<d'+c+'; j'+c+'++) \n')
    ofile.write('       for (int j'+d+' = 0; j'+d+'<d'+d+'; j'+d+'++) \n')
    ofile.write('        sorted[j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))] += unsorted[j4+d4*(j3+d3*(j2+d2*(j1)))];\n')
    ofile.write('    }\n\n')
    ofile.write('  } else if (f!=1.0 && g==1.0) { \n\n')
    if OpenMP:
        ofile.write('#pragma omp parallel for collapse(2) firstprivate(d1,d2,d3,d4,f) shared(sorted,unsorted) schedule(static)\n')
    ofile.write('    for (int j'+a+' = 0; j'+a+'<d'+a+'; j'+a+'++) {\n')
    ofile.write('     for (int j'+b+' = 0; j'+b+'<d'+b+'; j'+b+'++) \n')
    ofile.write('      for (int j'+c+' = 0; j'+c+'<d'+c+'; j'+c+'++) \n')
    ofile.write('       for (int j'+d+' = 0; j'+d+'<d'+d+'; j'+d+'++) \n')
    ofile.write('        sorted[j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))] += f*unsorted[j4+d4*(j3+d3*(j2+d2*(j1)))];\n')
    ofile.write('    }\n\n')
    ofile.write('  } else { \n\n')
    if OpenMP:
        ofile.write('#pragma omp parallel for collapse(2) firstprivate(d1,d2,d3,d4,f,g) shared(sorted,unsorted) schedule(static)\n')
    ofile.write('    for (int j'+a+' = 0; j'+a+'<d'+a+'; j'+a+'++) {\n')
    ofile.write('     for (int j'+b+' = 0; j'+b+'<d'+b+'; j'+b+'++) \n')
    ofile.write('      for (int j'+c+' = 0; j'+c+'<d'+c+'; j'+c+'++) \n')
    ofile.write('       for (int j'+d+' = 0; j'+d+'<d'+d+'; j'+d+'++) \n')
    ofile.write('        sorted[j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))] = g*sorted[j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))] + f*unsorted[j4+d4*(j3+d3*(j2+d2*(j1)))];\n')
    ofile.write('    }\n\n')
    ofile.write('  }\n\n')
    ofile.write('  return;\n')
    ofile.write('}\n\n')
    return


def generate_subroutine(ofile, name, description, OpenMP, transpose_order, loop_order):
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    a = loop_order[0]
    b = loop_order[1]
    c = loop_order[2]
    d = loop_order[3]
    ofile.write(description)
    ofile.write('      subroutine '+name+'(unsorted,sorted,\n')
    ofile.write('     &              dim1,dim2,dim3,dim4,factor,acc_factor)\n')
    ofile.write('      implicit none\n')
    ofile.write('      integer dim1,dim2,dim3,dim4\n')
    ofile.write('      integer j1,j2,j3,j4\n')
    ofile.write('      double precision sorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('      double precision unsorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('      double precision factor\n')
    ofile.write('      double precision acc_factor\n')
    ofile.write('      if ((factor .eq. 1.0).and.(acc_factor .eq. 0.0)) then\n')
    if OpenMP:
        ofile.write('!$omp parallel do collapse(2)\n')
        ofile.write('!$omp& private(j1,j2,j3,j4)\n')
        ofile.write('!$omp& firstprivate(dim1,dim2,dim3,dim4)\n')
        ofile.write('!$omp& shared(sorted,unsorted)\n')
        ofile.write('!$omp& schedule(static)\n')
    ofile.write('        do j'+a+' = 1,dim'+a+'\n')
    ofile.write('         do j'+b+' = 1,dim'+b+'\n')
    ofile.write('          do j'+c+' = 1,dim'+c+'\n')
    ofile.write('           do j'+d+' = 1,dim'+d+'\n')
    ofile.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
    ofile.write('     &    unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
    ofile.write('           enddo\n')
    ofile.write('          enddo\n')
    ofile.write('         enddo\n')
    ofile.write('        enddo\n')
    if OpenMP:
        ofile.write('!$omp end parallel do\n')
    ofile.write('      else if ((factor .ne. 1.0).and.(acc_factor .eq. 0.0)) then\n')
    if OpenMP:
        ofile.write('!$omp parallel do collapse(2)\n')
        ofile.write('!$omp& private(j1,j2,j3,j4)\n')
        ofile.write('!$omp& firstprivate(dim1,dim2,dim3,dim4,factor)\n')
        ofile.write('!$omp& shared(sorted,unsorted)\n')
        ofile.write('!$omp& schedule(static)\n')
    ofile.write('        do j'+a+' = 1,dim'+a+'\n')
    ofile.write('         do j'+b+' = 1,dim'+b+'\n')
    ofile.write('          do j'+c+' = 1,dim'+c+'\n')
    ofile.write('           do j'+d+' = 1,dim'+d+'\n')
    ofile.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
    ofile.write('     &    factor*unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
    ofile.write('           enddo\n')
    ofile.write('          enddo\n')
    ofile.write('         enddo\n')
    ofile.write('        enddo\n')
    if OpenMP:
        ofile.write('!$omp end parallel do\n')
    ofile.write('      else if ((factor .eq. 1.0).and.(acc_factor .eq. 1.0)) then\n')
    if OpenMP:
        ofile.write('!$omp parallel do collapse(2)\n')
        ofile.write('!$omp& private(j1,j2,j3,j4)\n')
        ofile.write('!$omp& firstprivate(dim1,dim2,dim3,dim4)\n')
        ofile.write('!$omp& shared(sorted,unsorted)\n')
        ofile.write('!$omp& schedule(static)\n')
    ofile.write('        do j'+a+' = 1,dim'+a+'\n')
    ofile.write('         do j'+b+' = 1,dim'+b+'\n')
    ofile.write('          do j'+c+' = 1,dim'+c+'\n')
    ofile.write('           do j'+d+' = 1,dim'+d+'\n')
    ofile.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
    ofile.write('     &    sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) + \n')
    ofile.write('     &    unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
    ofile.write('           enddo\n')
    ofile.write('          enddo\n')
    ofile.write('         enddo\n')
    ofile.write('        enddo\n')
    if OpenMP:
        ofile.write('!$omp end parallel do\n')
    ofile.write('      else if ((factor .ne. 1.0).and.(acc_factor .eq. 1.0)) then\n')
    if OpenMP:
        ofile.write('!$omp parallel do collapse(2)\n')
        ofile.write('!$omp& private(j1,j2,j3,j4)\n')
        ofile.write('!$omp& firstprivate(dim1,dim2,dim3,dim4,factor)\n')
        ofile.write('!$omp& shared(sorted,unsorted)\n')
        ofile.write('!$omp& schedule(static)\n')
    ofile.write('        do j'+a+' = 1,dim'+a+'\n')
    ofile.write('         do j'+b+' = 1,dim'+b+'\n')
    ofile.write('          do j'+c+' = 1,dim'+c+'\n')
    ofile.write('           do j'+d+' = 1,dim'+d+'\n')
    ofile.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
    ofile.write('     &    sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) + \n')
    ofile.write('     &    factor*unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
    ofile.write('           enddo\n')
    ofile.write('          enddo\n')
    ofile.write('         enddo\n')
    ofile.write('        enddo\n')
    if OpenMP:
        ofile.write('!$omp end parallel do\n')
    ofile.write('      else \n')
    if OpenMP:
        ofile.write('!$omp parallel do collapse(2)\n')
        ofile.write('!$omp& private(j1,j2,j3,j4)\n')
        ofile.write('!$omp& firstprivate(dim1,dim2,dim3,dim4,factor,acc_factor)\n')
        ofile.write('!$omp& shared(sorted,unsorted)\n')
        ofile.write('!$omp& schedule(static)\n')
    ofile.write('        do j'+a+' = 1,dim'+a+'\n')
    ofile.write('         do j'+b+' = 1,dim'+b+'\n')
    ofile.write('          do j'+c+' = 1,dim'+c+'\n')
    ofile.write('           do j'+d+' = 1,dim'+d+'\n')
    ofile.write('            sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) = \n')
    ofile.write('     &    acc_factor*sorted(j'+D+'+dim'+D+'*(j'+C+'-1+dim'+C+'*(j'+B+'-1+dim'+B+'*(j'+A+'-1)))) + \n')
    ofile.write('     &    factor*unsorted(j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1))))\n')
    ofile.write('           enddo\n')
    ofile.write('          enddo\n')
    ofile.write('         enddo\n')
    ofile.write('        enddo\n')
    if OpenMP:
        ofile.write('!$omp end parallel do\n')
    ofile.write('      endif\n')
    ofile.write('      return\n')
    ofile.write('      end\n\n')
    return


def generate_tester(ofile, transpose_order, reps, Language):
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    test_name = 'trans_'+perm_to_string(transpose_order)+'_'+Language
    ofile.write('        subroutine test_'+test_name+'(reference, unsorted, sorted,\n')
    ofile.write('     &                dim1, dim2, dim3, dim4)\n')
    ofile.write('        implicit none\n')
    ofile.write('! external variables\n')
    ofile.write('        integer dim1, dim2, dim3, dim4\n')
    ofile.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('        double precision reference(dim1*dim2*dim3*dim4)\n')
    ofile.write('! internal variables\n')
    ofile.write('        integer errors\n')
    ofile.write('        integer loop, omp, fac, r\n')
    ofile.write('        integer loops(4,24) \n')
    ofile.write('        integer bestloop(4,5,2) ! best loop order for (fac,omp) \n')
    ofile.write('        double precision factor, acc_factor\n')
    ofile.write('        double precision t0, t1 \n')
    ofile.write('        double precision dt0 ! reference timing for old_sort \n')
    ofile.write('        double precision dt(24,5,2) ! time for (loop,fac,omp) \n')
    ofile.write('        double precision besttime(5,2) ! best time for (fac,omp) \n')
    ofile.write('        double precision wtime\n')
    ofile.write('        external wtime\n')
    ofile.write('        character*20 labels(2,5)\n')
    ofile.write('        do omp = 1, 2\n')
    ofile.write('         do fac = 1, 5\n')
    ofile.write('          labels(omp,fac) = \'UNDEFINED\' \n')
    ofile.write('          do loop = 1, 24\n')
    ofile.write('           dt(loop,fac,omp) = 1000000.0\n')
    ofile.write('          enddo\n')
    ofile.write('         enddo\n')
    ofile.write('        enddo\n')
    ofile.write('        call init_4d_array(dim1,dim2,dim3,dim4,unsorted)\n')
    for (Factor,Accumulate) in [(1.0,0.0),(37.0,0.0),(1.0,1.0),(37.0,1.0),(37.0,37.0)]:
        if (Accumulate==0.0):
            if Factor==1.0:
                fac = 1
            else:
                fac = 2 
        elif (Accumulate==1.0):
            if Factor==1.0:
                fac = 3
            else:
                fac = 4
        else:
            fac = 5

        if (Accumulate==0.0):
            old_name = 'old_sort_4'
        else:
            old_name = 'old_sortacc_4'
        # flush cache routine belongs here if we want to do that
        ofile.write('        call zero_1d_array(dim1*dim2*dim3*dim4,reference)\n')
        ofile.write('        t0  = wtime() \n')
        ofile.write('        factor = '+str(Factor)+'\n')
        ofile.write('        do r = 1,'+str(reps)+'\n')
        ofile.write('          call '+old_name+'(unsorted,reference,\n')
        ofile.write('     &                    dim1,dim2,dim3,dim4,\n')
        ofile.write('     &                     '+str(A)+','+str(B)+','+str(C)+','+str(D)+',factor)\n')
        ofile.write('        enddo\n')
        ofile.write('        t1  = wtime() \n')
        ofile.write('        dt0 = (t1-t0) \n')
        for OpenMP in [False,True]:
            (omp_name,omp_text) = get_omp_info(OpenMP)
            if OpenMP:
                omp = 2
            else:
                omp = 1
            loop = 0
            for loop_order in generate_permutation_list(Debug):
                loop = loop+1
                a = loop_order[0]
                b = loop_order[1]
                c = loop_order[2]
                d = loop_order[3]
                source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)
                variant = omp_name+'_'+Language
                subroutine_name = source_name+'_'+variant
                ofile.write('        labels('+str(omp)+','+str(fac)+') = \''+variant+'('+str(Factor)+','+str(Accumulate)+')\' \n')
                ofile.write('!******** '+str(a)+','+str(b)+','+str(c)+','+str(d)+' ********\n')
                ofile.write('        fac  = '+str(fac)+' \n')
                ofile.write('        omp  = '+str(omp)+' \n')
                ofile.write('        loop = '+str(loop)+' \n')
                ofile.write('        loops(1,loop) = '+str(a)+'\n')
                ofile.write('        loops(2,loop) = '+str(b)+'\n')
                ofile.write('        loops(3,loop) = '+str(c)+'\n')
                ofile.write('        loops(4,loop) = '+str(d)+'\n')
                ofile.write('        call zero_1d_array(dim1*dim2*dim3*dim4,sorted)\n')
                # flush cache routine belongs here if we want to do that
                ofile.write('        factor     = '+str(Factor)+'\n')
                ofile.write('        acc_factor = '+str(Accumulate)+'\n')
                ofile.write('        t0 = wtime() \n')
                ofile.write('        do r = 1,'+str(reps)+'\n')
                ofile.write('          call '+subroutine_name+'(unsorted,sorted,\n')
                ofile.write('     &                  dim1,dim2,dim3,dim4,factor,acc_factor)\n')
                ofile.write('        enddo\n')
                ofile.write('        t1 = wtime() \n')
                ofile.write('        if (acc_factor .eq. 0.0) then\n')
                ofile.write('          call compare_1d_array(dim1*dim2*dim3*dim4,\n')
                ofile.write('     &                          sorted,reference,errors) \n')
                ofile.write('          if (errors.eq.0) then\n')
                ofile.write('            dt(loop,fac,omp) = (t1-t0)\n')
                ofile.write('          else\n')
                ofile.write('            dt(loop,fac,omp) = 10000000.0\n')
                ofile.write('            print*,\''+subroutine_name+'\'\n')
                ofile.write('            print*,\'errors = \',errors \n')
                ofile.write('            call print_4d_arrays(dim1,dim2,dim3,dim4,\n')
                ofile.write('     &                           sorted,reference) \n')
                ofile.write('          endif\n')
                ofile.write('        endif\n')
    ofile.write('!*************************************************\n')
    ofile.write('! determine the best time and loop order for each of (fac,omp)\n')
    ofile.write('        write(6,2000) '+str(A)+','+str(B)+','+str(C)+','+str(D)+'\n')
    ofile.write('        do omp = 1, 2\n')
    ofile.write('          do fac = 1, 5\n')
    ofile.write('            besttime(fac,omp) = 1000000.0\n')
    ofile.write('            do loop = 1, 24\n')
    ofile.write('              if (dt(loop,fac,omp).lt.besttime(fac,omp)) then\n')
    ofile.write('                besttime(fac,omp) = dt(loop,fac,omp)\n')
    ofile.write('                bestloop(1,fac,omp) = loops(1,loop)\n')
    ofile.write('                bestloop(2,fac,omp) = loops(2,loop)\n')
    ofile.write('                bestloop(3,fac,omp) = loops(3,loop)\n')
    ofile.write('                bestloop(4,fac,omp) = loops(4,loop)\n')
    ofile.write('              endif\n')
    ofile.write('            enddo\n')
    ofile.write('            if (besttime(fac,omp).lt.1000000.0) then\n')
    ofile.write('              write(6,1000) \'best \',labels(omp,fac),\n')
    ofile.write('     &        bestloop(1,fac,omp),bestloop(2,fac,omp),\n')
    ofile.write('     &        bestloop(3,fac,omp),bestloop(4,fac,omp),\n')
    ofile.write('     &        besttime(fac,omp),dt0,dt0/besttime(fac,omp)\n')
    ofile.write('            endif\n')
    ofile.write('          enddo\n')
    ofile.write('        enddo\n')
    ofile.write('        return\n')
    ofile.write(' 1000 format(1x,a8,a22,\' = \',4i1,1x,f9.6,1x,\'(\',f9.6,\' -> \',f7.3,\'x)\')\n')
    ofile.write(' 2000 format(1x,\'transpose: \',4i1)\n')
    ofile.write('        end\n')
    return


def generate_test_driver(Debug, Compiler, subdir, underscoring):
    oname = 'test_trans_all'
    cfile = open(subdir+'/'+oname+'.c','w')
    hfile = open(subdir+'/'+oname+'.h','w')
    cfile.write('#include <stdio.h>\n')
    cfile.write('#include <stdlib.h>\n')
    cfile.write('#include <string.h>\n')
    cfile.write('#include <assert.h>\n\n')
    cfile.write('int posix_memalign(void **memptr, size_t alignment, size_t size); \n\n')
    cfile.write('#ifdef _OPENMP\n')
    cfile.write('#include <omp.h>\n')
    cfile.write('#endif\n\n')
    cfile.write('#ifdef USE_MPI\n')
    cfile.write('#include <mpi.h>\n')
    cfile.write('#endif\n\n')
    cfile.write('#include \"'+oname+'.h\"\n\n')
    cfile.write('int main(int argc, char * argv[])\n')
    cfile.write('{\n')
    cfile.write('    int rc;\n')
    cfile.write('    int dim1 = (argc>1) ? atoi(argv[1]) : 30;\n')
    cfile.write('    int dim2 = (argc>2) ? atoi(argv[2]) : 30;\n')
    cfile.write('    int dim3 = (argc>3) ? atoi(argv[3]) : 30;\n')
    cfile.write('    int dim4 = (argc>4) ? atoi(argv[4]) : 30;\n')
    cfile.write('    int size = dim1*dim2*dim3*dim4;\n\n')
    cfile.write('#ifdef _OPENMP\n')
    cfile.write('    int nthreads = omp_get_max_threads();\n')
    cfile.write('#else\n')
    cfile.write('    int nthreads = 1;\n')
    cfile.write('#endif\n\n')
    cfile.write('    printf(\"dims = %d,%d,%d,%d - OpenMP threads = %d - %s compiler \\n\", dim1, dim2, dim3, dim4, nthreads, \"'+Compiler+'\");\n\n')
    cfile.write('    double * unsorted;\n')
    cfile.write('    double * sorted;\n')
    cfile.write('    double * reference;\n\n')
    cfile.write('    rc = posix_memalign((void**)&unsorted,  128, size*sizeof(double)); assert(rc==0 && unsorted!=NULL);\n')
    cfile.write('    rc = posix_memalign((void**)&sorted,    128, size*sizeof(double)); assert(rc==0 && sorted!=NULL);\n')
    cfile.write('    rc = posix_memalign((void**)&reference, 128, size*sizeof(double)); assert(rc==0 && reference!=NULL);\n\n')
    cfile.write('    /*********** begin testing **********/\n\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug):
            A = transpose_order[0]
            B = transpose_order[1]
            C = transpose_order[2]
            D = transpose_order[3]
            test_name = 'trans_'+perm_to_string(transpose_order)+'_'+Language+underscoring
            cfile.write('    test_'+test_name+'(reference, unsorted, sorted, &dim1, &dim2, &dim3, &dim4);\n')
            hfile.write('void test_'+test_name+'(double * unsorted, double * sorted, double * reference,\n')
            hfile.write('                     int * dim1, int * dim2, int * dim3, int * dim4);\n')
    cfile.write('    /* end testing */\n')
    cfile.write('    free(reference);\n')
    cfile.write('    free(sorted);\n')
    cfile.write('    free(unsorted);\n\n')
    cfile.write('    return 0;\n')
    cfile.write('}\n\n')
    cfile.close()
    hfile.close()


def generate_all_subroutines(Debug, Compiler, subdir, underscoring):
    generate_test_driver(Debug, Compiler, subdir, underscoring)
    if (Debug):
        reps = 3
    else:
        reps = 15
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug):
            source_name = 'test_trans_'+perm_to_string(transpose_order)+'_'+Language
            source_file = open(subdir+'/'+source_name+'.f','w')
            generate_tester(source_file, transpose_order, reps, Language)
            source_file.close()
            for loop_order in generate_permutation_list(Debug):
                source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)+'_'+Language
                source_file = open(subdir+'/'+source_name+'.'+Language,'w')
                source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)
                for OpenMP in [True,False]:
                    (omp_name,omp_text) = get_omp_info(OpenMP)
                    variant = omp_name+'_'+Language
                    print 'generating '+source_name+'_'+variant
                    if (Language=='f'):
                        subroutine_name = source_name+'_'+variant
                        description = '! '+omp_text+'\n'
                        generate_subroutine(source_file, subroutine_name, description, OpenMP, transpose_order, loop_order)
                    if (Language=='c'):
                        cfunction_name = source_name+'_'+variant+underscoring
                        description = '/* '+omp_text+' */\n'
                        generate_cfunction(source_file, cfunction_name, description, OpenMP, transpose_order, loop_order)

                source_file.close()


def generate_makefile(Debug, subdir, Compiler):
    makefile = open(subdir+'/Makefile','w')
    if (Compiler=='GNU' or Compiler=='BGP-GNU' or Compiler=='BGQ-GNU' or Compiler=='Mac'):
        if (Compiler=='GNU'):
            makefile.write('CC       = gcc \n')
            makefile.write('FC       = gfortran \n')
        if (Compiler=='Mac'):
            print 'Using the 4.8 version of GCC...'
            makefile.write('CC       = gcc-mp-4.8 \n')
            makefile.write('FC       = gfortran-mp-4.8 \n')
        if (Compiler=='BGP-GNU'):
            print 'You need to use the GCC 4.3.2 version not the default...'
            makefile.write('CC       = powerpc-bgp-linux-gcc \n')
            makefile.write('FC       = powerpc-bgp-linux-gfortran \n')
        if (Compiler=='BGQ-GNU'):
            makefile.write('CC       = powerpc64-bgq-linux-gcc \n')
            makefile.write('FC       = powerpc64-bgq-linux-gfortran \n')
        makefile.write('LD       = $(FC) \n')
        makefile.write('OMPFLAGS = -fopenmp \n')
        makefile.write('CFLAGS   = -std=c99 $(OMPFLAGS) \n')
        makefile.write('FFLAGS   = -fno-underscoring $(OMPFLAGS) \n')
        if (Debug):
            makefile.write('OFLAGS   = -g -O0 -Wall \n')
        else:
            makefile.write('OFLAGS   = -g -O3 \n')
        makefile.write('LDFLAGS  = $(FFLAGS) $(OFLAGS) \n')
        makefile.write('SFLAGS   = -fverbose-asm \n\n')
    elif (Compiler=='Intel'):
        makefile.write('CC       = icc \n')
        makefile.write('FC       = ifort \n')
        makefile.write('LD       = $(FC) \n')
        makefile.write('OMPFLAGS = -openmp \n')
        makefile.write('CFLAGS   = -std=c99 $(OMPFLAGS) \n')
        makefile.write('FFLAGS   = -assume nounderscore $(OMPFLAGS) \n')
        if (Debug):
            makefile.write('OFLAGS   = -g -O0 \n')
        else:
            makefile.write('OFLAGS   = -g -O3 \n')
        makefile.write('LDFLAGS  = $(FFLAGS) $(OFLAGS) -nofor-main \n')
        makefile.write('SFLAGS   = -fsource-asm -fverbose-asm -fcode-asm \n\n')
    elif (Compiler=='XL' or Compiler=='BG-XL'):
        if (Compiler=='XL'):
            makefile.write('CC       = xlc_r \n')
            makefile.write('FC       = xlf_r \n')
        if (Compiler=='BG-XL'):
            makefile.write('CC       = bgxlc_r \n')
            makefile.write('FC       = bgxlf_r \n')
        makefile.write('LD       = $(FC) \n')
        makefile.write('OMPFLAGS = -qsmp=omp \n')
        makefile.write('CFLAGS   = -qlanglvl=stdc99 $(OMPFLAGS) \n')
        makefile.write('FFLAGS   = $(OMPFLAGS) \n')
        if (Debug):
            makefile.write('OFLAGS   = -g -O3 -qstrict \n')
        else:
            makefile.write('OFLAGS   = -g -O3 -qhot \n')
        makefile.write('LDFLAGS  = $(FFLAGS) $(OFLAGS) \n')
        makefile.write('SFLAGS   = -qlist -qlistopt -qreport -qsource \n\n')
    elif (Compiler=='Cray'):
        makefile.write('CC       = craycc \n')
        makefile.write('FC       = crayftn \n')
        makefile.write('LD       = $(FC) \n')
        makefile.write('OMPFLAGS = -h thread3 \n')
        makefile.write('CFLAGS   = -h c99 $(OMPFLAGS) \n')
        makefile.write('FFLAGS   = $(OMPFLAGS) \n')
        if (Debug):
            makefile.write('OFLAGS   = -g -O0 \n')
        else:
            makefile.write('OFLAGS   = -O3 \n')
        makefile.write('LDFLAGS  = $(FFLAGS) $(OFLAGS) \n')
        makefile.write('SFLAGS   =  \n\n')
    else:
        print 'you must define Compiler'
        exit()

    makefile.write('SOURCES = \\\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug):
            source_name = 'test_trans_'+perm_to_string(transpose_order)+'_'+Language
            makefile.write(source_name+'.f \\\n')

        for transpose_order in generate_permutation_list(Debug):
            for loop_order in generate_permutation_list(Debug):
                source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)+'_'+Language
                makefile.write(source_name+'.f \\\n')


    makefile.write('\n\n')
    makefile.write('OBJECTS = \\\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug):
            source_name = 'test_trans_'+perm_to_string(transpose_order)+'_'+Language
            makefile.write(source_name+'.o \\\n')

        for transpose_order in generate_permutation_list(Debug):
            for loop_order in generate_permutation_list(Debug):
                source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)+'_'+Language
                makefile.write(source_name+'.o \\\n')

    makefile.write('\n\n')
    makefile.write('ASSEMBLY = \\\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug):
            for loop_order in generate_permutation_list(Debug):
                source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)+'_'+Language
                makefile.write(source_name+'.s \\\n')


    for transpose_order in generate_permutation_list(Debug):
        source_name = 'test_trans_'+perm_to_string(transpose_order)
        makefile.write(source_name+'.s \\\n')

    makefile.write('\n\n')
    makefile.write('TESTOBJ = tester_cutil.o tester_futil.o old_sort.o \n\n')
    makefile.write('all: test_trans_all.x  \n\n')
    makefile.write('%.x: %.o libspaghetty.a libtestutil.a \n')
    makefile.write('\t$(LD) $(LDFLAGS) $< -L. -lspaghetty -ltestutil -o $@ \n\n')
    makefile.write('libspaghetty.a: $(OBJECTS) \n')
    makefile.write('\t$(AR) $(ARFLAGS) $@ $(OBJECTS) \n\n')
    makefile.write('libtestutil.a: $(TESTOBJ) \n')
    makefile.write('\t$(AR) $(ARFLAGS) $@ $(TESTOBJ) \n\n')
    makefile.write('asm: $(ASSEMBLY) \n\n')
    makefile.write('%.s: %.f \n')
    makefile.write('\t$(FC) $(FFLAGS) $(SFLAGS) -S $< -o $@ \n\n')
    makefile.write('%.s: %.c \n')
    makefile.write('\t$(CC) $(CFLAGS) $(SFLAGS) -S $< -o $@ \n\n')
    makefile.write('%.o: %.f \n')
    makefile.write('\t$(FC) $(FFLAGS) $(OFLAGS) -c $< -o $@ \n\n')
    makefile.write('%.o: %.c \n')               
    makefile.write('\t$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@ \n\n')
    makefile.write('clean: \n')
    makefile.write('\t$(RM) $(RMFLAGS) test_trans_all.o $(OBJECTS) $(TESTOBJ) $(ASSEMBLY) \n\n')
    makefile.write('realclean: clean \n')
    makefile.write('\t$(RM) $(RMFLAGS) test_trans_all.x libspaghetty.a libtestutil.a \n\n')
    makefile.write('srcclean: realclean \n')
    makefile.write('\t$(RM) $(RMFLAGS) $(SOURCES) \n\n')
    makefile.close()
    return

compilers = ['GNU','BGP-GNU','BGQ-GNU','Intel','XL','BG-XL','Cray','Mac']

if len(sys.argv)>1:
    Compiler = str(sys.argv[1])
    if Compiler not in compilers:
        print Compiler+' is not a valid compiler choice'
        exit()
else:
    print 'Please choose a compiler from GNU, BGP-GNU, BGQ-GNU, Intel, XL, BG-XL, Cray, Mac'
    exit()


if len(sys.argv)>2:
    Debug = (str(sys.argv[2])=='Debug')
else:
    Debug = False


if (Compiler=='GNU' or Compiler=='BGP-GNU' or Compiler=='BGQ-GNU' or Compiler=='Mac'):
    underscoring=''
elif (Compiler=='Intel'):
    underscoring=''
elif (Compiler=='XL' or Compiler=='BG-XL'):
    underscoring=''
elif (Compiler=='Cray'):
    underscoring='_'


if Debug:
    subdir = str(Compiler)+'-Debug'
else:
    subdir = str(Compiler)


os.system('mkdir '+subdir)
os.system('cp tester_cutil.c tester_futil.f old_sort.f '+subdir+'/.')
generate_all_subroutines(Debug, Compiler, subdir, underscoring)
generate_makefile(Debug, subdir, Compiler)