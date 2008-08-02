import fileinput
import string
import sys
import os
import commands

fortran_compiler = 'ifort'
fortran_opt_flags = '-O3 -mtune=core2 -msse3 -align -c'
fortran_link_flags = '-O0'
src_dir = '/home/jeff/code/spaghetty/trunk/python/fettucini/src/'
exe_dir = '/home/jeff/code/spaghetty/trunk/python/fettucini/exe/'
log_dir = '/home/jeff/code/spaghetty/trunk/python/fettucini/log/'

count = '100'
rank = '15'
ranks = [rank,rank,rank,rank,rank,rank]
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])*int(ranks[4])*int(ranks[5])
sizechar = str(size)

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

# FORTRAN SHORTCUTS

f5 = 5*' '
f8 = 8*' '
f9 = 9*' '
f10 = 10*' '
f11 = 11*' '
f12 = 12*' '
f13 = 13*' '
f14 = 14*' '
f15 = 15*' '

def generate_subroutine(inVec,outVec):
    inA=inVec[0]
    inB=inVec[1]
    inC=inVec[2]
    inD=inVec[3]
    inE=inVec[4]
    inF=inVec[5]
    outA=outVec[0]
    outB=outVec[1]
    outC=outVec[2]
    outD=outVec[3]
    outE=outVec[4]
    outF=outVec[5]
    SinA = str(inA+1)
    SinB = str(inB+1)
    SinC = str(inC+1)
    SinD = str(inD+1)
    SinE = str(inE+1)
    SinF = str(inF+1)    
    SoutA = str(outA+1)	
    SoutB = str(outB+1)
    SoutC = str(outC+1)
    SoutD = str(outD+1)
    SoutE = str(outE+1)
    SoutF = str(outF+1)    
    subroutine_name = 'transpose_in'+SinA+SinB+SinC+SinD+SinE+SinF+'_out'+SoutA+SoutB+SoutC+SoutD+SoutE+SoutF
    source_name = subroutine_name+'.F'
    source_file = open(source_name,'w')
    source_file.write(f8+'subroutine '+subroutine_name+'(unsorted,sorted,\n')
    source_file.write(f5+'&'+2*f8+'dim'+SinA+',dim'+SinB+',dim'+SinC+',dim'+SinD+',\n')
    source_file.write(f5+'&'+2*f8+'dim'+SinE+',dim'+SinF+',factor)\n')
    source_file.write(f8+'implicit none\n')
    source_file.write(f8+'integer dim'+SinA+',dim'+SinB+',dim'+SinC+',dim'+SinD+',dim'+SinE+',dim'+SinF+'\n')
    source_file.write(f8+'integer j'+SinA+',j'+SinB+',j'+SinC+',j'+SinD+',j'+SinE+',j'+SinF+'\n')
    source_file.write(f8+'double precision sorted(dim'+SinA+'*dim'+SinB+'*dim'+SinC+'*dim'+SinD+'*dim'+SinE+'*dim'+SinF+')\n')
    source_file.write(f8+'double precision unsorted(dim'+SinA+'*dim'+SinB+'*dim'+SinC+'*dim'+SinD+'*dim'+SinE+'*dim'+SinF+')\n')
    source_file.write(f8+'double precision factor\n')
    source_file.write(f8+'do j'+SoutA+' = 1,dim'+SoutA+'\n')
    source_file.write(f9+'do j'+SoutB+' = 1,dim'+SoutB+'\n')
    source_file.write(f10+'do j'+SoutC+' = 1,dim'+SoutC+'\n')
    source_file.write(f11+'do j'+SoutD+' = 1,dim'+SoutD+'\n')
    source_file.write(f12+'do j'+SoutE+' = 1,dim'+SoutE+'\n')
    source_file.write(f13+'do j'+SoutF+' = 1,dim'+SoutF+'\n')
    #source_file.write(f14+'print*,"ijklmn=",j'+SinA+',j'+SinB+',j'+SinC+',j'+SinD+',j'+SinE+',j'+SinF+'\n')        
    source_file.write(f14+'sorted('+'j'+SinF+'+dim'+SinF+'*('+'j'+SinE+'-1+dim'+SinE+'*\n')
    source_file.write(f5+'&'+f10+'('+'j'+SinD+'-1+dim'+SinD+'*('+'j'+SinC+'-1+dim'+SinC+'*\n')
    source_file.write(f5+'&'+f10+'('+'j'+SinB+'-1+dim'+SinB+'*('+'j'+SinA+'-1)))))) = factor*\n')
    source_file.write(f5+'&'+f10+'unsorted('+'j'+SoutF+'+dim'+SoutF+'*('+'j'+SoutE+'-1+dim'+SoutE+'*\n')
    source_file.write(f5+'&'+f10+'('+'j'+SoutD+'-1+dim'+SoutD+'*('+'j'+SoutC+'-1+dim'+SoutC+'*\n')
    source_file.write(f5+'&'+f10+'('+'j'+SoutB+'-1+dim'+SoutB+'*('+'j'+SoutA+'-1))))))\n')
    source_file.write(f13+'enddo\n')
    source_file.write(f12+'enddo\n')
    source_file.write(f11+'enddo\n')
    source_file.write(f10+'enddo\n')
    source_file.write(f9+'enddo\n')
    source_file.write(f8+'enddo\n')
    source_file.write(f8+'return\n')
    source_file.write(f8+'end\n')
    source_file.close()
    print fortran_compiler+' '+fortran_opt_flags+' '+source_name
    os.system(fortran_compiler+' '+fortran_opt_flags+' '+source_name)
    os.system('ar -r tce_sort_jeff.a '+subroutine_name+'.o')
    os.system('mv '+subroutine_name+'.F '+src_dir)
    os.system('rm '+subroutine_name+'.o')

