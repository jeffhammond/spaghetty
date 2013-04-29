#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#ifdef USE_MPI
#include <mpi.h>
#endif

static inline double wtime_impl(void)
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

double wtime(void)
{
    return wtime_impl();
}

double wtime_(void)
{
    return wtime_impl();
}

double wtime__(void)
{
    return wtime_impl();
}

/* memcpy(void *restrict s1, const void *restrict s2, size_t n); */

/* Fortran does not respect const but requires no aliasing... */
static inline void f_memcpy_impl(void * restrict new, void * restrict old, int * length)
{
  const size_t l = (size_t) *length;
  memcpy(new,old,l);
  return;
}

void f_memcpy(void * restrict new, void * restrict old, int * length)
{
  return f_memcpy_impl(new,old,length);
}

void f_memcpy_(void * restrict new, void * restrict old, int * length)
{
  return f_memcpy_impl(new,old,length);
}

void f_memcpy__(void * restrict new, void * restrict old, int * length)
{
  return f_memcpy_impl(new,old,length);
}

