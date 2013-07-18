      subroutine tce_sort_4(unsorted,sorted,a,b,c,d,i,j,k,l,factor)
      implicit none
      integer version
      integer a,b,c,d
      integer i,j,k,l
      double precision sorted(a*b*c*d)
      double precision unsorted(a*b*c*d)
      double precision factor
      version = 1000*i+100*j+10*k+l
      if (version.eq.1234) then
        call transpose_1234_loop_2134(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.1243) then
        call transpose_1243_loop_1243(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.1324) then
        call transpose_1324_loop_1234(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.1342) then
        call transpose_1342_loop_1342(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.1423) then
        call transpose_1423_loop_1423(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.1432) then
        call transpose_1432_loop_1342(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.2134) then
        call transpose_2134_loop_2134(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.2143) then
        call transpose_2143_loop_2143(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.2314) then
        call transpose_2314_loop_2134(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.2341) then
        call transpose_2341_loop_2341(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.2413) then
        call transpose_2413_loop_2413(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.2431) then
        call transpose_2431_loop_2341(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.3124) then
        call transpose_3124_loop_1234(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.3142) then
        call transpose_3142_loop_1342(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.3214) then
        call transpose_3214_loop_2134(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.3241) then
        call transpose_3241_loop_2341(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.3412) then
        call transpose_3412_loop_1342(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.3421) then
        call transpose_3421_loop_2341(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.4123) then
        call transpose_4123_loop_1423(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.4132) then
        call transpose_4132_loop_1342(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.4213) then
        call transpose_4213_loop_2413(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.4231) then
        call transpose_4231_loop_2341(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.4312) then
        call transpose_4312_loop_1342(unsorted,sorted,a,b,c,d,factor)
      elseif (version.eq.4321) then
        call transpose_4321_loop_2341(unsorted,sorted,a,b,c,d,factor)
      else
        print*,'something is wrong...'
      endif
      return
      end