def build_hirata():
    print fortran_compiler+' '+fortran_opt_flags+' tce_sort_hirata.F'
    os.system(fortran_compiler+' '+fortran_opt_flags+' tce_sort_hirata.F')
    os.system('ar -r tce_sort_jeff.a tce_sort_hirata.o')

def generate_driver(inVec,outVec):
    dummy = 0
    inA=str(inVec[0]+1)
    inB=str(inVec[1]+1)
    inC=str(inVec[2]+1)
    inD=str(inVec[3]+1)
    inE=str(inVec[4]+1)
    inF=str(inVec[5]+1)
    driver_name = 'transpose_'+inA+inB+inC+inD+inE+inF
    print driver_name
    source_name = driver_name+'_driver.F'
    outA=str(outVec[0]+1)
    outB=str(outVec[1]+1)
    outC=str(outVec[2]+1)
    outD=str(outVec[3]+1)
    outE=str(outVec[4]+1)
    outF=str(outVec[5]+1)    
    source_file = open(source_name,'w')
    source_file.write('        PROGRAM ARRAYTEST\n')
    source_file.write('        REAL*8 before('+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+','+ranks[0]+')\n')
    source_file.write('        REAL*8 after_jeff('+sizechar+')\n')
    source_file.write('        REAL*8 after_hirata('+sizechar+')\n')
    source_file.write('        REAL*8 factor\n')
    source_file.write('        REAL*8 Tstart,Tfinish,Thirata,Tjeff,Tspeedup\n')
    source_file.write('        INTEGER*4 i,j,k,l,m,n\n')
    source_file.write('        INTEGER*4 aSize(4)\n')
    source_file.write('        INTEGER*4 perm(4)\n')
    source_file.write('        aSize(1) = '+ranks[0]+'\n')
    source_file.write('        aSize(2) = '+ranks[1]+'\n')
    source_file.write('        aSize(3) = '+ranks[2]+'\n')
    source_file.write('        aSize(4) = '+ranks[3]+'\n')
    source_file.write('        aSize(5) = '+ranks[4]+'\n')
    source_file.write('        aSize(6) = '+ranks[5]+'\n')
    source_file.write('        perm(1) = '+inA+'\n')
    source_file.write('        perm(2) = '+inB+'\n')
    source_file.write('        perm(3) = '+inC+'\n')
    source_file.write('        perm(4) = '+inD+'\n')
    source_file.write('        perm(5) = '+inE+'\n')
    source_file.write('        perm(6) = '+inF+'\n')    
    source_file.write('        DO 70 i = 1, '+ranks[0]+'\n')
    source_file.write('         DO 65 j = 1, '+ranks[1]+'\n')
    source_file.write('          DO 60 k = 1, '+ranks[2]+'\n')
    source_file.write('           DO 55 l = 1, '+ranks[3]+'\n')
    source_file.write('            DO 50 m = 1, '+ranks[4]+'\n')
    source_file.write('             DO 45 n = 1, '+ranks[5]+'\n')    
    source_file.write('                before(i,j,k,l,m,n) = n + m*10 + l*100 + k*1000\n')
    source_file.write('     &                          + j*10000 + i*100000\n')
    source_file.write('45           CONTINUE\n')
    source_file.write('50          CONTINUE\n')    
    source_file.write('55         CONTINUE\n')
    source_file.write('60        CONTINUE\n')
    source_file.write('65       CONTINUE\n')
    source_file.write('70      CONTINUE\n')
    source_file.write('        factor = 1.0\n')
    source_file.write('        Tstart=0.0\n')
    source_file.write('        Tfinish=0.0\n')
    source_file.write('        CALL CPU_TIME(Tstart)\n')
    #source_file.write('        Tstart=rtc()\n')
    source_file.write('        DO 30 i = 1, '+count+'\n')
    source_file.write('          CALL tce_sort_6(before, after_hirata,\n')
    source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
    source_file.write('     &                    aSize(5), aSize(6),\n')
    source_file.write('     &                    perm(1), perm(2), perm(3), perm(4),\n')
    source_file.write('     &                    perm(5), perm(6), factor)\n')
    source_file.write('30      CONTINUE\n')
    source_file.write('        CALL CPU_TIME(Tfinish)\n')
    #source_file.write('        Tfinish=rtc()\n')
    source_file.write('        Thirata=(Tfinish-Tstart)\n')
    source_file.write('        PRINT*,"TESTING TRANPOSE TYPE '+inA+inB+inC+inD+inE+inF+'"\n')
    source_file.write('        PRINT*,"Hirata Reference = ",Thirata,"seconds"\n')
    source_file.write('        PRINT*,"Algorithm         Jeff           "\n')
    for loop_order in [outVec]:
        dummy = dummy+1
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        e = loop_order[4]
        f = loop_order[5]
        subroutine_name = 'transpose_in'+inA+inB+inC+inD+inE+inF+'_out'+outA+outB+outC+outD+outE+outF
        source_file.write('        Tstart=0.0\n')
        source_file.write('        Tfinish=0.0\n')
        source_file.write('        CALL CPU_TIME(Tstart)\n')
        #source_file.write('        Tstart=rtc()\n')
        source_file.write('        DO '+str(100+dummy)+' i = 1, '+count+'\n')
        source_file.write('          CALL '+subroutine_name+'(before, after_jeff,\n')
        source_file.write('     &                    aSize(1), aSize(2), aSize(3), aSize(4),\n')
        source_file.write('     &                    aSize(5), aSize(6), factor)\n')
        source_file.write(str(100+dummy)+'     CONTINUE\n')
        source_file.write('        CALL CPU_TIME(Tfinish)\n')
        #source_file.write('        Tfinish=rtc()\n')
        source_file.write('        Tjeff=(Tfinish-Tstart)\n')
        source_file.write('        Tspeedup=Thirata/Tjeff\n')
        source_file.write('        PRINT*,"Loop '+outA+outB+outC+outD+outE+outF+'     ",Tjeff,Tspeedup\n')
        source_file.write('        DO '+str(500+dummy)+' i = 1, '+sizechar+'\n')
        source_file.write('          IF (after_jeff(i).ne.after_hirata(i)) THEN\n')
        source_file.write('            PRINT*,"error at position ",i,after_jeff(i),after_hirata(i)\n')
        source_file.write('          ENDIF\n')
        source_file.write(str(500+dummy)+'     CONTINUE\n')
        source_file.write('        STOP\n')
        source_file.write('      END\n')
        source_file.close()
        
    print fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' tce_sort_jeff.a '+' -o '+exe_dir+driver_name+'.x'
    os.system(fortran_compiler+' '+fortran_link_flags+' '+' '+source_name+' tce_sort_jeff.a '+' -o '+exe_dir+driver_name+'.x')
    os.system('mv '+source_name+' '+src_dir)


build_hirata()
generate_subroutine([1,0,2,3,4,5],[0,1,2,3,4,5]) 
generate_driver([1,0,2,3,4,5],[0,1,2,3,4,5])
