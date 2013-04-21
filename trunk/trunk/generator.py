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
    ofile.write('        subroutine test_'+test_name+'(reference, unsorted, sorted,\n')
    ofile.write('     &                dim1, dim2, dim3, dim4)\n')
    ofile.write('        implicit none\n')
    ofile.write('! external variables\n')
    ofile.write('        double precision besttime(3,2) ! best time for (fac,omp) \n')
    ofile.write('        integer bestloop(4,3,2) ! best loop order for (fac,omp) \n')
    ofile.write('        double precision sorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('        double precision unsorted(dim1*dim2*dim3*dim4)\n')
    ofile.write('        double precision reference(dim1*dim2*dim3*dim4)\n')
    ofile.write('        integer dim1, dim2, dim3, dim4\n')
    ofile.write('! internal variables\n')
    ofile.write('        integer errors\n')
    ofile.write('        integer loop, omp, fac, r\n')
    ofile.write('        integer loops(4,24) \n')
    ofile.write('        double precision factor\n')
    ofile.write('        double precision t0, t1 \n')
    ofile.write('        double precision dt0 ! reference timing for old_sort \n')
    ofile.write('        double precision dt(24,3,2) ! time for (loop,fac,omp) \n')
    ofile.write('        double precision wtime\n')
    ofile.write('        external wtime\n')
    ofile.write('        character*10 labels(2,3)\n')
    ofile.write('        do omp = 1, 2\n')
    ofile.write('          do fac = 1, 3\n')
    ofile.write('            do loop = 1, 24\n')
    ofile.write('              dt(loop,fac,omp) = 1000000.0\n')
    ofile.write('            enddo\n')
    ofile.write('          enddo\n')
    ofile.write('        enddo\n')
    ofile.write('        call init_4d_array(dim1,dim2,dim3,dim4,unsorted)\n')
    ofile.write('        call zero_1d_array(dim1*dim2*dim3*dim4,reference)\n')
    for Factor in [1.0,-1.0,37.0]:
        (fac_name,fac_text) = get_fac_info(Factor)
        if Factor==1.0:
            fac = 1
        elif Factor==-1.0:
            fac = 2
        else:
            fac = 3
        # flush cache routine belongs here if we want to do that
        ofile.write('        t0  = wtime() \n')
        ofile.write('        factor = '+str(Factor)+'\n')
        ofile.write('        do r = 1,20\n')
        ofile.write('          call old_sort_4(unsorted,reference,\n')
        ofile.write('     &                    dim1,dim2,dim3,dim4,\n')
        ofile.write('     &                     '+str(A)+','+str(B)+','+str(C)+','+str(D)+',factor)\n')
        ofile.write('        enddo\n')
        ofile.write('        t1  = wtime() \n')
        ofile.write('        dt0 = (t1-t0) \n')
        ofile.write('!        print*,\'old_sort_4: t0,t1,dt = \',t0,t1,(t1-t0) \n')
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
                variant = omp_name+'_'+fac_name
                subroutine_name = source_name+'_'+variant
                ofile.write('        labels('+str(omp)+','+str(fac)+') = \''+variant+'\' \n')
                ofile.write('!******** '+str(a)+','+str(b)+','+str(c)+','+str(d)+' ********\n')
                ofile.write('        fac  = '+str(fac)+' \n')
                ofile.write('        omp  = '+str(omp)+' \n')
                ofile.write('        loop = '+str(loop)+' \n')
                ofile.write('!        print*,\'loop,fac,omp = \',loop,fac,omp \n')
                ofile.write('        loops(1,loop) = '+str(a)+'\n')
                ofile.write('        loops(2,loop) = '+str(b)+'\n')
                ofile.write('        loops(3,loop) = '+str(c)+'\n')
                ofile.write('        loops(4,loop) = '+str(d)+'\n')
                ofile.write('        call zero_1d_array(dim1*dim2*dim3*dim4,sorted)\n')
                # flush cache routine belongs here if we want to do that
                ofile.write('        t0 = wtime() \n')
                if Factor==1.0:
                    ofile.write('        call '+subroutine_name+'(unsorted,sorted,\n')
                    ofile.write('     &                dim1,dim2,dim3,dim4)\n')
                elif Factor==-1.0:
                    ofile.write('        call '+subroutine_name+'(unsorted,sorted,\n')
                    ofile.write('     &                dim1,dim2,dim3,dim4)\n')
                else:
                    ofile.write('        factor = '+str(Factor)+'\n')
                    ofile.write('        do r = 1,20\n')
                    ofile.write('          call '+subroutine_name+'(unsorted,sorted,\n')
                    ofile.write('     &                  dim1,dim2,dim3,dim4,factor)\n')
                    ofile.write('        enddo\n')
                ofile.write('        t1 = wtime() \n')
                ofile.write('!        print*,\''+subroutine_name+': t0,t1,dt = \',t0,t1,(t1-t0) \n')
                ofile.write('        call compare_1d_array(dim1*dim2*dim3*dim4,\n')
                ofile.write('     &                        sorted,reference,errors) \n')
                ofile.write('        if (errors.eq.0) then\n')
                ofile.write('          dt(loop,fac,omp) = (t1-t0)\n')
                ofile.write('!          print*,\'dt           = \',dt(loop,fac,omp) \n')
                ofile.write('        else\n')
                ofile.write('          dt(loop,fac,omp) = 10000000.0\n')
                ofile.write('          print*,\'errors = \',errors \n')
                ofile.write('        endif\n')
    ofile.write('!*************************************************\n')
    ofile.write('! determine the best time and loop order for each of (fac,omp)\n')
    ofile.write('        write(6,2000) '+str(A)+','+str(B)+','+str(C)+','+str(D)+'\n')
    ofile.write('!        do omp = 1, 2\n')
    ofile.write('!          do fac = 1, 3\n')
    ofile.write('!            do loop = 1, 24\n')
    ofile.write('!              print*,\'loop,fac,omp,dt = \',loop,fac,omp,dt(loop,fac,omp) \n')
    ofile.write('!            enddo\n')
    ofile.write('!          enddo\n')
    ofile.write('!        enddo\n')
    ofile.write('        do omp = 1, 2\n')
    ofile.write('          do fac = 1, 3\n')
    ofile.write('            besttime(fac,omp) = 1000000.0\n')
    ofile.write('            do loop = 1, 24\n')
    ofile.write('              if ( dt(loop,fac,omp) .lt. besttime(fac,omp) ) then\n')
    ofile.write('                besttime(fac,omp) = dt(loop,fac,omp)\n')
    ofile.write('                bestloop(1,fac,omp) = loops(1,loop)\n')
    ofile.write('                bestloop(2,fac,omp) = loops(2,loop)\n')
    ofile.write('                bestloop(3,fac,omp) = loops(3,loop)\n')
    ofile.write('                bestloop(4,fac,omp) = loops(4,loop)\n')
    ofile.write('              endif\n')
    ofile.write('            enddo\n')
    ofile.write('            write(6,1000) \'best \',labels(omp,fac),\n')
    ofile.write('     &      bestloop(1,fac,omp),bestloop(2,fac,omp),\n')
    ofile.write('     &      bestloop(3,fac,omp),bestloop(4,fac,omp),\n')
    ofile.write('     &      besttime(fac,omp),dt0\n')
    ofile.write('          enddo\n')
    ofile.write('        enddo\n')
    ofile.write('        return\n')
    ofile.write(' 1000 format(1x,a8,a10,\' = \',4i1,f9.6,\' (\',f9.6,\')\')\n')
    ofile.write(' 2000 format(1x,\'transpose: \',4i1)\n')
    ofile.write('! 3000 format(1x,a30,f12.6)\n')
    ofile.write('! 4000 format(1x,a16,4f12.6)\n')
    ofile.write('        end\n')
    return


def generate_test_driver(Debug):
    oname = 'test_trans_all'
    cfile = open('src/'+oname+'.c','w')
    hfile = open('src/'+oname+'.h','w')
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
    cfile.write('    printf(\"dims = %d,%d,%d,%d \\n\", dim1, dim2, dim3, dim4);\n\n')
    cfile.write('    double * unsorted;\n')
    cfile.write('    double * sorted;\n')
    cfile.write('    double * reference;\n\n')
    cfile.write('    rc = posix_memalign((void**)&unsorted,  128, size*sizeof(double)); assert(rc==0 && unsorted!=NULL);\n')
    cfile.write('    rc = posix_memalign((void**)&sorted,    128, size*sizeof(double)); assert(rc==0 && sorted!=NULL);\n')
    cfile.write('    rc = posix_memalign((void**)&reference, 128, size*sizeof(double)); assert(rc==0 && reference!=NULL);\n\n')
    cfile.write('    /*********** begin testing **********/\n\n')
    for transpose_order in generate_permutation_list(Debug):
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
        test_name = 'trans_'+perm_to_string(transpose_order)
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


def generate_all_subroutines(Debug):
    generate_test_driver(Debug)
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
        makefile.write('FFLAGS  = -g -O0 -Wall -fopenmp -fno-underscoring \n\n')
    else:
        makefile.write('CFLAGS  = -O2 -fopenmp -std=c99  \n')
        makefile.write('FFLAGS  = -O2 -fopenmp -fnounderscore \n\n')
    makefile.write('FLIBS  = -lgfortran \n\n')

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
    makefile.write('all: test_trans_all.x  \n\n')
    makefile.write('%.x: %.o libspaghetty.a libtestutil.a \n')
    makefile.write('\t$(CC) $(CFLAGS) $< -L. -lspaghetty -ltestutil $(FLIBS) -o $@ \n\n')
    makefile.write('libspaghetty.a: $(OBJECTS) \n')
    makefile.write('\t$(AR) $(ARFLAGS) $@ $(OBJECTS) \n\n')
    makefile.write('libtestutil.a: $(TESTOBJ) \n')
    makefile.write('\t$(AR) $(ARFLAGS) $@ $(TESTOBJ) \n\n')
    makefile.write('%.o: %.f \n')
    makefile.write('\t$(FC) $(FFLAGS) -c $< -o $@ \n\n')
    makefile.write('%.o: %.c \n')
    makefile.write('\t$(CC) $(CFLAGS) -c $< -o $@ \n\n')
    makefile.write('clean: \n')
    makefile.write('\t$(RM) $(RMFLAGS) test_trans_all.o $(OBJECTS) $(TESTOBJ) \n\n')
    makefile.write('realclean: clean \n')
    makefile.write('\t$(RM) $(RMFLAGS) test_trans_all.x libspaghetty.a libtestutil.a \n\n')
    makefile.write('srcclean: realclean \n')
    makefile.write('\t$(RM) $(RMFLAGS) $(SOURCES) \n\n')
    makefile.close()
    return

Debug = True

generate_all_subroutines(Debug)
generate_makefile(Debug)
