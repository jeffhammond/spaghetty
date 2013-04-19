c
      logical function glass_correct(a,b,c,d)
c
      implicit none
      integer a,c,b,d;
      logical part1,part2;
c
      if ( (a.gt.b).and.(c.gt.d)) then
        part1 = .true.
      elseif ( (a.lt.b).and.(c.lt.d)) then
        part1 = .true.
      else
        part1 = .false.
      endif
c
      if ( (a.gt.c).and.(b.gt.d)) then
        part2 = .true.
      elseif ( (a.lt.c).and.(b.lt.d)) then
        part2 = .true.
      else
        part2 = .false.
      endif
c
      glass_correct=(part1.and.part2)
      end
