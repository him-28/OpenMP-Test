
CC=gcc
CFLAGS=-O0

test-affinity: test_affinity.c
	$(CC) $(CFLAGS) $^ -o $@ 

run: test-affinity
	@./test-affinity

clean:
	rm -fr test-affinity
