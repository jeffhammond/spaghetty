#!/usr/bin/python

import fileinput
import string
import sys
import os
import subprocess

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in range(sz) for p in perm(l[1:])]

def nwchem_triples_usage():
    # 123456 is included just for verification; it is not used in NWChem
    return [[1,2,3,4,5,6],[2,6,1,5,4,3],[2,6,5,4,3,1],[3,2,6,5,4,1],[3,6,2,1,5,4],[3,6,2,5,1,4],[3,6,2,5,4,1],[4,2,1,6,5,3],[4,3,1,6,5,2],[4,3,2,1,6,5],[4,3,2,6,5,1],[4,3,6,2,1,5],[4,3,6,2,5,1],[4,3,6,5,2,1],[4,6,3,2,1,5],[4,6,3,2,5,1],[4,6,3,5,2,1],[5,2,1,6,4,3],[5,3,1,6,4,2],[5,3,2,1,6,4],[5,3,2,6,4,1],[5,4,1,6,3,2],[5,4,2,1,3,6],[5,4,2,1,6,3],[5,4,2,6,3,1],[5,4,3,1,6,2],[5,4,3,2,1,6],[5,4,3,2,6,1],[5,4,3,6,2,1],[6,2,1,5,4,3],[6,2,5,4,3,1],[6,3,1,5,4,2],[6,3,2,1,5,4],[6,3,2,5,1,4],[6,3,2,5,4,1],[6,4,1,5,3,2],[6,4,2,1,5,3],[6,4,2,5,3,1],[6,4,3,1,5,2],[6,4,3,2,1,5],[6,4,3,2,5,1],[6,4,3,5,2,1],[6,5,1,4,3,2],[6,5,2,1,4,3],[6,5,2,4,1,3],[6,5,2,4,3,1],[6,5,3,1,4,2],[6,5,3,2,1,4],[6,5,3,2,4,1],[6,5,3,4,2,1],[6,5,4,1,3,2],[6,5,4,2,1,3],[6,5,4,2,3,1],[6,5,4,3,1,2],[6,5,4,3,2,1]]

def generate_permutation_list(Debug,which):
    indices = [1,2,3,4,5,6]
    if Debug:
        if which=='perm':
            #permlist = perm(indices)
            permlist = nwchem_triples_usage()
        elif which=='loop':
            #permlist = [indices]
            #permlist = nwchem_triples_usage()
            permlist = perm(indices)
        else:
            print('perm and loop are the only options')
            exit()
    else:
        permlist = perm(indices)
    return permlist


def perm_to_string(perm):
    A = str(perm[0])
    B = str(perm[1])
    C = str(perm[2])
    D = str(perm[3])
    E = str(perm[4])
    F = str(perm[5])
    return A+B+C+D+E+F


def get_omp_info(OpenMP):
    if OpenMP:
        name = 'omp'
        text = 'with OpenMP'
    else:
        name = 'nomp'
        text = 'without OpenMP'
    return (name,text)

#
# NOTES
#
# collapse(4) is not good.  on BGQ it is terrible, probably due to L1 thrashing.

