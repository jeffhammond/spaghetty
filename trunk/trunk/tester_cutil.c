#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#ifdef USE_MPI
#include <mpi.h>
#endif

double wtime(void)
{
    double t = 0.0;
#if   defined(_OPENMP)
#warning Using OpenMP timer
    t = omp_get_wtime();
#elif defined(USE_MPI)
#warning Using MPI timer
    t = MPI_Wtime();
#else
#warning NO TIMER AVAILABLE!!!
#endif
    return t;
}

double wtime_(void)
{
    return wtime();
}

double wtime__(void)
{
    return wtime();
}
