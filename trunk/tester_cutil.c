#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if defined(_OPENMP)
#  include <omp.h>
#elif defined(__llvm__)
   void f_wtime_impl(double * t);
#endif

#ifdef USE_MPI
#include <mpi.h>
#endif

double wtime_impl(void)
{
    double t = 0.0;
#if   defined(_OPENMP)
#warning Using OpenMP timer
    t = omp_get_wtime();
#elif defined(USE_MPI)
#warning Using MPI timer
    t = MPI_Wtime();
#elif defined(__llvm__)
    f_wtime_impl(&t);
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
  /* this can only be used for doubles... since the count needs to be converted to bytes */
  const size_t l = (size_t) *length * sizeof(double);
  //printf("length = %d; l = %zu \n", *length, l);
  memcpy(new,old,l);
  return;
}

void f_memcpy(void * restrict new, void * restrict old, int * length)
{
  f_memcpy_impl(new,old,length);
  return;
}

void f_memcpy_(void * restrict new, void * restrict old, int * length)
{
  f_memcpy_impl(new,old,length);
  return;
}

void f_memcpy__(void * restrict new, void * restrict old, int * length)
{
  f_memcpy_impl(new,old,length);
  return;
}