def generate_cfunction(ofile, name, description, OpenMP, transpose_order, loop_order):
    A = str(transpose_order[0])
    B = str(transpose_order[1])
    C = str(transpose_order[2])
    D = str(transpose_order[3])
    E = str(transpose_order[4])
    F = str(transpose_order[5])
    a = str(loop_order[0])
    b = str(loop_order[1])
    c = str(loop_order[2])
    d = str(loop_order[3])
    e = str(loop_order[4])
    f = str(loop_order[5])
    ofile.write(description)
    ofile.write('void '+name+'(const double * restrict unsorted, double * restrict sorted, const int * const dim1, const int * const dim2, const int * const dim3, const int * const dim4, const int * const dim5, const int * const dim6, const double * const factor, const double * const acc_factor)\n')
    ofile.write('{\n')
    ofile.write('  const int d1 = *dim1;\n')
    ofile.write('  const int d2 = *dim2;\n')
    ofile.write('  const int d3 = *dim3;\n')
    ofile.write('  const int d4 = *dim4;\n')
    ofile.write('  const int d5 = *dim5;\n')
    ofile.write('  const int d6 = *dim6;\n')
    ofile.write('  const int f  = *factor;\n')
    ofile.write('  const int g  = *acc_factor;\n')
    for case in [1,2,3,4,5]:
        if case==1:
            ofile.write('  if (f==1.0 && g==0.0) {\n')
        elif case==2:
            ofile.write('  } else if (f!=1.0 && g==0.0) { \n')
        elif case==3:
            ofile.write('  } else if (f==1.0 && g==1.0) { \n')
        elif case==4:
            ofile.write('  } else if (f!=1.0 && g==1.0) { \n')
        elif case==5:
            ofile.write('  } else { \n')
        if OpenMP:
            ofile.write('#ifdef _OPENMP \n')
            if case==1:
                ofile.write('#pragma omp parallel for collapse(3) firstprivate(d1,d2,d3,d4,d5,d6) shared(sorted,unsorted) schedule(static)\n')
            elif case==2:
                ofile.write('#pragma omp parallel for collapse(3) firstprivate(d1,d2,d3,d4,d5,d6,f) shared(sorted,unsorted) schedule(static)\n')
            elif case==3:
                ofile.write('#pragma omp parallel for collapse(3) firstprivate(d1,d2,d3,d4,d5,d6,f) shared(sorted,unsorted) schedule(static)\n')
            elif case==4:
                ofile.write('#pragma omp parallel for collapse(3) firstprivate(d1,d2,d3,d4,d5,d6,f) shared(sorted,unsorted) schedule(static)\n')
            else:
                ofile.write('#pragma omp parallel for collapse(3) firstprivate(d1,d2,d3,d4,d5,d6,f,g) shared(sorted,unsorted) schedule(static)\n')
            ofile.write('#endif \n')
        ofile.write('    for (int j'+a+' = 0; j'+a+'<d'+a+'; j'+a+'++)\n')
        ofile.write('     for (int j'+b+' = 0; j'+b+'<d'+b+'; j'+b+'++)\n')
        ofile.write('      for (int j'+c+' = 0; j'+c+'<d'+c+'; j'+c+'++)\n')
        ofile.write('       for (int j'+d+' = 0; j'+d+'<d'+d+'; j'+d+'++)\n')
        ofile.write('        for (int j'+e+' = 0; j'+e+'<d'+e+'; j'+e+'++)\n')
        ofile.write('         for (int j'+f+' = 0; j'+f+'<d'+f+'; j'+f+'++)\n')
        if case==1:
            ofile.write('          sorted[j'+F+'+d'+F+'*(j'+E+'+d'+E+'*(j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))))] = ')
            ofile.write('unsorted[j6+d6*(j5+d5*(j4+d4*(j3+d3*(j2+d2*(j1)))))];\n')
        elif case==2:
            ofile.write('          sorted[j'+F+'+d'+F+'*(j'+E+'+d'+E+'*(j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))))] = ')
            ofile.write('f*unsorted[j6+d6*(j5+d5*(j4+d4*(j3+d3*(j2+d2*(j1)))))];\n')
        elif case==3:
            ofile.write('          sorted[j'+F+'+d'+F+'*(j'+E+'+d'+E+'*(j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))))] += ')
            ofile.write('unsorted[j6+d6*(j5+d5*(j4+d4*(j3+d3*(j2+d2*(j1)))))];\n')
        elif case==4:
            ofile.write('          sorted[j'+F+'+d'+F+'*(j'+E+'+d'+E+'*(j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))))] += ')
            ofile.write('f*unsorted[j6+d6*(j5+d5*(j4+d4*(j3+d3*(j2+d2*(j1)))))];\n')
        else:
            ofile.write('          sorted[j'+F+'+d'+F+'*(j'+E+'+d'+E+'*(j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))))] = ')
            ofile.write('g*sorted[j'+F+'+d'+F+'*(j'+E+'+d'+E+'*(j'+D+'+d'+D+'*(j'+C+'+d'+C+'*(j'+B+'+d'+B+'*(j'+A+')))))] + ')
            ofile.write('f*unsorted[j6+d6*(j5+d5*(j4+d4*(j3+d3*(j2+d2*(j1)))))];\n')
    ofile.write('  }\n\n')
    ofile.write('  return;\n')
    ofile.write('}\n\n')
    return


