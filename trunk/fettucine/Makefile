#WALL     = -Wall -pedantic
WALL     = 

#OMP      = -fopenmp
OMP      = -qsmp=omp

OPT      = -g -O3 -qtune=pwr7 -qarch=pwr7

CXX      = xlC_r
CXXFLAGS = $(OPT) $(WALL)

CC       = xlc_r -qlanglvl=stdc99
CFLAGS   = $(OPT) $(WALL) $(OMP)

FC       = xlf_r
FFLAGS   = $(OPT) $(WALL) -qextname

LD       = $(CC)
LDFLAGS  = $(CFLAGS) -L. -lpermute

OBJECTS := 	permute_1234.o permute_1243.o permute_1324.o permute_1342.o permute_1423.o permute_1432.o \
			permute_2134.o permute_2143.o permute_2314.o permute_2341.o permute_2413.o permute_2431.o \
			permute_3124.o permute_3142.o permute_3214.o permute_3241.o permute_3412.o permute_3421.o \
			permute_4123.o permute_4132.o permute_4213.o permute_4231.o permute_4312.o permute_4321.o \
			tce_sort_hirata.o tce_sort_hirata_noflop.o \
			getticks.o util.o
			
SOURCES := 	permute_1234.c permute_1243.c permute_1324.c permute_1342.c permute_1423.c permute_1432.c \
			permute_2134.c permute_2143.c permute_2314.c permute_2341.c permute_2413.c permute_2431.c \
			permute_3124.c permute_3142.c permute_3214.c permute_3241.c permute_3412.c permute_3421.c \
			permute_4123.c permute_4132.c permute_4213.c permute_4231.c permute_4312.c permute_4321.c

all: help

help:
	@echo Valid targets are generate, libpermute.a and test.x

generate: generator.x
	@echo Generating source
	./generator.x 0 1

generator.x: generator.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
test.x: test.c generator.x
	./generator.x 1 0
	$(LD) $< $(LDFLAGS) -o $@

libpermute.a: $(OBJECTS)
	-ar -r libpermute.a $(OBJECTS)

show:
	@echo $(OBJECTS)

clean:
	@rm -f $(OBJECTS) $(SOURCES)

realclean: clean
	@rm -f test.x generator.x libpermute.a


