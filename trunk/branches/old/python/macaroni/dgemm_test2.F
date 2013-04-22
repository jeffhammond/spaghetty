#define RANKA 3
#define RANKB 4
#define RANKC 5
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
      integer row_a,col_a,row_b,col_b,row_c,col_c
      double precision t_raw(RANKA*RANKB*RANKI*RANKJ)
      double precision v_raw(RANKA*RANKB*RANKC*RANKD)
      double precision r_dgemm(RANKC*RANKD*RANKI*RANKJ)
      double precision r_loops(RANKC*RANKD*RANKI*RANKJ)
      double precision a_raw(RANKA*RANKC)
      double precision b_raw(RANKC*RANKB)
      double precision c_dgemm(RANKA*RANKB)
      double precision c_loops(RANKA*RANKB)
c
      size_a = RANKA * RANKC
      size_b = RANKC * RANKB
      size_c = RANKA * RANKB
c
      row_a=RANKA
      col_a=RANKC
      row_b=RANKC
      col_b=RANKB
      row_c=RANKA
      col_c=RANKB
c
      call number_array(a_raw,size_a)
      call number_array(b_raw,size_b)
c      call print_matrix(a_raw,row_a,col_a)
c      call print_matrix(b_raw,row_b,col_b)
c
      call zero_array(c_dgemm,size_c)
      call zero_array(c_loops,size_c)
c
c     Test case=1 - works
c      write(6,2) "CASE 1"
c
c      call dgemm('N','N',row_a,col_b,col_a,1.0d0,
c     &           a_raw,row_a,b_raw,row_b,0.0d0,c_dgemm,row_c)
c
      call simple_dgemm(a_raw,b_raw,c_dgemm,
     &                  row_a,col_a,row_b,col_b,row_c,col_c,1)
c
      call loop_dgemm(a_raw,size_a,b_raw,size_b,c_loops,size_c,
     &                row_a,col_a,row_b,col_b,row_c,col_c,1)
c
c      call print_matrix(c_dgemm,row_c,col_c)
c      call print_matrix(c_loops,row_c,col_c)
c
      call compare_arrays(c_dgemm,c_loops,size_c,.false.)
c
c     Test case=2 - works
c      write(6,2) "CASE 2"
c
c      call dgemm('N','T',row_a,col_b,col_a,1.0d0,
c     &           a_raw,row_a,b_raw,col_b,0.0d0,c_dgemm,row_c)
c
      call simple_dgemm(a_raw,b_raw,c_dgemm,
     &                  row_a,col_a,col_b,row_b,row_c,col_c,2)
c
      call loop_dgemm(a_raw,size_a,b_raw,size_b,c_loops,size_c,
     &                row_a,col_a,col_b,row_b,row_c,col_c,2)
c
c      call print_matrix(c_dgemm,row_c,col_c)
c      call print_matrix(c_loops,row_c,col_c)
c
      call compare_arrays(c_dgemm,c_loops,size_c,.false.)
c
c     Test case=3 - works
c      write(6,2) "CASE 3"
c
c      call dgemm('T','N',row_a,col_b,col_a,1.0d0,
c     &           a_raw,col_a,b_raw,col_a,0.0d0,c_dgemm,row_c)
c
      call simple_dgemm(a_raw,b_raw,c_dgemm,
     &                  col_a,row_a,row_b,col_b,row_c,col_c,3)
c
      call loop_dgemm(a_raw,size_a,b_raw,size_b,c_loops,size_c,
     &                col_a,row_a,row_b,col_b,row_c,col_c,3)
c
c      call print_matrix(c_dgemm,row_c,col_c)
c      call print_matrix(c_loops,row_c,col_c)
c
      call compare_arrays(c_dgemm,c_loops,size_c,.false.)
