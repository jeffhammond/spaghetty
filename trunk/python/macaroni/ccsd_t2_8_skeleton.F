#define RANKA 4
#define RANKB 4
#define RANKC 4
#define RANKD 4
#define RANKI 4
#define RANKJ 4
c
      program run_ccsd_t2_8
c
      implicit none
      integer dim1,dim2,dim3,dim4,dim5,dim6
      integer size_t,size_v,size_r

      integer size_a,size_b,size_c
      integer dim_common,dima_sort,dima,dimb_sort,dimb,dimc

      double precision a_raw(RANKA*RANKB*RANKI*RANKJ)
      double precision a_sort(RANKA*RANKB*RANKI*RANKJ)
      double precision b_raw(RANKA*RANKB*RANKC*RANKD)
      double precision b_sort(RANKA*RANKB*RANKC*RANKD)
      double precision c_sort(RANKC*RANKD*RANKI*RANKJ)
      double precision c_done(RANKC*RANKD*RANKI*RANKJ)

      integer row_a,col_a,row_b,col_b,row_c,col_c

      double precision t_raw(RANKA*RANKB*RANKI*RANKJ)
      double precision t_sort(RANKA*RANKB*RANKI*RANKJ)
      double precision v_raw(RANKA*RANKB*RANKC*RANKD)
      double precision v_sort(RANKA*RANKB*RANKC*RANKD)
      double precision r_sort(RANKC*RANKD*RANKI*RANKJ)
      double precision r_done(RANKC*RANKD*RANKI*RANKJ)
      double precision r_tce(RANKC*RANKD*RANKI*RANKJ)
c
      dim1=RANKI
      dim2=RANKJ
      dim3=RANKA
      dim4=RANKB
      dim5=RANKC ! common index
      dim6=RANKD ! common index
c
!       write(6,1) 'dim1 = ',dim1
!       write(6,1) 'dim2 = ',dim2
!       write(6,1) 'dim3 = ',dim3
!       write(6,1) 'dim4 = ',dim4
!       write(6,1) 'dim5 = ',dim5
!       write(6,1) 'dim6 = ',dim6
c
      size_t = dim1 * dim2 * dim3 * dim4
      size_a = size_t ! dima_sort*dimb_sort
      size_v = dim3 * dim4 * dim5 * dim6
      size_b = size_v ! dimb_sort*dim_common
      size_r = dim1 * dim2 * dim5 * dim6
      size_c = size_r ! dima_sort*dim_common
c
!       write(6,1) 'size_t = ',size_t
!       write(6,1) 'size_v = ',size_v
!       write(6,1) 'size_r = ',size_r
c
      dima_sort = dim1*dim2
      dimb_sort = dim3*dim4
      dim_common = dim5*dim6
c
      call number_array(b_raw,size_b)

c      call print_4array(b_raw,dim3,dim4,dim5,dim6)
c      call print_matrix(b_raw,dim3*dim4,dim5*dim6)
c      call print_array(b_raw,size_b)

      call tce_sort_4(b_raw,b_sort,dim3,dim4,dim5,dim6,4,3,2,1,1.0d0)

c      call print_4array(b_sort,dim6,dim5,dim4,dim3)
c      call print_matrix(b_sort,dim5*dim6,dim3*dim4)
c      call print_array(b_sort,size_b)

      call number_array(v_raw,size_v)

      call transpose_4321_loop_1234(v_raw,v_sort,
     &                              dim3,dim4,dim5,dim6,1.0d0)

      call compare_arrays(b_sort,v_sort,size_v,.false.)

      call number_array(a_raw,size_a)
      call number_array(t_raw,size_t)

      call tce_sort_4(a_raw,a_sort,dim3,dim4,dim1,dim2,2,1,4,3,1.0d0)

      call transpose_2143_loop_1234(t_raw,t_sort,
     &                              dim3,dim4,dim1,dim2,1.0d0)

      call compare_arrays(a_sort,t_sort,size_t,.false.)

      call zero_array(c_sort,size_c)
      call zero_array(r_sort,size_r)

