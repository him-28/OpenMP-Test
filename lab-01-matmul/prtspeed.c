#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "precision.h"

#define max(a,b)( ((a) > (b)) ? (a) : (b) )

void prtspeed_human( int m, int l, int n, int nb, double time, int err, unsigned long nops )
{
	double speed = 1.0e-9*nops/time;
	printf("Matrix size: %dx%d\n", m, n);
	printf("Block size: %dx%d\n", nb, nb);
#ifdef DP
	printf("Precision type: Double\n");
#else
	printf("Precision type: Simple\n");
#endif

	printf("  GFLOPS : %.4lf\n", speed);
	printf("  computation time (in seconds): %.4lf\n", time);
	if ( err == 0 ) {
		printf("  Verification: Ok\n");
	} else {
		printf("  Verification: Failed  (%d)\n", err);
	}
}

void prtspeed_machine( int m, int l, int n, int nb, double time, int err, unsigned long nops )
{
    //Print data so it can be read by a machine for mater processing
    printf("%.6lf,", time);
}


void prtspeed( int m, int l, int n, int nb, double time, int err, unsigned long nops ) {
    char *output;

    output = getenv("MM_OUTPUT");
    if (!output || strcmp(output, "machine")) {
        prtspeed_human(m, l, n, nb, time, err, nops);
    } else {
        prtspeed_machine(m, l, n, nb, time, err, nops);
    }
}