c
c      call compare_arrays(c_dgemm,c_loops,size_c,.false.)
c
c     Test case=4 - works
c      write(6,2) "CASE 4"
c
c      call dgemm('T','T',row_a,col_b,col_a,1.0d0,
c     &           a_raw,col_a,b_raw,col_b,0.0d0,c_dgemm,row_a)
c
      call simple_dgemm(a_raw,b_raw,c_dgemm,
     &                  col_a,row_a,col_b,row_b,row_c,col_c,4)
c
      call loop_dgemm(a_raw,size_a,b_raw,size_b,c_loops,size_c,
     &                col_a,row_a,col_b,row_b,row_c,col_c,4)
c
c      call print_matrix(c_dgemm,row_c,col_c)
c      call print_matrix(c_loops,row_c,col_c)
c
c      call compare_arrays(c_dgemm,c_loops,size_c,.false.)
c
c      dim1=RANKI
c      dim2=RANKJ
c      dim3=RANKA
c      dim4=RANKB
c      dim5=RANKC ! common index
c      dim6=RANKD ! common index
c
c      write(6,1) 'dim1 = ',dim1
c      write(6,1) 'dim2 = ',dim2
c      write(6,1) 'dim3 = ',dim3
c      write(6,1) 'dim4 = ',dim4
c      write(6,1) 'dim5 = ',dim5
c      write(6,1) 'dim6 = ',dim6
c
c      size_t = RANKI * RANKJ * RANKA * RANKB
c      size_v = RANKA * RANKB * RANKC * RANKD
c      size_r = RANKI * RANKJ * RANKC * RANKD
c
c      write(6,1) 'size_t = ',size_t
c      write(6,1) 'size_v = ',size_v
c      write(6,1) 'size_r = ',size_r
c
c      call number_array(t_raw,size_t)
c      call fill_array(t_raw,size_t,1.0d0)
c      call print_array(t_raw,size_t)
c      call number_array(v_raw,size_v)
c      call fill_array(v_raw,size_v,1.0d0)
c      call print_array(v_raw,size_v)
c
c      call zero_array(r_dgemm,size_r)
c
c      call ccsd_t2_8(t_raw,size_t,v_raw,size_v,r_dgemm,size_r,
c     &               dim1,dim2,dim3,dim4,dim5,dim6)
c
c      call print_array(r_dgemm,size_r)
c
c      call number_array(t_raw,size_t)
c      call fill_array(t_raw,size_t,1.0d0)
c      call print_array(t_raw,size_t)
c      call number_array(v_raw,size_v)
c      call fill_array(v_raw,size_v,1.0d0)
c      call print_array(v_raw,size_v)
c
c      call zero_array(r_loops,size_r)
c
c      call loop_ccsd_t2_8(t_raw,size_t,v_raw,size_v,r_loops,size_r,
c     &                    dim1,dim2,dim3,dim4,dim5,dim6)
c
c      call print_array(r_loops,size_r)
c
c      call compare_arrays(r_dgemm,r_loops,size_r)
c
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

      subroutine loop_ccsd_t2_8(a_raw,size_a,b_raw,size_b,c_done,size_c,
     &                          dim1,dim2,dim3,dim4,dim5,dim6)
c
c     c(p3,p4,h1,h2) = Sum(p5,p6)  a(p5,p6,h1,h2) * b(p3,p4,p5,p6)
c
      implicit none
      integer dim1,dim2,dim3,dim4,dim5,dim6
      integer i1,i2,i3,i4,i5,i6
      integer a_o1,a_o2,a_o3,a_o4,a_o5,a_o6
      integer b_o1,b_o2,b_o3,b_o4,b_o5,b_o6
      integer c_o1,c_o2,c_o3,c_o4,c_o5,c_o6
      integer a_offset,b_offset,c_offset
      integer old_offset,new_offset
      integer size_a,size_b,size_c
      double precision a_raw(size_a),b_raw(size_b),c_done(size_c)
      double precision a_sort(size_a),b_sort(size_b),c_sort(size_c)
      integer dim_common,dima_sort,dima,dimb_sort,dimb,dimc