def generate_subroutine(ofile, name, description, OpenMP, transpose_order, loop_order):
    A = str(transpose_order[0])
    B = str(transpose_order[1])
    C = str(transpose_order[2])
    D = str(transpose_order[3])
    E = str(transpose_order[4])
    F = str(transpose_order[5])
    a = str(loop_order[0])
    b = str(loop_order[1])
    c = str(loop_order[2])
    d = str(loop_order[3])
    e = str(loop_order[4])
    f = str(loop_order[5])
    ofile.write(description)
    ofile.write('      subroutine '+name+'(unsorted,sorted,\n')
    ofile.write('     &              d1,d2,d3,d4,d5,d6,\n')
    ofile.write('     &              f,g)\n')
    ofile.write('      implicit none\n')
    ofile.write('      integer d1,d2,d3,d4,d5,d6\n')
    ofile.write('      integer j1,j2,j3,j4,j5,j6\n')
    ofile.write('      double precision sorted(d1*d2*d3*d4*d5*d6)\n')
    ofile.write('      double precision unsorted(d1*d2*d3*d4*d5*d6)\n')
    ofile.write('      double precision f\n')
    ofile.write('      double precision g\n')
    for case in [1,2,3,4,5]:
        if case==1:
            ofile.write('      if ((f .eq. 1.0).and.(g .eq. 0.0)) then\n')
        elif case==2:
            ofile.write('      else if ((f .ne. 1.0).and.(g .eq. 0.0)) then\n')
        elif case==3:
            ofile.write('      else if ((f .eq. 1.0).and.(g .eq. 1.0)) then\n')
        elif case==4:
            ofile.write('      else if ((f .ne. 1.0).and.(g .eq. 1.0)) then\n')
        elif case==5:
            ofile.write('      else \n')
        if OpenMP:
            # need to see if 3 is really the right number of loops to collapse
            ofile.write('!$omp parallel do collapse(3)\n')
            ofile.write('!$omp& private(j1,j2,j3,j4,j5,j6)\n')
            if case==1 or case==3:
                ofile.write('!$omp& firstprivate(d1,d2,d3,d4,d5,d6)\n')
            elif case==2 or case==4:
                ofile.write('!$omp& firstprivate(d1,d2,d3,d4,d5,d6,f)\n')
            elif case==5:
                ofile.write('!$omp& firstprivate(d1,d2,d3,d4,d5,d6,f,g)\n')
            ofile.write('!$omp& shared(sorted,unsorted)\n')
            ofile.write('!$omp& schedule(static)\n')
        ofile.write('      do j'+a+' = 1,d'+a+'\n')
        ofile.write('       do j'+b+' = 1,d'+b+'\n')
        ofile.write('        do j'+c+' = 1,d'+c+'\n')
        ofile.write('         do j'+d+' = 1,d'+d+'\n')
        ofile.write('          do j'+e+' = 1,d'+e+'\n')
        ofile.write('           do j'+f+' = 1,d'+f+'\n')
        if case==1:
            ofile.write('          sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) = \n')
            ofile.write('     &  unsorted(j6+d6*(j5-1+d5*(j4-1+d4*(j3-1+d3*(j2-1+d2*(j1-1))))))\n')
        elif case==2:        
            ofile.write('          sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) = \n')
            ofile.write('     &  sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) + \n')
            ofile.write('     &  f*unsorted(j6+d6*(j5-1+d5*(j4-1+d4*(j3-1+d3*(j2-1+d2*(j1-1))))))\n')
        elif case==3:        
            ofile.write('          sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) = \n')
            ofile.write('     &  sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) + \n')
            ofile.write('     &  unsorted(j6+d6*(j5-1+d5*(j4-1+d4*(j3-1+d3*(j2-1+d2*(j1-1))))))\n')
        elif case==4:        
            ofile.write('          sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) = \n')
            ofile.write('     &  sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) + \n')
            ofile.write('     &  f*unsorted(j6+d6*(j5-1+d5*(j4-1+d4*(j3-1+d3*(j2-1+d2*(j1-1))))))\n')
        elif case==5:        
            ofile.write('          sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) = \n')
            ofile.write('     &  g*sorted(j'+F+'+d'+F+'*(j'+E+'-1+d'+E+'*(j'+D+'-1+d'+D+'*(j'+C+'-1+d'+C+'*(j'+B+'-1+d'+B+'*(j'+A+'-1)))))) + \n')
            ofile.write('     &  f*unsorted(j6+d6*(j5-1+d5*(j4-1+d4*(j3-1+d3*(j2-1+d2*(j1-1))))))\n')
        ofile.write('           enddo\n')
        ofile.write('          enddo\n')
        ofile.write('         enddo\n')
        ofile.write('        enddo\n')
        ofile.write('       enddo\n')
        ofile.write('      enddo\n')
        if OpenMP:
            ofile.write('!$omp end parallel do\n')
    ofile.write('      endif\n')
    ofile.write('      return\n')
    ofile.write('      end\n\n')
    return


