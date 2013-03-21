      subroutine zero_1d_array(n,x)
      implicit none
      integer i
      integer n
      double precision x(n)
      do i=1,n
       x(i)=0.0
      enddo 
      return
      end

      subroutine fill_1d_array(n,x,val)
      implicit none
      integer i
      integer n
      double precision x(n)
      double precision val
      do i=1,n
       x(i)=val
      enddo 
      return
      end

      subroutine init_2d_array(a,b,x)
      implicit none
      integer i,j
      integer a,b
      double precision x(a,b)
      do j=1,b
       do i=1,a
        x(i,j)=i+j*a
       enddo 
      enddo 
      return
      end

      subroutine init_4d_array(a,b,c,d,x)
      implicit none
      integer i,j,k,l
      integer a,b,c,d
      double precision x(a,b,c,d)
      do l=1,d
       do k=1,c
        do j=1,b
         do i=1,a
          x(i,j,k,l)=i+j*a+k*a*b+l*a*b*c
         enddo 
        enddo 
       enddo 
      enddo 
      return
      end

      subroutine init_6d_array(a,b,c,d,e,f,x)
      implicit none
      integer i,j,k,l,m,n
      integer a,b,c,d,e,f
      double precision x(a,b,c,d,e,f)
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
      return
      end


