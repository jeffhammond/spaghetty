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

void flush_cache(void)
{
    size_t n = 32*1024*1024/sizeof(double);

    double * tmp = (double *) malloc(n*sizeof(double));

    if (tmp==NULL)
#ifdef USE_MPI
        MPI_Abort(MPI_COMM_WORLD,1);
#else
        exit(1);
#endif

    for (size_t i=0; i<n; i++)
        tmp[i] = (double)i;

    free(tmp);

    return;
}
 
