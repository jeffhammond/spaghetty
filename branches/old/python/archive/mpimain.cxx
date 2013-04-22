#include <iostream>
#include <math.h>
#include "mpi.h"

using namespace std;
using namespace MPI;

/*
Example for how to link with Fortran from C++
extern "C"{
  void mulmatvec_(int *m, int *n, int *max, 
      double a[MAX][MAX], double x[MAX], double b[MAX]);
}
*/

extern "C"{ void transpose_1234_driver();}
#ifdef ALL24
extern "C"{ void transpose_1243_driver();}
extern "C"{ void transpose_1324_driver();}
extern "C"{ void transpose_1342_driver();}
extern "C"{ void transpose_1423_driver();}
extern "C"{ void transpose_1432_driver();}
extern "C"{ void transpose_2134_driver();}
extern "C"{ void transpose_2143_driver();}
extern "C"{ void transpose_2314_driver();}
extern "C"{ void transpose_2341_driver();}
extern "C"{ void transpose_2413_driver();}
extern "C"{ void transpose_2431_driver();}
extern "C"{ void transpose_3124_driver();}
extern "C"{ void transpose_3142_driver();}
extern "C"{ void transpose_3214_driver();}
extern "C"{ void transpose_3241_driver();}
extern "C"{ void transpose_3412_driver();}
extern "C"{ void transpose_3421_driver();}
extern "C"{ void transpose_4123_driver();}
extern "C"{ void transpose_4132_driver();}
extern "C"{ void transpose_4213_driver();}
extern "C"{ void transpose_4231_driver();}
extern "C"{ void transpose_4312_driver();}
extern "C"{ void transpose_4321_driver();}
#endif

int main(int argc, char** argv) {

        int status=-1;
        int i,j;
        int me, nprocs;
        double start_time, end_time, driver_time;
        
        /* All MPI programs begin with this. *
         * It ensures proper handling of command line arguments. */
        status = MPI_Init(&argc, &argv);

        /* Finding the identity of the local process. */
        status = MPI_Comm_rank(MPI::COMM_WORLD, &me);
        cout << "process " << me << ": status = " << status << " after MPI_Comm_rank" << endl;

        /* How many processes are we using? */
        status = MPI_Comm_size(MPI::COMM_WORLD, &nprocs);
        cout << "process " << me << ": status = " << status << " after MPI_Comm_size" << endl;
        //if(me==0){ cout << "nprocs = " << nprocs << endl; }
        
        /* This is where you put the serial executable. */
        if (me==0){transpose_1234_driver();}
#ifdef ALL24
        if (me==1){transpose_1243_driver();}
        if (me==2){transpose_1324_driver();}
        if (me==3){transpose_1342_driver();}
        if (me==4){transpose_1423_driver();}
        if (me==5){transpose_1432_driver();}
        if (me==6){transpose_2134_driver();}
        if (me==7){transpose_2143_driver();}
        if (me==8){transpose_2314_driver();}
        if (me==9){transpose_2341_driver();}
        if (me==10){transpose_2413_driver();}
        if (me==11){transpose_2431_driver();}
        if (me==12){transpose_3124_driver();}
        if (me==13){transpose_3142_driver();}
        if (me==14){transpose_3214_driver();}
        if (me==15){transpose_3241_driver();}
        if (me==16){transpose_3412_driver();}
        if (me==17){transpose_3421_driver();}
        if (me==18){transpose_4123_driver();}
        if (me==19){transpose_4132_driver();}
        if (me==20){transpose_4213_driver();}
        if (me==21){transpose_4231_driver();}
        if (me==22){transpose_4312_driver();}
        if (me==23){transpose_4321_driver();}
#endif

        /* All MPI programs end with this. */
        status = MPI_Finalize();
        cout << "process " << me << ": status = " << status << " after MPI_Finalize" << endl;
        
        return(0);
        
}

