#include <stdlib.h>
#include <stdint.h>

#ifdef USE_OMP
#include <omp.h>
#endif

#ifdef USE_MPI
#include <mpi.h>
#endif

double wtime(void)
{
#if   defined(USE_OMP)
    return omp_get_wtime();
#elif defined(USE_MPI)
    return MPI_Wtime();
#else
#warning NO TIMER AVAILABLE!!!
    return 0.0;
#endif
}

void flush_cache(const int64_t * bytes)
{
    int64_t n = bytes/sizeof(double);

    double * tmp = (double) malloc(n*sizeof(double));

    if (tmp==NULL)
#ifdef USE_MPI
        MPI_Abort(MPI_COMM_WORLD,1);
#else
        exit(1);
#endif

    for (int i=0; i<n; i++)
        tmp[i] = (double)i;

    free(tmp);

    return;
}
 