c      call dgemm('T','N',row_a,col_b,col_a,1.0d0,
c     &           a_raw,col_a,b_raw,col_a,0.0d0,c_dgemm,row_c)
c      call loop_dgemm(1.0d0,1.0d0,
c     &                a_raw,size_a,b_raw,size_b,c_loops,size_c,
c     &                col_a,row_a,row_b,col_b,row_c,col_c,3)

      row_a = dim1*dim2
      col_a = dim3*dim4
      row_b = dim3*dim4
      col_b = dim5*dim6
      row_c = dim1*dim2
      col_c = dim5*dim6

      call dgemm('T','N',row_a,col_b,col_a,1.0d0,
     &           a_sort,col_a,b_sort,col_a,0.0d0,c_sort,row_c)
      call loop_dgemm(1.0d0,1.0d0,
     &                t_sort,size_t,v_sort,size_v,r_sort,size_r,
     &                col_a,row_a,row_b,col_b,row_c,col_c,3)

      call compare_arrays(c_sort,r_sort,size_r,.false.)

      call tce_sort_4(c_sort,c_done,dim4,dim3,dim2,dim1,2,1,4,3,1.0d0)
      call transpose_2143_loop_1234(r_sort,r_done,
     &                              dim4,dim3,dim2,dim1,1.0d0)

      call compare_arrays(c_done,r_done,size_r,.false.)

      call ccsd_t2_8(t_raw,size_t,v_raw,size_v,r_tce,size_r,
     &               dim1,dim2,dim3,dim4,dim5,dim6)

      call compare_arrays(r_tce,c_done,size_r,.false.)

   1  format(1x,a8,i8)
   2  format(1x,a60)
      end

      subroutine ccsd_t2_8(a_raw,size_a,b_raw,size_b,c_done,size_c,
     &                     dim1,dim2,dim3,dim4,dim5,dim6)
c
c     i0(p3,p4,h1,h2) = Sum(p5,p6) v(p3,p4,p5,p6) * t(p5,p6,h1,h2)
c
      implicit none
      integer dim1,dim2,dim3,dim4,dim5,dim6
      integer size_a,size_b,size_c
      double precision a_raw(size_a),b_raw(size_b),c_done(size_c)
      double precision a_sort(size_a),b_sort(size_b),c_sort(size_c)
      integer dim_common,dima_sort,dima,dimb_sort,dimb,dimc
c
      dima_sort = dim1*dim2
      dimb_sort = dim3*dim4
      dim_common = dim5*dim6
      dima = dim1*dim2*dim5*dim6
      dimb = dim3*dim4*dim5*dim6
      dimc = dim1*dim2*dim3*dim4
c
      call dfill(dimc,0.0d0,c_sort,1)
      call tce_sort_4(a_raw,a_sort,dim5,dim6,dim1,dim2,4,3,2,1,1.0d0)
      call tce_sort_4(b_raw,b_sort,dim3,dim4,dim5,dim6,2,1,4,3,1.0d0)
      call dgemm('T','N',dima_sort,dimb_sort,dim_common,1.0d0,a_sort,
     &           dim_common,b_sort,dim_common,1.0d0,c_sort,dima_sort)
      call tce_sort_4(c_sort,c_done,dim4,dim3,dim2,dim1,2,1,4,3,1.0d0)
      return
      end

      subroutine test_ccsd_t2_8(a_raw,size_a,b_raw,size_b,c_done,size_c,
     &                          dim1,dim2,dim3,dim4,dim5,dim6)