def generate_tester(ofile, transpose_order, reps, Language):
    A = str(transpose_order[0])
    B = str(transpose_order[1])
    C = str(transpose_order[2])
    D = str(transpose_order[3])
    E = str(transpose_order[4])
    F = str(transpose_order[5])
    test_name = 'trans_'+perm_to_string(transpose_order)+'_'+Language
    ofile.write('        subroutine test_'+test_name+'(reference, unsorted, sorted,\n')
    ofile.write('     &                dim1, dim2, dim3, dim4, dim5, dim6)\n')
    ofile.write('        implicit none\n')
    ofile.write('! external variables\n')
    ofile.write('        integer dim1, dim2, dim3, dim4, dim5, dim6\n')
    ofile.write('        integer dim123456\n')
    ofile.write('        double precision sorted(dim1*dim2*dim3*dim4*dim5*dim6)\n')
    ofile.write('        double precision unsorted(dim1*dim2*dim3*dim4*dim5*dim6)\n')
    ofile.write('        double precision reference(dim1*dim2*dim3*dim4*dim5*dim6)\n')
    ofile.write('! internal variables\n')
    ofile.write('        integer errors\n')
    ofile.write('        integer loop, omp, fac, r\n')
    ofile.write('        integer loops(6,720) \n')
    ofile.write('        integer bestloop(6,5,2) ! best loop order for (fac,omp) \n')
    ofile.write('        double precision factor, acc_factor\n')
    ofile.write('        double precision t0, t1 \n')
    ofile.write('        double precision dt0 ! reference timing for old_sort \n')
    ofile.write('        double precision dt1 ! reference timing for old_sortacc \n')
    ofile.write('        double precision dtX ! reference timing for comparison \n')
    ofile.write('        double precision dt(720,5,2) ! time for (loop,fac,omp) \n')
    ofile.write('        double precision besttime(5,2) ! best time for (fac,omp) \n')
    ofile.write('        double precision wtime\n')
    ofile.write('        external wtime\n')
    ofile.write('        character*20 labels(2,5)\n')
    ofile.write('        dim123456=dim1*dim2*dim3*dim4*dim5*dim6\n')
    ofile.write('        do omp = 1, 2\n')
    ofile.write('         do fac = 1, 5\n')
    ofile.write('          labels(omp,fac) = \'UNDEFINED\' \n')
    ofile.write('          do loop = 1, 720\n')
    ofile.write('           dt(loop,fac,omp) = 1000000.0\n')
    ofile.write('          enddo\n')
    ofile.write('         enddo\n')
    ofile.write('        enddo\n')
    ofile.write('        call init_6d_array(dim1,dim2,dim3,dim4,dim5,dim6,unsorted)\n')
    for (Factor,Accumulate) in [(1.0,0.0)]: #,(37.0,0.0),(1.0,1.0),(37.0,1.0),(37.0,37.0)]:
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
            old_name = 'old_sort_6'
        else:
            old_name = 'old_sortacc_6'
        # flush cache routine belongs here if we want to do that
        ofile.write('        call zero_1d_array(dim123456,reference)\n')
        ofile.write('        t0  = wtime() \n')
        ofile.write('        factor = '+str(Factor)+'\n')
        ofile.write('        do r = 1,'+str(reps)+'\n')
        ofile.write('          call '+old_name+'(unsorted,reference,\n')
        ofile.write('     &                    dim1,dim2,dim3,dim4,dim5,dim6,\n')
        ofile.write('     &                     '+str(A)+','+str(B)+','+str(C)+','+str(D)+','+str(E)+','+str(F)+',factor)\n')
        ofile.write('        enddo\n')
        ofile.write('        t1  = wtime() \n')
        if (Accumulate==0.0):
            ofile.write('        dt0 = (t1-t0) \n')
        else:
            ofile.write('        dt1 = (t1-t0) \n')
        for OpenMP in [False,True]:
            (omp_name,omp_text) = get_omp_info(OpenMP)
            if OpenMP:
                omp = 2
            else:
                omp = 1
            loop = 0
            for loop_order in generate_permutation_list(Debug,'loop'):
                loop = loop+1
                a = str(loop_order[0])
                b = str(loop_order[1])
                c = str(loop_order[2])
                d = str(loop_order[3])
                e = str(loop_order[4])
                f = str(loop_order[5])
                source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)
                variant = omp_name+'_'+Language
                subroutine_name = source_name+'_'+variant
                ofile.write('        labels('+str(omp)+','+str(fac)+') = \''+variant+'('+str(Factor)+','+str(Accumulate)+')\' \n')
                ofile.write('!******** '+str(a)+','+str(b)+','+str(c)+','+str(d)+','+str(e)+','+str(f)+' ********\n')
                ofile.write('        fac  = '+str(fac)+' \n')
                ofile.write('        omp  = '+str(omp)+' \n')
                ofile.write('        loop = '+str(loop)+' \n')
                ofile.write('        loops(1,loop) = '+str(a)+'\n')
                ofile.write('        loops(2,loop) = '+str(b)+'\n')
                ofile.write('        loops(3,loop) = '+str(c)+'\n')
                ofile.write('        loops(4,loop) = '+str(d)+'\n')
                ofile.write('        loops(5,loop) = '+str(e)+'\n')
                ofile.write('        loops(6,loop) = '+str(f)+'\n')
                ofile.write('        call zero_1d_array(dim123456,sorted)\n')
                # flush cache routine belongs here if we want to do that
                ofile.write('        factor     = '+str(Factor)+'\n')
                ofile.write('        acc_factor = '+str(Accumulate)+'\n')
                ofile.write('        t0 = wtime() \n')
                ofile.write('        do r = 1,'+str(reps)+'\n')
                ofile.write('          call '+subroutine_name+'(unsorted,sorted,\n')
                ofile.write('     &                  dim1,dim2,dim3,dim4,dim5,dim6,factor,acc_factor)\n')
                ofile.write('        enddo\n')
                ofile.write('        t1 = wtime() \n')
                ofile.write('        if (acc_factor .eq. 0.0) then\n')
                ofile.write('          call compare_1d_array(dim123456,\n')
                ofile.write('     &                          sorted,reference,errors) \n')
                ofile.write('        else\n')
                ofile.write('          errors = 0\n')
                ofile.write('        endif\n')
                ofile.write('        if (errors.eq.0) then\n')
                ofile.write('          dt(loop,fac,omp) = (t1-t0)\n')
                ofile.write('        else\n')
                ofile.write('          dt(loop,fac,omp) = 10000000.0\n')
                ofile.write('          print*,\''+subroutine_name+'\'\n')
                ofile.write('          print*,\'errors = \',errors \n')
                ofile.write('          call print_6d_arrays(dim1,dim2,dim3,dim4,dim5,dim6,\n')
                ofile.write('     &                         sorted,reference) \n')
                ofile.write('        endif\n')
    ofile.write('!*************************************************\n')
    ofile.write('! determine the best time and loop order for each of (fac,omp)\n')
    ofile.write('        write(6,2000) '+str(A)+','+str(B)+','+str(C)+','+str(D)+','+str(E)+','+str(F)+'\n')
    ofile.write('        if (dt0.gt.(1.0e-9)) then\n')
    ofile.write('          write(6,1500) \'old_sort_6   \',dt0,(8*dim123456)/dt0\n')
    ofile.write('        endif\n')
    ofile.write('        if (dt1.gt.(1.0e-9)) then\n')
    ofile.write('          write(6,1500) \'old_sortacc_6\',dt1,(8*dim123456)/dt1\n')
    ofile.write('        endif\n')
    ofile.write('        do omp = 1, 2\n')
    ofile.write('          do fac = 1, 5\n')
    ofile.write('            ! make sure these are right for the fac cases at hand \n')
    ofile.write('            if (fac.le.2) dtX = dt0 \n')
    ofile.write('            if (fac.gt.2) dtX = dt1 \n')
    ofile.write('            besttime(fac,omp) = 1000000.0\n')
    ofile.write('            do loop = 1, 720\n')
    ofile.write('              if (dt(loop,fac,omp).lt.besttime(fac,omp)) then\n')
    ofile.write('                besttime(fac,omp) = dt(loop,fac,omp)\n')
    ofile.write('                bestloop(1,fac,omp) = loops(1,loop)\n')
    ofile.write('                bestloop(2,fac,omp) = loops(2,loop)\n')
    ofile.write('                bestloop(3,fac,omp) = loops(3,loop)\n')
    ofile.write('                bestloop(4,fac,omp) = loops(4,loop)\n')
    ofile.write('                bestloop(5,fac,omp) = loops(5,loop)\n')
    ofile.write('                bestloop(6,fac,omp) = loops(6,loop)\n')
    ofile.write('              endif\n')
    ofile.write('            enddo\n')
    ofile.write('            if (besttime(fac,omp).lt.1000000.0) then\n')
    ofile.write('              write(6,1000) \'best \',labels(omp,fac),\n')
    ofile.write('     &        bestloop(1,fac,omp),bestloop(2,fac,omp),\n')
    ofile.write('     &        bestloop(3,fac,omp),bestloop(4,fac,omp),\n')
    ofile.write('     &        bestloop(5,fac,omp),bestloop(6,fac,omp),\n')
    ofile.write('     &        besttime(fac,omp),dtX/besttime(fac,omp),\n')
    ofile.write('     &        (8*dim123456)/besttime(fac,omp)\n')
    ofile.write('            endif\n')
    ofile.write('          enddo\n')
    ofile.write('        enddo\n')
    ofile.write('        return\n')
    ofile.write(' 1000 format(1x,a8,a22,\' = \',6i1,1x,f9.6,1x,\'(\',f7.3,\'x,\',e10.3,\' B/s)\')\n')
    ofile.write(' 1500 format(11x,a13,7x,\' = \',5x,f9.6,1x,\'(\',9x,e10.3,\' B/s)\')\n')
    ofile.write(' 2000 format(1x,\'transpose: \',6i1)\n')
    ofile.write('        end\n')
    return


