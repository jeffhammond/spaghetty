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
rank = '5'
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
    SinA = str(inA)
    SinB = str(inB)
    SinC = str(inC)
    SinD = str(inD)
    SinE = str(inE)
    SinF = str(inF)    
    SoutA = str(outA)	
    SoutB = str(outB)
    SoutC = str(outC)
    SoutD = str(outD)
    SoutE = str(outE)
    SoutF = str(outF)    
    subroutine_name = 'transpose_in'+SinA+SinB+SinC+SinD+SinE+SinF+'_out'+SoutA+SoutB+SoutC+SoutD+SoutE+SoutF
    source_name = subroutine_name+'.F'
    source_file = open(source_name,'w')
    source_file.write(f8+'subroutine '+subroutine_name+'(old,new,\n')
    source_file.write(f5+'&'+2*f8+'d'+SinA+',d'+SinB+',d'+SinC+',d'+SinD+',d'+SinE+',d'+SinF+',factor)\n')
    source_file.write(f8+'implicit none\n')
    source_file.write(f8+'integer d'+SinA+',d'+SinB+',d'+SinC+',d'+SinD+',d'+SinE+',d'+SinF+'\n')
    source_file.write(f8+'integer i'+SinA+',i'+SinB+',i'+SinC+',i'+SinD+',i'+SinE+',i'+SinF+'\n')
    source_file.write(f8+'double precision new(d'+SinA+'*d'+SinB+'*d'+SinC+'*d'+SinD+'*d'+SinE+'*d'+SinF+')\n')
    source_file.write(f8+'double precision old(d'+SinA+'*d'+SinB+'*d'+SinC+'*d'+SinD+'*d'+SinE+'*d'+SinF+')\n')
    source_file.write(f8+'double precision factor\n')
    source_file.write(f8+'do i'+SoutA+' = 1,d'+SoutA+'\n')
    source_file.write(f9+'do i'+SoutB+' = 1,d'+SoutB+'\n')
    source_file.write(f10+'do i'+SoutC+' = 1,d'+SoutC+'\n')
    source_file.write(f11+'do i'+SoutD+' = 1,d'+SoutD+'\n')
    source_file.write(f12+'do i'+SoutE+' = 1,d'+SoutE+'\n')
    source_file.write(f13+'do i'+SoutF+' = 1,d'+SoutF+'\n')
    #source_file.write(f14+'print*,"ijklmn=",i'+SinA+',i'+SinB+',i'+SinC+',i'+SinD+',i'+SinE+',i'+SinF+'\n')        
    source_file.write(f14+'new(1+'+'i'+SinF+'-1+d'+SinF+'*('+'i'+SinE+'-1+d'+SinE+'*\n')
    source_file.write(f5+'&'+f10+'('+'i'+SinD+'-1+d'+SinD+'*('+'i'+SinC+'-1+d'+SinC+'*\n')
    source_file.write(f5+'&'+f10+'('+'i'+SinB+'-1+d'+SinB+'*('+'i'+SinA+'-1)))))) = factor*\n')
    source_file.write(f5+'&'+f10+'old(1+'+'i'+SoutF+'-1+d'+SoutF+'*('+'i'+SoutE+'-1+d'+SoutE+'*\n')
    source_file.write(f5+'&'+f10+'('+'i'+SoutD+'-1+d'+SoutD+'*('+'i'+SoutC+'-1+d'+SoutC+'*\n')
    source_file.write(f5+'&'+f10+'('+'i'+SoutB+'-1+d'+SoutB+'*('+'i'+SoutA+'-1))))))\n')
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
    os.system('rm tce_sort_hirata.o')

def generate_driver(inVec,outVec):
    dummy = 0
    inA=str(inVec[0])
    inB=str(inVec[1])
    inC=str(inVec[2])
    inD=str(inVec[3])
    inE=str(inVec[4])
    inF=str(inVec[5])
    driver_name = 'transpose_'+inA+inB+inC+inD+inE+inF
    print driver_name
    source_name = driver_name+'_driver.F'
    outA=str(outVec[0])
    outB=str(outVec[1])
    outC=str(outVec[2])
    outD=str(outVec[3])
    outE=str(outVec[4])
    outF=str(outVec[5])    
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

def build_subroutines_simple(all_permutations):
    for transpose_order in all_permutations:
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
        E = transpose_order[4]
        F = transpose_order[5]    
        generate_subroutine([A,B,C,D,E,F],[A,B,C,D,E,F]) 

def build_drivers_simple(all_permutations):
    for transpose_order in all_permutations:
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
        E = transpose_order[4]
        F = transpose_order[5]    
        generate_driver([A,B,C,D,E,F],[A,B,C,D,E,F])

def build_executables_simple(all_permutations):
    for transpose_order in all_permutations:
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
        E = transpose_order[4]
        F = transpose_order[5]    
        generate_subroutine([A,B,C,D,E,F],[A,B,C,D,E,F]) 
        generate_driver([A,B,C,D,E,F],[A,B,C,D,E,F])

def build_executables(all_permutations):
    for transpose_order in all_permutations:
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
        E = transpose_order[4]
        F = transpose_order[5]    
        for loop_order in all_permutations:
            loop_order = transpose_order
            a = loop_order[0]
            b = loop_order[1]
            c = loop_order[2]
            d = loop_order[3]
            e = loop_order[4]
            f = loop_order[5]
            generate_subroutine([A,B,C,D,E,F],[a,b,c,d,e,f]) 
            generate_driver([A,B,C,D,E,F],[a,b,c,d,e,f])

def run_simple(all_permutations):
    for transpose_order in all_permutations:
        A = transpose_order[0]
        B = transpose_order[1]
        C = transpose_order[2]
        D = transpose_order[3]
        E = transpose_order[4]
        F = transpose_order[5]    
        driver_name = 'transpose_'+str(A)+str(B)+str(C)+str(D)+str(E)+str(F)
        os.system('./exe/'+driver_name+'.x > '+log_dir+driver_name+'.log')

#generate_subroutine([1,0,2,3,4,5],[0,1,2,3,4,5]) 
#generate_driver([1,0,2,3,4,5],[0,1,2,3,4,5])

indices = [5,4,0,1,2,3]
#indices = [1,2,3,4,5,6]

#all_permutations = perm(indices)
all_permutations = [indices]

build_hirata()
build_subroutines_simple(all_permutations)
build_drivers_simple(all_permutations)
run_simple(all_permutations)    