c
c     i0(p3,p4,h1,h2) = Sum(p5,p6) v(p3,p4,p5,p6) * t(p5,p6,h1,h2)
c
      implicit none
      integer dim1,dim2,dim3,dim4,dim5,dim6
      integer size_a,size_b,size_c
      double precision a_raw(size_a),b_raw(size_b),c_done(size_c)
      double precision a_sort(size_a),b_sort(size_b),c_sort(size_c)
      integer dim_common,dima_sort,dima,dimb_sort,dimb,dimc
c
      dima_sort = dim1*dim2
      dimb_sort = dim3*dim4
      dim_common = dim5*dim6
      dima = dim1*dim2*dim5*dim6
      dimb = dim3*dim4*dim5*dim6
      dimc = dim1*dim2*dim3*dim4
c
      call dfill(dimc,0.0d0,c_sort,1)
!       call tce_sort_4(a_raw,a_sort,dim5,dim6,dim1,dim2,4,3,2,1,1.0d0)

!       call tce_sort_4(b_raw,b_sort,dim3,dim4,dim5,dim6,2,1,4,3,1.0d0)

!       call dgemm('T','N',dima_sort,dimb_sort,dim_common,1.0d0,a_sort,
!      &           dim_common,b_sort,dim_common,1.0d0,c_sort,dima_sort)

!       call tce_sort_4(c_sort,c_done,dim4,dim3,dim2,dim1,2,1,4,3,1.0d0)

      return
      end

      subroutine loop_dgemm(alpha,beta,
     &                      a_in,size_a,b_in,size_b,c_out,size_c,
     &                      row_a,col_a,row_b,col_b,row_c,col_c,case)
      implicit none
      integer i,j,k
      integer a_offset,b_offset,c_offset
      integer size_a,size_b,size_c
      integer row_a,col_a,row_b,col_b,row_c,col_c
      double precision a_in(size_a)
      double precision b_in(size_b)
      double precision c_out(size_c)
      double precision alpha,beta,temp
      integer case
c
c     case = 1 C += A*B   ---- 'N','N'
c     case = 2 C += A*B'  ---- 'N','T'
c     case = 3 C += A'*B  ---- 'T','N'
c     case = 4 C += A'*B' ---- 'T','T'
c
      if (case.eq.1) then
c
c     C(i,j) = A(i,k) * B(k,j)
c
        if (row_a.ne.row_c) print*,'moron'
        if (col_b.ne.col_c) print*,'moron'
        if (col_a.ne.row_b) print*,'moron'
        do i = 1, row_c      ! row_a
          do j = 1, col_c    ! col_b
            c_offset = i+(j-1)*row_c
            c_out(c_offset) = 0.0d0
            do k = 1, col_a  ! row_b
              a_offset = i+(k-1)*row_a
              b_offset = k+(j-1)*row_b
              c_out(c_offset) = c_out(c_offset) +
     &                          a_in(a_offset) * b_in(b_offset)
            enddo
          enddo
        enddo
      elseif (case.eq.2) then
c
c     C(i,j) = A(i,k) * B(j,k)
c
        if (row_a.ne.row_c) print*,'moron'
        if (row_b.ne.col_c) print*,'moron'
        if (col_a.ne.col_b) print*,'moron'
        do i = 1, row_c
          do j = 1, col_c
            c_offset = i+(j-1)*row_c
            c_out(c_offset) = 0.0d0
            do k = 1, col_a
              a_offset = i+(k-1)*row_a
              b_offset = j+(k-1)*row_b
              c_out(c_offset) = c_out(c_offset) +
     &                          a_in(a_offset) * b_in(b_offset)
            enddo
          enddo
        enddo
      elseif (case.eq.3) then
c
c     C(i,j) = A(k,i) * B(k,j)
c
        if (col_a.ne.row_c) print*,'moron'
        if (col_b.ne.col_c) print*,'moron'
        if (row_a.ne.row_b) print*,'moron'
        do i = 1, row_c
          do j = 1, col_c
            c_offset = i+(j-1)*row_c
            c_out(c_offset) = 0.0d0
            do k = 1, row_a
              a_offset = k+(i-1)*row_a
              b_offset = k+(j-1)*row_b
              c_out(c_offset) = c_out(c_offset) +
     &                          a_in(a_offset) * b_in(b_offset)
            enddo
          enddo
        enddo
      elseif (case.eq.4) then