def generate_test_driver(Debug, Compiler, subdir, underscoring, rev, flags):
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
    cfile.write('    int dim1 = (argc>1) ? atoi(argv[1]) : 16;\n')
    cfile.write('    int dim2 = (argc>2) ? atoi(argv[2]) : 16;\n')
    cfile.write('    int dim3 = (argc>3) ? atoi(argv[3]) : 16;\n')
    cfile.write('    int dim4 = (argc>4) ? atoi(argv[4]) : 16;\n')
    cfile.write('    int dim5 = (argc>5) ? atoi(argv[5]) : 16;\n')
    cfile.write('    int dim6 = (argc>6) ? atoi(argv[6]) : 16;\n')
    cfile.write('    int size = dim1*dim2*dim3*dim4*dim5*dim6;\n\n')
    cfile.write('#ifdef _OPENMP\n')
    cfile.write('    int nthreads = omp_get_max_threads();\n')
    cfile.write('#else\n')
    cfile.write('    int nthreads = 1;\n')
    cfile.write('#endif\n\n')
    cfile.write('    printf(\"SPAGHETTY: generator2.py r'+str(rev)+'\\n\");\n')
    cfile.write('    printf(\"dims = %d,%d,%d,%d,%d,%d - OpenMP threads = %d \\n\", dim1, dim2, dim3, dim4, dim5, dim6, nthreads);\n')
    cfile.write('    printf(\"%s compiler: %s \\n\", \"'+Compiler+'\",\"'+flags+'\");\n\n')
    cfile.write('    fflush(stdout);\n')
    cfile.write('    double * unsorted = NULL;\n')
    cfile.write('    double * sorted = NULL;\n')
    cfile.write('    double * reference = NULL;\n\n')
    cfile.write('    rc = posix_memalign((void**)&unsorted,  128, size*sizeof(double)); assert(rc==0 && unsorted!=NULL);\n')
    cfile.write('    rc = posix_memalign((void**)&sorted,    128, size*sizeof(double)); assert(rc==0 && sorted!=NULL);\n')
    cfile.write('    rc = posix_memalign((void**)&reference, 128, size*sizeof(double)); assert(rc==0 && reference!=NULL);\n\n')
    cfile.write('    /*********** begin testing **********/\n\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug,'perm'):
            A = transpose_order[0]
            B = transpose_order[1]
            C = transpose_order[2]
            D = transpose_order[3]
            E = transpose_order[4]
            F = transpose_order[5]
            test_name = 'trans_'+perm_to_string(transpose_order)+'_'+Language+underscoring
            cfile.write('    test_'+test_name+'(reference, unsorted, sorted, &dim1, &dim2, &dim3, &dim4, &dim5, &dim6);\n')
            hfile.write('void test_'+test_name+'(double * unsorted, double * sorted, double * reference,\n')
            hfile.write('                     int * dim1, int * dim2, int * dim3, int * dim4, int * dim5, int * dim6);\n')
    cfile.write('    /* end testing */\n')
    cfile.write('    free(reference);\n')
    cfile.write('    free(sorted);\n')
    cfile.write('    free(unsorted);\n\n')
    cfile.write('    return 0;\n')
    cfile.write('}\n\n')
    cfile.close()
    hfile.close()


def generate_all_subroutines(Debug, Compiler, subdir, underscoring):
    if (Debug):
        reps = 1
    else:
        reps = 15
    for transpose_order in generate_permutation_list(Debug,'perm'):
        for Language in ['f','c']:
            source_name = 'test_trans_'+perm_to_string(transpose_order)+'_'+Language
            source_file = open(subdir+'/'+source_name+'.F','w')
            generate_tester(source_file, transpose_order, reps, Language)
            source_file.close()
            # 720 files is enough parallelism for make...
            source_name = 'trans_'+perm_to_string(transpose_order)+Language
            source_file = open(subdir+'/'+source_name+'.'+Language,'w')
            print('generating '+source_name)
            for loop_order in generate_permutation_list(Debug,'loop'):
                #source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)+'_'+Language
                #source_file = open(subdir+'/'+source_name+'.'+Language,'w')
                source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)
                for OpenMP in [False,True]:
                    (omp_name,omp_text) = get_omp_info(OpenMP)
                    variant = omp_name+'_'+Language
                    #print 'generating '+source_name+'_'+variant
                    if (Language=='f'):
                        subroutine_name = source_name+'_'+variant
                        description = '! '+omp_text+'\n'
                        generate_subroutine(source_file, subroutine_name, description, OpenMP, transpose_order, loop_order)
                    if (Language=='c'):
                        cfunction_name = source_name+'_'+variant+underscoring
                        description = '/* '+omp_text+' */\n'
                        generate_cfunction(source_file, cfunction_name, description, OpenMP, transpose_order, loop_order)

                #source_file.close()
            source_file.close()


