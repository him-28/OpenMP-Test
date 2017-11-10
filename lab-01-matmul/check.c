#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>

#include "config.h"
#include "precision.h"

#ifndef VALS_INT
int check( int nrep, int m, int l, int n, int mDIM, int nDIM, REAL **c, REAL **ref)
{
    int    i, j, k, o, err = 0;

    REAL eps = 0.0001;

    int perfectM = m / BSIZE;
    int perfectN = n / BSIZE;

    int leftOutM = m % BSIZE;
    int leftOutN = n % BSIZE;

    for(i=0;i<mDIM;i++){
        for(j=0;j<nDIM;j++){
            for(k=0;k<BSIZE;k++){
                for(o=0;o<BSIZE;o++){
                    if( i == mDIM-1 && mDIM > perfectM && k >= leftOutM )
                        break;
                    else if( j == nDIM-1 && nDIM > perfectN && o >= leftOutN )
                        break;
                    else {
                        REAL diff =( c[i*nDIM+j][k*BSIZE+o] / (ref[i*nDIM+j][k*BSIZE+o])) /nrep;
                        if ( fabs(1-diff) > eps){ //TODO check
                            err++;
                            if (err < 100) fprintf(stderr, "%d %d %lf %lf\n", l, nrep, ref[i*nDIM+j][k*BSIZE+o]*nrep, c[i*nDIM+j][k*BSIZE+o]);
                        }
                    }
                }
            }
        }
    }

        return( err );
    }
#else

    extern const int NB;

#if 0
    int check_matmul_tile( REAL *A, REAL *B, REAL *C , int nrep)
    {
        int nb = NB;
        int i, j, k;
        int val;
        int err = 0;

        // implements C <= alpha*A*B + beta*C, with alpha=1.0 & beta=1.0
        for (i=0; i < nb; i++) {
            for (j=0; j < nb; j++) {
                val = 0;
                for (k=0; k < nb; k++) {
                    val += A[i*nb+k] * B[k*nb+j];
                }
                if (C[i*nb+j] != val) {
                    err++;
                    if (err < 3) printf("%d %d %d %d\n", nb, nrep, val, C[i*nb+j]);
                }
            }
        }
        return (err);
    }
#endif


    int check( int nrep, int m, int l, int n, int mDIM, int lDIM, int nDIM, REAL **tileC, REAL ** tileA, REAL ** tileB)
    {
        int err = 0;
        int nb = NB;
        int i, j, k;
        int val;

        int ii, jj, kk;
        for(ii = 0;ii < mDIM; ii++){
            for (jj = 0; jj < nDIM; jj++){
                for (i=0; i < nb; i++) {
                    for (j=0; j < nb; j++) {
                        val = 0;
                        for (kk = 0; kk < lDIM; kk++){
                            //                                err += check_matmul_tile (tileA[i* /*lDIM*/ nDIM+k], tileB[k*nDIM+j], tileC[i*nDIM+j], nrep);

                            for (k=0; k < nb; k++) {
                                val += tileA[ii*mDIM+kk][i*nb+k] * tileB[kk*lDIM+jj][k*nb+j];
                            }
                        }
                        if (tileC[ii*mDIM+jj][i*nb+j] != val*nrep) {
                            err++;
                            if (err < 3) printf("%d %d %d %d\n", nb, nrep, val*nrep, tileC[ii*mDIM+jj][i*nb+j]);
                        }
                    }
                }
            }
        }

        return (err);
    }

#endif
