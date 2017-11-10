CC     =  gcc 

OPT3 	= -O3 -g
CFLAGS  = -Wall -std=c99 -fopenmp
LFLAGS  = -lm 

EXTRAEI = -I$(EXTRAE_HOME)/include
EXTRAEL = -L$(EXTRAE_HOME)/lib -lomptrace

ALL	= heat-omp heat-omp.extrae
all: $(ALL)


heat-omp: heat-omp.c heat.h solver-omp.c misc.o
	$(CC) $(OPT3) $(CFLAGS) $+ $(LFLAGS) -o $@

misc.o: misc.c
	$(CC) -c $(OPT3) $(CFLAGS) $< -o $@

heat-omp.extrae: heat-omp.c heat.h solver-omp.c misc.o
	$(CC) -D_EXTRAE_ $(OPT3) $(CFLAGS) $(EXTRAEI) $+ $(LFLAGS) $(EXTRAEL) -o $@

clean:
	rm -fr $(ALL) .tareador.* *.o *.xdot *.ppm *.out *.err *.prv *.pcf *.row set-0 TRACE.sym TRACE.mpits

