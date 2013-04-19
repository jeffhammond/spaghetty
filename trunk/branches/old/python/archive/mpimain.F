#define ALL24
      program main

      implicit none

      include 'mpif.h'

      integer status;
      integer me, nprocs;
      double precision start_time, end_time, driver_time;

c     All MPI programs begin with this.
      call mpi_init(status)

c     Finding the identity of the local process.
      call mpi_comm_rank(MPI_COMM_WORLD,me,status)

c     How many processes are we using?
      call mpi_comm_size(MPI_COMM_WORLD,nprocs,status)

c     This is where you put the serial executable.
      if (me.eq.0) call transpose_1234_driver()
#ifdef ALL24
      if (me.eq.1) call transpose_1243_driver()
      if (me.eq.2) call transpose_1324_driver()
      if (me.eq.3) call transpose_1342_driver()
      if (me.eq.4) call transpose_1423_driver()
      if (me.eq.5) call transpose_1432_driver()
      if (me.eq.6) call transpose_2134_driver()
      if (me.eq.7) call transpose_2143_driver()
      if (me.eq.8) call transpose_2314_driver()
      if (me.eq.9) call transpose_2341_driver()
      if (me.eq.10) call transpose_2413_driver()
      if (me.eq.11) call transpose_2431_driver()
      if (me.eq.12) call transpose_3124_driver()
      if (me.eq.13) call transpose_3142_driver()
      if (me.eq.14) call transpose_3214_driver()
      if (me.eq.15) call transpose_3241_driver()
      if (me.eq.16) call transpose_3412_driver()
      if (me.eq.17) call transpose_3421_driver()
      if (me.eq.18) call transpose_4123_driver()
      if (me.eq.19) call transpose_4132_driver()
      if (me.eq.20) call transpose_4213_driver()
      if (me.eq.21) call transpose_4231_driver()
      if (me.eq.22) call transpose_4312_driver()
      if (me.eq.23) call transpose_4321_driver()
#endif

c     All MPI programs end with this. *
      call mpi_finalize(status)
      end
