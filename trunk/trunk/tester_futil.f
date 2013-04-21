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
!$omp parallel do collapse(2)
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

      subroutine init_4d_array(a,b,c,d,x)
      implicit none
      integer i,j,k,l, a,b,c,d
      double precision x(a,b,c,d)
!$omp parallel do collapse(4)
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
!$omp parallel do collapse(6)
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


