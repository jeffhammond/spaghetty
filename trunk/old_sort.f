      subroutine old_sort_0(x,y,s)
      implicit none
      double precision y
      double precision x
      double precision s
      y = x * s
      return
      end

      subroutine old_sort_2(x,y,a,b,i,j,s)
      implicit none
      integer a,b
      integer i,j
      integer id(2),jd(2),ia,ib,j1,j2
      double precision y(a*b)
      double precision x(a*b)
      double precision s
      ia = 0
      jd(1) = a
      jd(2) = b
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        ia = ia + 1
        ib = id(j)+jd(j)*(id(i)-1)
        y(ib) = x(ia) * s
       enddo
      enddo
      return
      end

      subroutine old_sort_4(x,y,a,b,c,d,i,j,k,l,s)
      implicit none
      integer a,b,c,d
      integer i,j,k,l
      integer id(4),jd(4),ia,ib,j1,j2,j3,j4
      double precision y(a*b*c*d)
      double precision x(a*b*c*d)
      double precision s
      jd(1) = a
      jd(2) = b
      jd(3) = c
      jd(4) = d
      if ((l.eq.4).or.(l.eq.3)) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          ia = id(4)+jd(4)*(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))
          ib = id(l)+jd(l)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          y(ib) = x(ia) * s
         enddo
        enddo
       enddo
      enddo
      else if (l.eq.2) then
      do j1 = 1,a
       id(1) = j1
       do j3 = 1,c
        id(3) = j3
        do j2 = 1,b
         id(2) = j2
         do j4 = 1,d
          id(4) = j4
          ia = id(4)+jd(4)*(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))
          ib = id(l)+jd(l)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          y(ib) = x(ia) * s
         enddo
        enddo
       enddo
      enddo
      else ! if (l.eq.1) then
      do j2 = 1,b
       id(2) = j2
       do j3 = 1,c
        id(3) = j3
        do j1 = 1,a
         id(1) = j1
         do j4 = 1,d
          id(4) = j4
          ia = id(4)+jd(4)*(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))
          ib = id(l)+jd(l)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          y(ib) = x(ia) * s
         enddo
        enddo
       enddo
      enddo
      endif
      return
      end

      subroutine old_sort_6(x,y,a,b,c,d,e,f,i,j,k,l,m,n,s)
      implicit none
      integer a,b,c,d,e,f
      integer i,j,k,l,m,n
      integer id(6),jd(6),ia,ib,j1,j2,j3,j4,j5,j6
      double precision y(a*b*c*d*e*f)
      double precision x(a*b*c*d*e*f)
      double precision s
      ia = 0
      jd(1) = a
      jd(2) = b
      jd(3) = c
      jd(4) = d
      jd(5) = e
      jd(6) = f
      if ((n.eq.6).or.(n.eq.5)) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          do j5 = 1,e
           id(5) = j5
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.4) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j5 = 1,e
          id(5) = j5
          do j4 = 1,d
           id(4) = j4
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.3) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j3 = 1,c
           id(3) = j3
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.2) then
      do j1 = 1,a
       id(1) = j1
       do j3 = 1,c
        id(3) = j3
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j2 = 1,b
           id(2) = j2
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else ! if (n.eq.1) then
      do j2 = 1,b
       id(2) = j2
       do j3 = 1,c
        id(3) = j3
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j1 = 1,a
           id(1) = j1
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      endif
      return
      end

      subroutine old_sort_8(x,y,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,s)
      implicit none
      integer a,b,c,d,e,f,g,h
      integer i,j,k,l,m,n,o,p
      integer id(8),jd(8),ia,ib,j1,j2,j3,j4,j5,j6,j7,j8
      double precision y(a*b*c*d*e*f*g*h)
      double precision x(a*b*c*d*e*f*g*h)
      double precision s
      jd(1) = a
      jd(2) = b
      jd(3) = c
      jd(4) = d
      jd(5) = e
      jd(6) = f
      jd(7) = g
      jd(8) = h
      if ((p.eq.8).or.(p.eq.7)) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          do j5 = 1,e
           id(5) = j5
           do j6 = 1,f
            id(6) = j6
            do j7 = 1,g
             id(7) = j7
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.6) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          do j5 = 1,e
           id(5) = j5
           do j7 = 1,g
            id(7) = j7
            do j6 = 1,f
             id(6) = j6
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.5) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j5 = 1,e
             id(5) = j5
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.4) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j5 = 1,e
          id(5) = j5
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j4 = 1,d
             id(4) = j4
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.3) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j3 = 1,c
             id(3) = j3
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.2) then
      do j1 = 1,a
       id(1) = j1
       do j3 = 1,c
        id(3) = j3
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j2 = 1,b
             id(2) = j2
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else ! if (p.eq.1) then
      do j2 = 1,b
       id(2) = j2
       do j3 = 1,c
        id(3) = j3
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j1 = 1,a
             id(1) = j1
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      endif
      return
      end

      subroutine old_sortacc_0(x,y,s)
      implicit none
      double precision y
      double precision x
      double precision s
      y = y + x * s
      return
      end

      subroutine old_sortacc_2(x,y,a,b,i,j,s)
      implicit none
      integer a,b
      integer i,j
      integer id(2),jd(2),ia,ib,j1,j2
      double precision y(a*b)
      double precision x(a*b)
      double precision s
      ia = 0
      jd(1) = a
      jd(2) = b
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        ia = ia + 1
        ib = id(j)+jd(j)*(id(i)-1)
        y(ib) = y(ib) + x(ia) * s
       enddo
      enddo
      return
      end

      subroutine old_sortacc_4(x,y,a,b,c,d,i,j,k,l,s)
      implicit none
      integer a,b,c,d
      integer i,j,k,l
      integer id(4),jd(4),ia,ib,j1,j2,j3,j4
      double precision y(a*b*c*d)
      double precision x(a*b*c*d)
      double precision s
      jd(1) = a
      jd(2) = b
      jd(3) = c
      jd(4) = d
      if ((l.eq.4).or.(l.eq.3)) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          ia = id(4)+jd(4)*(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))
          ib = id(l)+jd(l)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          y(ib) = y(ib) + x(ia) * s
         enddo
        enddo
       enddo
      enddo
      else if (l.eq.2) then
      do j1 = 1,a
       id(1) = j1
       do j3 = 1,c
        id(3) = j3
        do j2 = 1,b
         id(2) = j2
         do j4 = 1,d
          id(4) = j4
          ia = id(4)+jd(4)*(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))
          ib = id(l)+jd(l)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          y(ib) = y(ib) + x(ia) * s
         enddo
        enddo
       enddo
      enddo
      else
      do j2 = 1,b
       id(2) = j2
       do j3 = 1,c
        id(3) = j3
        do j1 = 1,a
         id(1) = j1
         do j4 = 1,d
          id(4) = j4
          ia = id(4)+jd(4)*(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))
          ib = id(l)+jd(l)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          y(ib) = y(ib) + x(ia) * s
         enddo
        enddo
       enddo
      enddo
      endif
      return
      end

      subroutine old_sortacc_6(x,y,a,b,c,d,e,f,i,j,k,l,m,n,s)
      implicit none
      integer a,b,c,d,e,f
      integer i,j,k,l,m,n
      integer id(6),jd(6),ia,ib,j1,j2,j3,j4,j5,j6
      double precision y(a*b*c*d*e*f)
      double precision x(a*b*c*d*e*f)
      double precision s
      ia = 0
      jd(1) = a
      jd(2) = b
      jd(3) = c
      jd(4) = d
      jd(5) = e
      jd(6) = f
      if ((n.eq.6).or.(n.eq.5)) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          do j5 = 1,e
           id(5) = j5
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = y(ib) + x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.4) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j5 = 1,e
          id(5) = j5
          do j4 = 1,d
           id(4) = j4
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = y(ib) + x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.3) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j3 = 1,c
           id(3) = j3
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = y(ib) + x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.2) then
      do j1 = 1,a
       id(1) = j1
       do j3 = 1,c
        id(3) = j3
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j2 = 1,b
           id(2) = j2
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = y(ib) + x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else
      do j2 = 1,b
       id(2) = j2
       do j3 = 1,c
        id(3) = j3
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j1 = 1,a
           id(1) = j1
           do j6 = 1,f
            id(6) = j6
            ia = id(6)+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     1         *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))
            ib = id(n)+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            y(ib) = y(ib) + x(ia) * s
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      endif
      return
      end

      subroutine old_sortacc_8(x,y,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,s)
      implicit none
      integer a,b,c,d,e,f,g,h
      integer i,j,k,l,m,n,o,p
      integer id(8),jd(8),ia,ib,j1,j2,j3,j4,j5,j6,j7,j8
      double precision y(a*b*c*d*e*f*g*h)
      double precision x(a*b*c*d*e*f*g*h)
      double precision s
      jd(1) = a
      jd(2) = b
      jd(3) = c
      jd(4) = d
      jd(5) = e
      jd(6) = f
      jd(7) = g
      jd(8) = h
      if ((p.eq.8).or.(p.eq.7)) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          do j5 = 1,e
           id(5) = j5
           do j6 = 1,f
            id(6) = j6
            do j7 = 1,g
             id(7) = j7
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = y(ib) + x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.6) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          do j5 = 1,e
           id(5) = j5
           do j7 = 1,g
            id(7) = j7
            do j6 = 1,f
             id(6) = j6
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = y(ib) + x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.5) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j4 = 1,d
          id(4) = j4
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j5 = 1,e
             id(5) = j5
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = y(ib) + x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.4) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j3 = 1,c
         id(3) = j3
         do j5 = 1,e
          id(5) = j5
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j4 = 1,d
             id(4) = j4
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = y(ib) + x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.3) then
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j3 = 1,c
             id(3) = j3
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = y(ib) + x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (p.eq.2) then
      do j1 = 1,a
       id(1) = j1
       do j3 = 1,c
        id(3) = j3
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j2 = 1,b
             id(2) = j2
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = y(ib) + x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else
      do j2 = 1,b
       id(2) = j2
       do j3 = 1,c
        id(3) = j3
        do j4 = 1,d
         id(4) = j4
         do j5 = 1,e
          id(5) = j5
          do j6 = 1,f
           id(6) = j6
           do j7 = 1,g
            id(7) = j7
            do j1 = 1,a
             id(1) = j1
             do j8 = 1,h
              id(8) = j8
              ia = id(8)+jd(8)*(id(7)-1+jd(7)
     1           *(id(6)-1+jd(6)*(id(5)-1+jd(5)*(id(4)-1+jd(4)
     2           *(id(3)-1+jd(3)*(id(2)-1+jd(2)*(id(1)-1)))))))
              ib = id(p)+jd(p)*(id(o)-1+jd(o)
     1           *(id(n)-1+jd(n)*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     2           *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))))
              y(ib) = y(ib) + x(ia) * s
             enddo
            enddo
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      endif
      return
      end
