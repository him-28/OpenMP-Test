#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>

int main ( int argc, char *argv[] ) {

   cpu_set_t mask;
   sched_getaffinity( 0, sizeof(mask), &mask );
   int NCPUS = sysconf(_SC_NPROCESSORS_ONLN);

   printf("(%d):",getpid());
   for ( int i=0; i<NCPUS; i++ )
      printf("%d", CPU_ISSET( i, &mask ));

   printf("\n");

  return 0;
}