c
c     C(i,j) = A(k,i) * B(j,k)
c
        if (row_c.ne.col_a) print*,'moron'
        if (col_c.ne.row_b) print*,'moron'
        if (row_a.ne.col_b) print*,'moron'
        do i = 1, row_c
          do j = 1, col_c
            c_offset = i+(j-1)*row_c
            c_out(c_offset) = 0.0d0
            do k = 1, row_a
              a_offset = k+(i-1)*row_a
              b_offset = j+(k-1)*row_b
              c_out(c_offset) = c_out(c_offset) +
     &                          a_in(a_offset) * b_in(b_offset)
            enddo
          enddo
        enddo
      endif
c
      return
      end

      subroutine simple_dgemm(alpha,beta,a_in,b_in,c_out,
     &                        row_a,col_a,row_b,col_b,row_c,col_c,case)
      implicit none
      integer i,j,k
      integer row_a,col_a,row_b,col_b,row_c,col_c
      double precision a_in(row_a,col_a)
      double precision b_in(row_b,col_b)
      double precision c_out(row_c,col_c)
      double precision alpha,beta,temp
      integer case
c
c     case = 1 C += A*B   ---- 'N','N'
c     case = 2 C += A*B'  ---- 'N','T'
c     case = 3 C += A'*B  ---- 'T','N'
c     case = 4 C += A'*B' ---- 'T','T'
c
      if (case.eq.1) then
c
c     C(i,j) = A(i,k) * B(k,j)
c
        do i = 1, row_c      ! row_a
          do j = 1, col_c    ! col_b
            temp = beta*c_out(i,j)
            do k = 1,col_a   ! row_b
              temp = temp + a_in(i,k) * b_in(k,j)
            enddo
            c_out(i,j) = temp
          enddo
        enddo
      elseif (case.eq.2) then
c
c     C(i,j) = A(i,k) * B(j,k)
c
        do i = 1, row_c      ! row_a
          do j = 1, col_c    ! row_b
            temp = beta*c_out(i,j)
            do k = 1,col_a   ! col_b
              temp = temp + a_in(i,k) * b_in(j,k)
            enddo
            c_out(i,j) = temp
          enddo
        enddo
      elseif (case.eq.3) then
c
c     C(i,j) = A(k,i) * B(k,j)
c
        do i = 1, row_c      ! row_a
          do j = 1, col_c    ! col_b
            temp = beta*c_out(i,j)
            do k = 1,row_a   ! row_b
              temp = temp + a_in(k,i) * b_in(k,j)
            enddo
            c_out(i,j) = temp
          enddo
        enddo
      elseif (case.eq.4) then
c
c     C(i,j) = A(k,i) * B(j,k)
c
        do i = 1, row_c      ! row_a
          do j = 1, col_c    ! col_b
            temp = beta*c_out(i,j)
            do k = 1,row_a   ! col_b
              temp = temp + a_in(k,i) * b_in(j,k)
            enddo
            c_out(i,j) = temp
          enddo
        enddo
      endif
c
      return
      end


      subroutine compare_arrays(array1,array2,size,always)
      implicit none
      integer i,size
      double precision array1(size),array2(size)
      double precision value
      logical always
c
      do i = 1, size
        if ((array1(i).ne.array2(i)).or.always) then
        write(6,1) i,array1(i),array2(i)
        endif
      enddo
   1  format(1x,'element ',i8,' is ',f20.8,f20.8)
      end

      subroutine print_array(array,size)
      implicit none
      integer i,size
      double precision array(size)
