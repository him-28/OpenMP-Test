#include "matrix_loop.h"
#include "support.h"
#include "matrix_main.h"

void matrix_multiply ( double *A, double *B, double *C, int size)
{
   int i,j,k;
 #pragma omp for private(j,k) //schedule(dynamic) nowait
   for(i=0;i<size;i++)
   {
      int base = i * size;
      for(j=0;j<size;j++)
      {
         int jindex = base + j;
         for( k=0;k<size;k++)
         {
         // A[i*size+j] = A[i*size+j] + B[i*size+k]*C[k*size+j];
            A[jindex] = A[jindex] + B[base+k]*C[k*size+j];
         }
      }
   }
}

void matrix_compute ( double *A, int size )
{
   int i,j;
  #pragma omp for schedule(guided) private(j) //(dynamic) nowait
   for(i=0;i<size;i++)
   {
      for(j=0;j<=i;j++)
      {
         A[i*size+j] = compute(i,j,size);

      }
   }
  #pragma omp for schedule(guided) private(j) 
   for(i=0;i<size;i++)
   {
      for(j=i;j<size;j++)
      {
         A[i*size+j] = A[j*size+i];
      }
   }
}
