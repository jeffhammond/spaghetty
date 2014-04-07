      subroutine f_wtime_impl(t);
      implicit none
      double precision t
#if defined(_OPENMP)
      double precision omp_get_wtime
      external omp_get_wtime
      t = omp_get_wtime()
#else
! This is Fortran95
      call cpu_time(t)
#endif
      return
      end

      subroutine compare_1d_array(n,x,y,errors)
      implicit none
      integer i, n, errors
      double precision x(n), y(n)
      errors = 0
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n)
!$omp& shared(x)
!$omp& schedule(static)
!$omp& reduction(+:errors)
      do i=1,n
        if (x(i).ne.y(i)) then
!$omp atomic
          errors = errors + 1
        endif
      enddo
!$omp end parallel do
      return
      end

      subroutine zero_1d_array(n,x)
      implicit none
      integer i, n
      double precision x(n)
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n)
!$omp& shared(x)
!$omp& schedule(static)
      do i=1,n
       x(i)=0.0
      enddo
!$omp end parallel do
      return
      end

      subroutine scale_1d_array(n,x,val)
      implicit none
      integer i, n
      double precision x(n)
      double precision val
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n,val)
!$omp& shared(x)
!$omp& schedule(static)
      do i=1,n
       x(i)=x(i)*val
      enddo
!$omp end parallel do
      return
      end

      subroutine fill_1d_array(n,x,val)
      implicit none
      integer i, n
      double precision x(n)
      double precision val
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n,val)
!$omp& shared(x)
!$omp& schedule(static)
      do i=1,n
       x(i)=val
      enddo
!$omp end parallel do
      return
      end

      subroutine init_2d_array(a,b,x)
      implicit none
      integer i,j, a,b
      double precision x(a,b)
!$omp parallel do
!$omp& private(i,j)
!$omp& firstprivate(a,b)
!$omp& shared(x)
!$omp& schedule(static)
      do j=1,b
       do i=1,a
        x(i,j)=i+j*a
       enddo
      enddo
!$omp end parallel do
      return
      end

      subroutine print_4d_array(a,b,c,d,x)
      implicit none
      integer i,j,k,l, a,b,c,d
      double precision x(a,b,c,d)
      do l=1,d
       do k=1,c
        do j=1,b
         do i=1,a
          write(6,1) i,j,k,l,x(i,j,k,l)
         enddo
        enddo
       enddo
      enddo
      return
 1    format(1x,i2,1x,i2,1x,i2,1x,i2,1x,f12.1)
      end

      subroutine print_4d_arrays(a,b,c,d,x,y)
      implicit none
      integer i,j,k,l, a,b,c,d
      double precision x(a,b,c,d)
      double precision y(a,b,c,d)
      do l=1,d
       do k=1,c
        do j=1,b
         do i=1,a
          write(6,1) i,j,k,l,x(i,j,k,l),y(i,j,k,l)
         enddo
        enddo
       enddo
      enddo
      return
 1    format(1x,i2,1x,i2,1x,i2,1x,i2,1x,f12.1,1x,f12.1)
      end

      subroutine init_4d_array(a,b,c,d,x)
      implicit none
      integer i,j,k,l, a,b,c,d
      double precision x(a,b,c,d)
!$omp parallel do collapse(2)
!$omp& private(i,j,k,l)
!$omp& firstprivate(a,b,c,d)
!$omp& shared(x)
!$omp& schedule(static)
      do l=1,d
       do k=1,c
        do j=1,b
         do i=1,a
          x(i,j,k,l)=i+j*a+k*a*b+l*a*b*c
         enddo
        enddo
       enddo
      enddo
!$omp end parallel do
      return
      end

      subroutine init_6d_array(a,b,c,d,e,f,x)
      implicit none
      integer i,j,k,l,m,n, a,b,c,d,e,f
      double precision x(a,b,c,d,e,f)
