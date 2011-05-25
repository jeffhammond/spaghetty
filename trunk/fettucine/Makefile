CXX      = g++
CXXFLAGS = -g -O3 -Wall -pedantic

CC       = gcc
CFLAGS   = -g -O3 -Wall -pedantic -std=c99
CLIBS    = -L. -lpermute

OBJECTS := 	permute_1234.o permute_1243.o permute_1324.o permute_1342.o permute_1423.o permute_1432.o \
			permute_2134.o permute_2143.o permute_2314.o permute_2341.o permute_2413.o permute_2431.o \
			permute_3124.o permute_3142.o permute_3214.o permute_3241.o permute_3412.o permute_3421.o \
			permute_4123.o permute_4132.o permute_4213.o permute_4231.o permute_4312.o permute_4321.o
			
SOURCES := 	permute_1234.c permute_1243.c permute_1324.c permute_1342.c permute_1423.c permute_1432.c \
			permute_2134.c permute_2143.c permute_2314.c permute_2341.c permute_2413.c permute_2431.c \
			permute_3124.c permute_3142.c permute_3214.c permute_3241.c permute_3412.c permute_3421.c \
			permute_4123.c permute_4132.c permute_4213.c permute_4231.c permute_4312.c permute_4321.c

all: test.x

generate: generator.x
	@echo Generating source
	./generator.x

generator.x: generator.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
test.x: test.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

libpermute.a: source objects
	-ar -r libpermute.a $(OBJECTS)

objects: $(OBJECTS)

source: generate

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
show:
	@echo $(OBJECTS)

clean:
	@rm -f $(OBJECTS)

realclean: clean
	@rm -f test.x generator.x libpermute.a $(SOURCES)


