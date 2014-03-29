INCLUDE		= -I/opt/intel/mkl/9.1/include
FC		= ifort
CC		= icc
AR		= ar
RM		= rm
CPU_FLAGS	= -xT -mtune=core2 -march=core2
CC_OPTS		= -O3 $(CPU_FLAGS)
FC_OPTS		= -O3 $(CPU_FLAGS)
AR_FLAGS	= -r
RM_FLAGS	= -f
OMP_FLAGS	= -openmp
MKL_LIB		= -L/opt/intel/mkl/10.0.3.020/lib/32 -lguide -liomp5 -lmkl_intel -lmkl_ia32 -lmkl_core -lmkl_lapack -lmkl_intel_thread -lpthread -lsvml
CC_FLAGS	= $(CC_OPTS)
FC_FLAGS	= $(FC_OPTS)
LD_FLAGS	= -O1 $(CPU_FLAGS)
LIBS		= -lguide -lpthread -lsvml

LIB_NAME	= transpose.a
BIN_NAME	= transpose.x

all: main

lib: saday hirata jeff omp
	$(AR) $(AR_FLAGS) $(LIB_NAME) transpose_2d_kernel.o transpose_2d_kernel_omp.o tce_sort_2.o saday_sort.o
	$(RM) $(RM_FLAGS) transpose_2d_kernel.o transpose_2d_kernel_omp.o tce_sort_2.o saday_sort.o

main: lib
	$(FC) $(LD_FLAGS) transpose_2d_test.F $(LIBS) $(LIB_NAME) -o $(BIN_NAME)

saday:
	$(CC)  $(CC_OPTS) -c saday_sort.c

hirata:
	$(FC)  $(FC_OPTS) -c tce_sort_2.F

jeff:
	$(FC)  $(FC_OPTS) -c transpose_2d_kernel.F

omp:
	$(FC)  $(FC_OPTS) $(OMP_FLAGS) -c transpose_2d_kernel_omp.F

clean:
	$(RM) $(RM_FLAGS) *.o

realclean: clean
	$(RM) $(RM_FLAGS) *.x *.a
