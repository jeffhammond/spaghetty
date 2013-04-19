import fileinput
import string
import sys
import os

c_compiler = 'icc'
c_link_flags = '-g -O1 -xT -march=core2 -mtune=core2 -align -strict-ansi'
c_opt_flags = '-g -O3 -xT -march=core2 -mtune=core2 -funroll-loops -align -strict-ansi'
#fortran_compiler = 'ifort'
#fortran_link_flags = '-g -O1 -xT -march=core2 -mtune=core2 -align '
#fortran_opt_flags = '-g -O3 -xT -march=core2 -mtune=core2 -funroll-loops -align '
src_dir = '/home/jeff/code/spaghetty/trunk/source/ansi-C/'
exe_dir = '/home/jeff/code/spaghetty/trunk/binary/ansi-C/'

modlabel = 'a4d'

lib_name = 'tce_sort_'+modlabel+'.a'

count = '20'
rank  = '8'
ranks = [rank,rank,rank,rank]
size  =  int(ranks[0])*int(ranks[1])*int(ranks[2])*int(ranks[3])
sizechar = str(size)

cind = '  '
ctab = '  '

def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

indices = ['1','2','3','4']
#indices = ['4','3','2','1']

transpose_list = [indices]
#transpose_list = perm(indices)
loop_list = [indices]
#loop_list = perm(indices)


