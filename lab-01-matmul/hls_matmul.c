#include <stdc-predef.h>
#include "/opt/install-arm/nanox/include/nanox/nanos.h"
#include "/opt/install-arm/nanox/include/nanox/nanos_omp.h"
#include "/opt/install-arm/nanox/include/nanox/nanos-fpga.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "config.h"
#include "precision.h"
void matmul_tile_hls(float *A, float *B, float *C)
{
  int i;
  int k;
  int j;
  for (i = 0; i < NB; i++)
    {
      for (k = 0; k < NB; k++)
        {
          float tmp = A[i * NB + k];
          for (j = 0; j < NB; j++)
            {
              C[i * NB + j] += tmp * B[k * NB + j];
            }
        }
    }
}