!$omp parallel do collapse(3)
!$omp& private(i,j,k,l,m,n)
!$omp& firstprivate(a,b,c,d,e,f)
!$omp& shared(x)
!$omp& schedule(static)
      do n=1,f
       do m=1,e
        do l=1,d
         do k=1,c
          do j=1,b
           do i=1,a
            x(i,j,k,l,m,n)=i+j*a+k*a*b+l*a*b*c+m*a*b*c*d+n*a*b*c*d*e
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
!$omp end parallel do
      return
      end

      subroutine print_6d_array(a,b,c,d,e,f,x)
      implicit none
      integer i,j,k,l,m,n, a,b,c,d,e,f
      double precision x(a,b,c,d,e,f)
      do n=1,f
       do m=1,e
        do l=1,d
         do k=1,c
          do j=1,b
           do i=1,a
            write(6,1) i,j,k,l,m,n,x(i,j,k,l,m,n)
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      return
 1    format(1x,i2,1x,i2,1x,i2,1x,i2,1x,i2,1x,i2,1x,f12.1)
      end

      subroutine print_6d_arrays(a,b,c,d,e,f,x,y)
      implicit none
      integer i,j,k,l,m,n, a,b,c,d,e,f
      double precision x(a,b,c,d,e,f)
      double precision y(a,b,c,d,e,f)
      do n=1,f
       do m=1,e
        do l=1,d
         do k=1,c
          do j=1,b
           do i=1,a
            write(6,1) i,j,k,l,m,n,x(i,j,k,l,m,n),y(i,j,k,l,m,n)
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
 1    format(1x,i2,1x,i2,1x,i2,1x,i2,1x,i2,1x,i2,1x,f12.1,1x,f12.1)
      end

! this stuff is actually used by the spaghetty code, not just the tester

      subroutine c_1d_nomp(n,x,y)
      implicit none
      integer i, n
      double precision x(n), y(n)
!DEC$ UNROLL
      do i=1,n
        y(i) = x(i)
      enddo
      return
      end

      subroutine cs_1d_nomp(n,x,y,f)
      implicit none
      integer i, n
      double precision x(n), y(n), f
!DEC$ UNROLL
      do i=1,n
        y(i) = f * x(i)
      enddo
      return
      end

      subroutine a_1d_nomp(n,x,y)
      implicit none
      integer i, n
      double precision x(n), y(n)
!DEC$ UNROLL
      do i=1,n
        y(i) = y(i) + x(i)
      enddo
      return
      end

      subroutine as_1d_nomp(n,x,y,f)
      implicit none
      integer i, n
      double precision x(n), y(n), f
!DEC$ UNROLL
      do i=1,n
        y(i) = y(i) + f*x(i)
      enddo
      return
      end

      subroutine sas_1d_nomp(n,x,y,f,g)
      implicit none
      integer i, n
      double precision x(n), y(n), f, g
!DEC$ UNROLL
      do i=1,n
        y(i) = g*y(i) + f*x(i)
      enddo
      return
      end

      subroutine c_1d_omp(n,x,y)
      implicit none
      integer i, n
      double precision x(n), y(n)
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n)
!$omp& shared(x,y)
!$omp& schedule(static)
!DEC$ UNROLL
      do i=1,n
        y(i) = x(i)
      enddo
!$omp end parallel do
      return
      end

      subroutine cs_1d_omp(n,x,y,f)
      implicit none
      integer i, n
      double precision x(n), y(n), f
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n,f)
!$omp& shared(x,y)
!$omp& schedule(static)
!DEC$ UNROLL
      do i=1,n
        y(i) = f * x(i)
      enddo
!$omp end parallel do
      return
      end

      subroutine a_1d_omp(n,x,y)
      implicit none
      integer i, n
      double precision x(n), y(n)
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n)
!$omp& shared(x,y)
!$omp& schedule(static)
!DEC$ UNROLL
      do i=1,n
        y(i) = y(i) + x(i)
      enddo
!$omp end parallel do
      return
      end

      subroutine as_1d_omp(n,x,y,f)
      implicit none
      integer i, n
      double precision x(n), y(n), f
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n,f)
!$omp& shared(x,y)
!$omp& schedule(static)
!DEC$ UNROLL
      do i=1,n
        y(i) = y(i) + f*x(i)
      enddo
!$omp end parallel do
      return
      end

      subroutine sas_1d_omp(n,x,y,f,g)
      implicit none
      integer i, n
      double precision x(n), y(n), f, g
!$omp parallel do
!$omp& private(i)
!$omp& firstprivate(n,f,g)
!$omp& shared(x,y)
!$omp& schedule(static)
!DEC$ UNROLL
      do i=1,n
        y(i) = g*y(i) + f*x(i)
      enddo
!$omp end parallel do
      return
      end