for transpose_order in transpose_list:
    dummy = 0
    A = transpose_order[0]
    B = transpose_order[1]
    C = transpose_order[2]
    D = transpose_order[3]
    driver_name = 'trans_a4d_'+A+B+C+D+'_'+modlabel
    print driver_name
    source_name = driver_name+'_driver.c'
    source_file = open(source_name,'w')
    source_file.write(cind+'#include <stdio.h>\n')
    source_file.write(cind+'#include <stdlib.h>\n')
    source_file.write(cind+'#include <math.h>\n')
    source_file.write(cind+'#include <time.h>\n\n')
    #source_file.write(cind+'#define MIN(X,Y) ((X) < (Y) ? : (X) : (Y))\n\n')
    #source_file.write(cind+'void main(){\n\n')
    source_file.write(cind+'int main(int argc, char **argv){\n\n')
    source_file.write(cind+'double before['+ranks[0]+']['+ranks[0]+']['+ranks[0]+']['+ranks[0]+'];\n')
    source_file.write(cind+'double after_jeff['+ranks[0]+']['+ranks[0]+']['+ranks[0]+']['+ranks[0]+'];\n')
    source_file.write(cind+'double after_hirata['+ranks[0]+']['+ranks[0]+']['+ranks[0]+']['+ranks[0]+'];\n')
    source_file.write(cind+'double factor;\n')
    source_file.write(cind+'clock_t Tstart,Tfinish;\n')
    source_file.write(cind+'double Thirata,Tjeff,Tspeedup,Tbest;\n')
    source_file.write(cind+'unsigned int i,j,k,l;\n')
    source_file.write(cind+'unsigned int aSize[4];\n')
    source_file.write(cind+'unsigned int perm[4];\n')
    source_file.write(cind+'unsigned int fastest[4];\n\n')
    source_file.write(cind+'aSize[0] = '+ranks[0]+';\n')
    source_file.write(cind+'aSize[1] = '+ranks[1]+';\n')
    source_file.write(cind+'aSize[2] = '+ranks[2]+';\n')
    source_file.write(cind+'aSize[3] = '+ranks[3]+';\n\n')
    source_file.write(cind+'perm[0] = '+A+';\n')
    source_file.write(cind+'perm[1] = '+B+';\n')
    source_file.write(cind+'perm[2] = '+C+';\n')
    source_file.write(cind+'perm[3] = '+D+';\n\n')
    source_file.write(cind+0*ctab+'for( i=0; i<'+ranks[0]+'; i++) {\n')
    source_file.write(cind+1*ctab+'for( j=0; j<'+ranks[1]+'; j++) {\n')
    source_file.write(cind+2*ctab+'for( k=0; k<'+ranks[2]+'; k++) {\n')
    source_file.write(cind+3*ctab+'for( l=0; l<'+ranks[3]+'; l++) {\n')
    source_file.write(cind+4*ctab+'before[i][j][k][l] = (double)(l + k*10 + j*100 + i*1000);\n')
    source_file.write(cind+3*ctab+'}\n')
    source_file.write(cind+2*ctab+'}\n')
    source_file.write(cind+1*ctab+'}\n')
    source_file.write(cind+0*ctab+'}\n\n')
    source_file.write(cind+0*ctab+'for( i=0; i<'+ranks[0]+'; i++) {\n')
    source_file.write(cind+1*ctab+'for( j=0; j<'+ranks[1]+'; j++) {\n')
    source_file.write(cind+2*ctab+'for( k=0; k<'+ranks[2]+'; k++) {\n')
    source_file.write(cind+3*ctab+'for( l=0; l<'+ranks[3]+'; l++) {\n')
    source_file.write(cind+4*ctab+'printf("before[i][j][k][l] = %f\\n",before[i][j][k][l]);\n')
    source_file.write(cind+3*ctab+'}\n')
    source_file.write(cind+2*ctab+'}\n')
    source_file.write(cind+1*ctab+'}\n')
    source_file.write(cind+0*ctab+'}\n\n')
    source_file.write(cind+'factor = 1.0;\n')
    source_file.write(cind+'Tbest=999999.0;\n')
    source_file.write(cind+'Tstart=clock();\n\n')
    source_file.write(cind+'for( i=0; i<'+count+'; i++) {\n')
    #source_file.write(cind+'  CALL tce_sort_4(before, after_hirata,\n')
    #source_file.write(cind+'                  aSize(1), aSize(2), aSize(3), aSize(4),\n')
    #source_file.write(cind+'                  perm(1), perm(2), perm(3), perm(4), factor)\n')
    source_file.write(cind+'}\n\n')
    source_file.write(cind+'Tfinish=clock();\n')
    source_file.write(cind+'Thirata=(double)(Tfinish-Tstart);\n\n')
    source_file.write(cind+'printf("TESTING TRANPOSE TYPE '+A+B+C+D+'\\n");\n')
    source_file.write(cind+'printf("===================\\n");\n')
    source_file.write(cind+'printf("The compilation flags were:\\n");\n')
    for option in range(0,len(c_opt_flags.split())):
        source_file.write(cind+'printf("'+c_opt_flags.split()[option]+'\\n");\n')

    source_file.write(cind+'printf("===================\\n");\n\n')
    source_file.write(cind+'printf("Hirata Reference = %f seconds\\n",Thirata);\n')
    source_file.write(cind+'printf("Algorithm        Jeff          Speedup         Best             Best Speedup\\n");\n')
    for loop_order in loop_list:
        dummy = dummy+1
        a = loop_order[0]
        b = loop_order[1]
        c = loop_order[2]
        d = loop_order[3]
        subroutine_name = 'trans_a4d_'+A+B+C+D+'_loop_'+a+b+c+d+'_'
        source_file.write(cind+'Tstart=clock();\n\n')
        #source_file.write(cind+'printf("*** START TIMING THE SUBROUTINE ***\\n");\n')
        source_file.write(cind+'for( i=0; i<'+count+'; i++) {\n')
        source_file.write(cind+1*ctab+subroutine_name+'(before, after_jeff,\n')
        source_file.write(cind+7*ctab+'aSize[1], aSize[1], aSize[2], aSize[3],\n')
        source_file.write(cind+7*ctab+'&factor);\n')
        source_file.write(cind+'}\n\n')
        #source_file.write(cind+'printf("*** FINISHED TIMING THE SUBROUTINE ***\\n");\n')
        source_file.write(cind+'Tfinish=clock();\n')
        source_file.write(cind+'Tjeff=(double)(Tfinish-Tstart);\n')
        source_file.write(cind+'Tspeedup=Thirata/Tjeff;\n\n')
        #source_file.write(cind+'Tbest=MIN(Tjeff,Tbest);\n')
        source_file.write(cind+'if(Tjeff == Tbest){ \n')
        source_file.write(cind+'  fastest[0]='+a+';\n')
        source_file.write(cind+'  fastest[1]='+b+';\n')
        source_file.write(cind+'  fastest[2]='+c+';\n')
        source_file.write(cind+'  fastest[3]='+d+';\n')
        source_file.write(cind+'}\n\n')
        if 0 < dummy < 10:
            nice_dummy=cind+''+str(dummy)

        if 9 < dummy < 100:
            nice_dummy=' '+str(dummy)

        if 99 < dummy < 999:
            nice_dummy=''+str(dummy)

        source_file.write(cind+'printf("'+nice_dummy+' Loop '+a+b+c+d+' %f %f %f %f\\n",Tjeff,Tspeedup,Tbest,Thirata/Tbest);\n\n')
        ###source_file.write(cind+0*ctab+'for( i=0; i<'+ranks[0]+'; i++) {\n')
        ###source_file.write(cind+1*ctab+'for( j=0; j<'+ranks[1]+'; j++) {\n')
        ###source_file.write(cind+2*ctab+'for( k=0; k<'+ranks[2]+'; k++) {\n')
        ###source_file.write(cind+3*ctab+'for( l=0; l<'+ranks[3]+'; l++) {\n')
        ###source_file.write(cind+4*ctab+'if (after_jeff[i][j][k][l] != after_hirata[i][j][k][l]) {\n')
        ###source_file.write(cind+5*ctab+'printf("jeff error %d %d %d %d %f %f\\n",i,j,k,l,after_jeff[i][j][k][l], after_hirata[i][j][k][l]);\n')
        ###source_file.write(cind+4*ctab+'}\n')
        ###source_file.write(cind+3*ctab+'}\n')
        ###source_file.write(cind+2*ctab+'}\n')
        ###source_file.write(cind+1*ctab+'}\n')
        ###source_file.write(cind+0*ctab+'}\n\n')

    source_file.write(cind+'printf("The best loop order is: %d%d%d%d\\n",fastest[0],fastest[1],fastest[2],fastest[3]);\n')
    source_file.write(cind+'printf("The best time is: %f\\n",Tbest);\n')
    source_file.write(cind+'printf("The best speedup is: %f\\n",Thirata/Tbest);\n\n')
    source_file.write(cind+'return 0;\n\n')
    source_file.write(cind+'}\n')
    source_file.close()
    print c_compiler+' '+c_link_flags+' '+' '+source_name+' '+lib_name+' '+' -o '+exe_dir+driver_name+'.x'
    os.system(c_compiler+' '+c_link_flags+' '+' '+source_name+' '+lib_name+' '+' -o '+exe_dir+driver_name+'.x')
    os.system('mv '+source_name+' '+src_dir)
