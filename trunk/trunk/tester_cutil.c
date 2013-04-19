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
#if   defined(_OPENMP)
    return omp_get_wtime();
#elif defined(USE_MPI)
    return MPI_Wtime();
#else
#warning NO TIMER AVAILABLE!!!
    return 0.0;
#endif
}

double wtime_(void)
{
    return wtime();
}

double wtime__(void)
{
    return wtime();
}
