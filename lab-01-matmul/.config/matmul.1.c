#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "config.h"
#include "precision.h"

#ifdef CBLAS_GEMM
#include <cblas.h>
#endif

#ifdef _EXTRAE_
#include "extrae_user_events.h"
#endif


const int NB = BSIZE;

void matmul_tile( REAL *A, REAL *B, REAL *C )
{
   int i, j, k;

   for (i=0; i < NB; i++) {
      for (k=0; k < NB; k++) {
         REAL tmp = A[i*NB+k];
         for (j=0; j < NB; j++) {
            C[i*NB+j] += tmp * B[k*NB+j];
         }
      }
   }

}

void matmul( int m, int l, int n, int mDIM, int lDIM, int nDIM, REAL **tileA, REAL **tileB,
             REAL **tileC )
{
   int i, j, k;

#pragma omp parallel for private(j,k)
   for(i = 0;i < mDIM; i++){
      for (j = 0; j < nDIM; j++){
         for (k = 0; k < lDIM; k++){
            matmul_tile (tileA[i*lDIM+k], tileB[k*nDIM+j], tileC[i*nDIM+j]);
         }
      }
   }
}



void matmul_tile_seq( REAL *A, REAL *B, REAL *C )
{
   int i, j, k;

   for (i=0; i < NB; i++) {
      for (k=0; k < NB; k++) {
         REAL tmp = A[i*NB+k];
         for (j=0; j < NB; j++) {
            C[i*NB+j] += tmp * B[k*NB+j];
         }
      }
   }
}

void matmul_reference( int m, int l, int n, int mDIM, int lDIM, int nDIM, REAL **tileA, REAL **tileB, REAL **tileC )
{

   int i, j, k;
   for(i = 0;i < mDIM; i++){
      for (j = 0; j < nDIM; j++){
         for (k = 0; k < lDIM; k++){
            matmul_tile_seq (tileA[i*lDIM+k], tileB[k*nDIM+j], tileC[i*nDIM+j]);
         }
      }
   }
}