c
      do i = 1, size
        write(6,1) i,array(i)
      enddo
   1  format(1x,'array ',i8,' is ',f20.8)
      end

      subroutine zero_array(array,size)
      implicit none
      integer i,size
      double precision array(size)
c
      do i = 1, size
        array(i) = 0.0d0
      enddo
      end

      subroutine fill_array(array,size,value)
      implicit none
      integer i,size
      double precision array(size)
      double precision value
c
      do i = 1, size
        array(i) = value
      enddo
      end

      subroutine number_array(array,size)
      implicit none
      integer i,size
      double precision array(size)
c
      do i = 1, size
        array(i) = 1.0d0*i
      enddo
      end

      subroutine rand_array(array,size)
      implicit none
      integer i,size
      double precision array(size)
c
      integer iseed
      double precision linux_rand
      external linux_rand
c
      iseed = 99
c
      if(iseed.gt.0) call linux_sran(iseed)
      do i = 1, size
        array(i) = linux_rand()
      enddo
      end

      subroutine print_matrix(matrix,row,col)
      implicit none
      integer i,j,row,col
      double precision matrix(row,col)
c
      write(6,2) row,col
      write(6,3)
      do j = 1, col
        do i = 1, row
          write(6,1) i,j,matrix(i,j)
        enddo
      enddo
      write(6,3)
   1  format(1x,'matrix (',i4,',',i4,') is ',f20.8)
   2  format(1x,'the matrix has ',i3,' rows and ',i3,' columns')
   3  format(1x,'===================================')
      end

      subroutine print_4array(array,d1,d2,d3,d4)
      implicit none
      integer i1,i2,i3,i4
      integer d1,d2,d3,d4
      double precision array(d1,d2,d3,d4)
c
      write(6,2) d1,d2,d3,d4
      write(6,3)

      do i4 = 1, d4
        do i3 = 1, d3
          do i2 = 1, d2
            do i1 = 1, d1
              write(6,1) i1,i2,i3,i4,array(i1,i2,i3,i4)
            enddo
          enddo
        enddo
      enddo
      write(6,3)
   1  format(1x,'array (',i4,',',i4,',',i4,',',i4,') is ',f20.8)
   2  format(1x,'dimensions = ',4i4)
   3  format(1x,'===================================')
      end

      subroutine transpose_2143_loop_1234(unsorted,sorted,
     &                                    dim1,dim2,dim3,dim4,factor)
      implicit none
      integer dim1,dim2,dim3,dim4
      integer old_offset,new_offset
      integer j1,j2,j3,j4
      double precision sorted(dim1*dim2*dim3*dim4)
      double precision unsorted(dim1*dim2*dim3*dim4)
      double precision factor
      do j1 = 1,dim1
       do j2 = 1,dim2
        do j3 = 1,dim3
         do j4 = 1,dim4
          old_offset = j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1)))
          new_offset = j3+dim3*(j4-1+dim4*(j1-1+dim1*(j2-1)))
          sorted(new_offset) = unsorted(old_offset) * factor
         enddo
        enddo
       enddo
      enddo
      return
      end

      subroutine transpose_4321_loop_1234(unsorted,sorted,
     &                                    dim1,dim2,dim3,dim4,factor)
      implicit none
      integer dim1,dim2,dim3,dim4
      integer old_offset,new_offset
      integer j1,j2,j3,j4
      double precision sorted(dim1*dim2*dim3*dim4)
      double precision unsorted(dim1*dim2*dim3*dim4)
      double precision factor
      do j1 = 1,dim1
       do j2 = 1,dim2
        do j3 = 1,dim3
         do j4 = 1,dim4
          old_offset = j4+dim4*(j3-1+dim3*(j2-1+dim2*(j1-1)))
          new_offset = j1+dim1*(j2-1+dim2*(j3-1+dim3*(j4-1)))
          sorted(new_offset) = unsorted(old_offset) * factor
         enddo
        enddo
       enddo
      enddo
      return
      end
