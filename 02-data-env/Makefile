
CC=gcc
CFLAGS=-O0 -fopenmp

test-data: data_sharing.c
	$(CC) $(CFLAGS) $^ -o $@ 

run: test-data
	@./test-data

clean:
	rm -fr test-data
