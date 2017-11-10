
CC=gcc
CFLAGS=-O0

OBJECTS_SEQ=matrix_init-seq.o matrix_loop-seq.o matrix_list-seq.o
OBJECTS_PAR=matrix_init-par.o matrix_loop-par.o matrix_list-par.o

HEADERS=matrix_main.h
SUPPORT=support.o

all: matrix-seq matrix-par matrix-head matrix-run.sh

matrix-run.sh: ../sched-job.sh
	cp ../sched-job.sh matrix-run.sh
	cat ../.config/benchmark/matrix-run.sh >> matrix-run.sh

matrix-head: matrix_head.o $(SUPPORT)
	$(CC) $(CFLAGS) $^ -o $@ -lrt

################################################################################
################################################################################

matrix-par: matrix_main.c $(SUPPORT) $(OBJECTS_PAR) $(HEADERS)
	$(CC) $(CFLAGS) -fopenmp $^ -o $@ -lrt

matrix_init-par.o: matrix_init.c
	$(CC) $(CFLAGS) -c -fopenmp $^ -o $@ 
 
matrix_loop-par.o: matrix_loop.c
	$(CC) $(CFLAGS) -c -fopenmp $^ -o $@ 

matrix_list-par.o: matrix_list.c
	$(CC) $(CFLAGS) -c -fopenmp $^ -o $@ 

################################################################################
################################################################################

matrix-seq: matrix_main.c $(SUPPORT) $(OBJECTS_SEQ) $(HEADERS)
	$(CC) $(CFLAGS) $^ -o $@ -lrt

matrix_init-seq.o: matrix_init.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

matrix_loop-seq.o: matrix_loop.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

matrix_list-seq.o: matrix_list.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

################################################################################
################################################################################

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./matrix-run.sh

clean:
	rm -fr matrix-par matrix-seq matrix-head *.o

reset: clean matrix-run.sh
	cp ../.config/benchmark/* .

solve-main:
	cp ../.config/benchmark/.config/matrix_main.c .

solve-loop:
	cp ../.config/benchmark/.config/matrix_loop.c .

solve-list:
	cp ../.config/benchmark/.config/matrix_list.c .