#ifdef AAA
      do i1 = 1, dim1
       do i2 = 1, dim2
        do i3 = 1, dim3
         do i4 = 1, dim4
          c_o1 = (i1-1)*dim2*dim3*dim4
          c_o2 = (i2-1)*dim3*dim4
          c_o3 = (i3-1)*dim4
          c_o4 = (i4-1)
          c_offset = c_o1+c_o2+c_o3+c_o4+1
          c_done(c_offset) = 0.0d0
          do i5 = 1, dim5
           do i6 = 1, dim6
            a_o5 = (i5-1)
            a_o6 = (i6-1)*dim5
            a_o1 = (i1-1)*dim5*dim6
            a_o2 = (i2-1)*dim5*dim6*dim1
            a_offset = a_o5+a_o6+a_o1+a_o2+1
            b_o3 = (i3-1)
            b_o4 = (i4-1)*dim3
            b_o5 = (i5-1)*dim3*dim4
            b_o6 = (i6-1)*dim3*dim4*dim5
            b_offset = b_o3+b_o4+b_o5+b_o6+1
            c_done(c_offset) = c_done(c_offset) +
     &                          a_raw(a_offset) * b_raw(b_offset)
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
#endif
c
      return
      end

      subroutine loop_dgemm(a_in,size_a,b_in,size_b,c_out,size_c,
     &                      row_a,col_a,row_b,col_b,row_c,col_c,case)
      implicit none
      integer i,j,k
      integer a_offset,b_offset,c_offset
      integer size_a,size_b,size_c
      integer row_a,col_a,row_b,col_b,row_c,col_c
      double precision a_in(size_a)
      double precision b_in(size_b)
      double precision c_out(size_c)
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

      subroutine simple_dgemm(a_in,b_in,c_out,
     &                        row_a,col_a,row_b,col_b,row_c,col_c,case)
      implicit none
      integer i,j,k
      integer row_a,col_a,row_b,col_b,row_c,col_c
      double precision a_in(row_a,col_a)
      double precision b_in(row_b,col_b)
      double precision c_out(row_c,col_c)
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
            c_out(i,j) = 0.0d0
            do k = 1,col_a   ! row_b
              c_out(i,j) = c_out(i,j) + a_in(i,k) * b_in(k,j)
            enddo
          enddo
        enddo
      elseif (case.eq.2) then
c
c     C(i,j) = A(i,k) * B(j,k)
c
        do i = 1, row_c      ! row_a
          do j = 1, col_c    ! row_b
            c_out(i,j) = 0.0d0
            do k = 1,col_a   ! col_b
              c_out(i,j) = c_out(i,j) + a_in(i,k) * b_in(j,k)
            enddo
          enddo
        enddo
      elseif (case.eq.3) then
c
c     C(i,j) = A(k,i) * B(k,j)
c
        do i = 1, row_c      ! row_a
          do j = 1, col_c    ! col_b
            c_out(i,j) = 0.0d0
            do k = 1,row_a   ! row_b
              c_out(i,j) = c_out(i,j) + a_in(k,i) * b_in(k,j)
            enddo
          enddo
        enddo
      elseif (case.eq.4) then
c
c     C(i,j) = A(k,i) * B(j,k)
c
        do i = 1, row_c      ! row_a
          do j = 1, col_c    ! col_b
            c_out(i,j) = 0.0d0
            do k = 1,row_a   ! col_b
              c_out(i,j) = c_out(i,j) + a_in(k,i) * b_in(j,k)
            enddo
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
   1  format(1x,'element ',i8,' is ',f20.8)
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
   1  format(1x,'element (',i4,',',i4,') is ',f20.8)
   2  format(1x,'the matrix has ',i3,' rows and ',i3,' columns')
   3  format(1x,'===================================')
      end