def generate_makefile(Debug, subdir, Compiler, rev):
    makefile = open(subdir+'/Makefile','w')
    if (Compiler=='GNU' or Compiler=='BGP-GNU' or Compiler=='BGQ-GNU' or Compiler=='Mac'):
        if (Compiler=='GNU'):
            makefile.write('CC       = gcc \n')
            makefile.write('FC       = gfortran \n')
        if (Compiler=='BGP-GNU'):
            print('You need to use the GCC 4.3.2 version not the default...')
            makefile.write('CC       = powerpc-bgp-linux-gcc \n')
            makefile.write('FC       = powerpc-bgp-linux-gfortran \n')
        if (Compiler=='BGQ-GNU'):
            makefile.write('CC       = powerpc64-bgq-linux-gcc \n')
            makefile.write('FC       = powerpc64-bgq-linux-gfortran \n')
        makefile.write('LD       = $(FC) \n')
        makefile.write('OMPFLAGS = -fopenmp \n')
        makefile.write('CFLAGS   = -std=c99 $(OMPFLAGS) \n')
        makefile.write('FFLAGS   = -fno-underscoring $(OMPFLAGS) \n')
        if (False): #Debug):
            makefile.write('RFLAGS   = -g -O0 -Wall \n')
            makefile.write('OFLAGS   = -g -O0 -Wall \n')
        else:
            makefile.write('RFLAGS   = -O1  \n')
            makefile.write('OFLAGS   = -O1 \n')
        flags = '-fopenmp -std=c99 -fno-underscoring -O3'
        makefile.write('LDFLAGS  = $(FFLAGS) $(RFLAGS) \n')
        makefile.write('SFLAGS   = -fverbose-asm \n\n')
    elif (Compiler=='LLVM' or Compiler=='BGQ-LLVM'):
        if (Compiler=='LLVM'):
            makefile.write('CC       = clang \n')
            makefile.write('FC       = gfortran \n')
        if (Compiler=='BGQ-LLVM'):
            makefile.write('CC       = bgclang \n')
            makefile.write('FC       = powerpc64-bgq-linux-gfortran \n')
        makefile.write('LD       = $(FC) \n')
        makefile.write('OMPFLAGS = -fopenmp \n')
        makefile.write('CFLAGS   = -std=c99 $(OMPFLAGS) \n')
        makefile.write('FFLAGS   = -fno-underscoring $(OMPFLAGS) \n')
        if (Debug):
            makefile.write('RFLAGS   = -g -O0 -Wall \n')
            makefile.write('OFLAGS   = -g -O0 -Wall \n')
        else:
            makefile.write('RFLAGS   = -O2  \n')
            makefile.write('OFLAGS   = -O3 \n')
        flags = '-fopenmp -std=c99 -fno-underscoring -O3'
        makefile.write('LDFLAGS  = $(FFLAGS) $(RFLAGS) \n')
        makefile.write('SFLAGS   = -fverbose-asm \n\n')
    elif (Compiler=='Intel'):
        makefile.write('CC       = icc \n')
        makefile.write('FC       = ifort \n')
        makefile.write('LD       = $(FC) \n')
        makefile.write('OMPFLAGS = -openmp \n')
        makefile.write('CFLAGS   = -std=c99 $(OMPFLAGS) \n')
        makefile.write('FFLAGS   = -assume nounderscore $(OMPFLAGS) \n')
        if (False): #Debug):
            makefile.write('RFLAGS   = -g -O0 \n')
            makefile.write('OFLAGS   = -g -O0 \n')
        else:
            makefile.write('RFLAGS   = -O2 -mavx \n')
            makefile.write('OFLAGS   = -O2 -mavx \n')
        flags = '-openmp -std=c99 -assume nounderscore -O2 -mavx'
        makefile.write('LDFLAGS  = $(FFLAGS) $(RFLAGS) -nofor-main \n')
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
            makefile.write('RFLAGS   = -g -O3 -qstrict \n')
            makefile.write('OFLAGS   = -g -O3 -qstrict \n')
        else:
            makefile.write('RFLAGS   = -O3 -qhot -qnoipa -qsimd=auto \n')
            makefile.write('OFLAGS   = -O3 -qhot -qnoipa -qsimd=auto \n')
        flags = '-qsmp=omp -qlanglvl=stdc99 -g -O3 -qhot -qsimd=auto'
        makefile.write('LDFLAGS  = $(FFLAGS) $(RFLAGS) \n')
        makefile.write('SFLAGS   = -qlist -qlistopt -qreport -qsource \n\n')
    elif (Compiler=='Cray'):
        makefile.write('CC       = craycc \n')
        makefile.write('FC       = crayftn \n')
        makefile.write('LD       = $(FC) \n')
        makefile.write('OMPFLAGS = -h thread3 \n')
        makefile.write('CFLAGS   = -h c99 $(OMPFLAGS) \n')
        makefile.write('FFLAGS   = $(OMPFLAGS) \n')
        if (Debug):
            makefile.write('RFLAGS   = -g -O0 \n')
            makefile.write('OFLAGS   = -g -O0 \n')
        else:
            makefile.write('RFLAGS   = -O1 \n')
            makefile.write('OFLAGS   = -O2 \n')
        flags = '-h thread3 -h c99 -O3'
        makefile.write('LDFLAGS  = $(FFLAGS) $(RFLAGS) \n')
        makefile.write('SFLAGS   =  \n\n')
    else:
        print('you must define Compiler')
        exit()

    makefile.write('\n\n')
    makefile.write('SOURCES = \\\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug,'perm'):
            source_name = 'test_trans_'+perm_to_string(transpose_order)+'_'+Language
            makefile.write(source_name+'.F \\\n')
            source_name = 'trans_'+perm_to_string(transpose_order)+Language
            makefile.write(source_name+'.'+Language+' \\\n')
        #for transpose_order in generate_permutation_list(Debug,'perm'):
        #    for loop_order in generate_permutation_list(Debug,'loop'):
        #        source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)+'_'+Language
        #        makefile.write(source_name+'.f \\\n')


    makefile.write('\n\n')
    makefile.write('ROBJECTS = \\\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug,'perm'):
            source_name = 'test_trans_'+perm_to_string(transpose_order)+'_'+Language
            makefile.write(source_name+'.o \\\n')

    makefile.write('\n\n')
    makefile.write('OBJECTS = \\\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug,'perm'):
            source_name = 'trans_'+perm_to_string(transpose_order)+Language
            makefile.write(source_name+'.o \\\n')
            #for loop_order in generate_permutation_list(Debug,'loop'):
            #    source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)+'_'+Language
            #    makefile.write(source_name+'.o \\\n')

    makefile.write('\n\n')
    makefile.write('ASSEMBLY = \\\n')
    for Language in ['f','c']:
        for transpose_order in generate_permutation_list(Debug,'perm'):
            source_name = 'trans_'+perm_to_string(transpose_order)+Language
            makefile.write(source_name+'.s \\\n')
            #for loop_order in generate_permutation_list(Debug,'loop'):
            #    source_name = 'trans_'+perm_to_string(transpose_order)+'_loop_'+perm_to_string(loop_order)+'_'+Language
            #    makefile.write(source_name+'.s \\\n')


    for transpose_order in generate_permutation_list(Debug,'perm'):
        source_name = 'test_trans_'+perm_to_string(transpose_order)
        makefile.write(source_name+'.s \\\n')

    makefile.write('\n\n')
    makefile.write('TESTOBJ = tester_cutil.o tester_futil.o old_sort.o \n\n')
    makefile.write('all: test_trans_all.x  \n\n')
    makefile.write('%.x: %.o libtestutil.a libspaghetty.a \n')
    makefile.write('\t$(LD) $(LDFLAGS) $< -L. -ltestutil -lspaghetty -o $@ \n\n')
    makefile.write('libspaghetty.a: $(OBJECTS) \n')
    makefile.write('\t$(AR) $(ARFLAGS) $@ $(OBJECTS) \n\n')
    makefile.write('libtestutil.a: $(TESTOBJ) $(ROBJECTS) \n')
    makefile.write('\t$(AR) $(ARFLAGS) $@ $(TESTOBJ) $(ROBJECTS) \n\n')
    makefile.write('asm: $(ASSEMBLY) \n\n')
    makefile.write('%.s: %.f \n')
    makefile.write('\t$(FC) $(FFLAGS) $(OFLAGS) $(SFLAGS) -S $< -o $@ \n\n')
    makefile.write('%.s: %.c \n')
    makefile.write('\t$(CC) $(CFLAGS) $(OFLAGS) $(SFLAGS) -S $< -o $@ \n\n')
    makefile.write('%.o: %.F \n')
    makefile.write('\t$(FC) $(FFLAGS) $(RFLAGS) -c $< -o $@ \n\n')
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
    generate_test_driver(Debug, Compiler, subdir, underscoring, rev, flags)
    return

compilers = ['GNU','BGP-GNU','BGQ-GNU','Intel','XL','BG-XL','Cray','Mac','LLVM','BGQ-LLVM']

if len(sys.argv)>1:
    Compiler = str(sys.argv[1])
    if Compiler not in compilers:
        print(Compiler+' is not a valid compiler choice')
        exit()
else:
    print('Please choose a compiler from GNU, BGP-GNU, BGQ-GNU, Intel, XL, BG-XL, Cray, Mac, LLVM, BGQ-LLVM')
    exit()


if len(sys.argv)>2:
    Debug = (str(sys.argv[2])=='Debug')
else:
    Debug = False


if (Compiler in ['GNU','BGP-GNU','BGQ-GNU','Intel','XL','BG-XL','Mac','LLVM','BGQ-LLVM']):
    underscoring=''
elif (Compiler in ['Cray']):
    underscoring='_'


if Debug:
    subdir = str(Compiler)+'-Debug'
else:
    subdir = str(Compiler)


rev = 'git'
os.system('mkdir -p '+subdir)
os.system('cp tester_cutil.c tester_futil.F old_sort.f '+subdir+'/.')
generate_all_subroutines(Debug, Compiler, subdir, underscoring)
generate_makefile(Debug, subdir, Compiler, rev)
