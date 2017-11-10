#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "config.h"
#include "precision.h"

#ifdef _EXTRAE_
#include <extrae_user_events.h>
#endif



double   cclock( void );
#ifdef VALS_INT
int      check( int nrep, int m, int l, int n, int mDIM, int lDIM, int nDIM, REAL **c, REAL ** a, REAL ** b );
#else
int      check( int nrep, int m, int l, int n, int mDIM, int nDIM, REAL **c, REAL **ref);
#endif
void     gendat(int, int, int, int, int, int, REAL **, REAL **, REAL **);
void     matmul( int, int, int, int, int, int, REAL **a, REAL **b, REAL **c );
void     prtspeed( int, int, int, int, double, int, unsigned long );


void matmul_reference( int m, int l, int n, int mDIM, int lDIM, int nDIM, REAL **tileA, REAL **tileB, REAL **tileC );

int calcdim(int x)
{
        int dimval;
        if(x%BSIZE != 0)
                dimval = x/BSIZE + 1;
        else
                dimval = x/BSIZE;

        return dimval;
}
	
int main(int argc, char *argv[])
{ 
   int      lda, m, l, n;
   int      mDIM, lDIM, nDIM;
   int      err, nrep;
   unsigned long nops;
   int      i,k,j;
   REAL   **a, **b, **c;
   double   time;
   FILE     *inl;

   REAL    **ref;


   inl = fopen( "test.in", "r" );
   if (inl == 0) {
      printf("No input file 'test.in' found.\n");
      exit(1);
   }

#ifdef _EXTRAE_
   Extrae_init();
#endif

   int check_result = 1;

   if (argc > 1) {
      check_result = atoi(argv[1]);
   }

   while( ( fscanf( inl, "%d%d%d%d\n", &m, &l, &n, &nrep ) != EOF ) ) {
      lda = l + 1;

      mDIM = calcdim(m);
      lDIM = calcdim(l);
      nDIM = calcdim(n);

      a = (REAL **)malloc( mDIM*lDIM*sizeof( REAL *) );
      b = (REAL **)malloc( lDIM*nDIM*sizeof( REAL *) );
      c = (REAL **)malloc( mDIM*nDIM*sizeof( REAL *) );


      for(i=0;i<mDIM*lDIM;i++)
         a[i] = (REAL *)malloc(BSIZE*BSIZE*sizeof(REAL));

      for(i=0;i<lDIM*nDIM;i++)
         b[i] = (REAL *)malloc(BSIZE*BSIZE*sizeof(REAL));

      for(i=0;i<mDIM*nDIM;i++)
         c[i] = (REAL *)malloc(BSIZE*BSIZE*sizeof(REAL));

#ifndef VALS_INT
      //allocate space for a reference result matrix
      ref = (REAL **)malloc( mDIM*nDIM*sizeof( REAL *) );
      for(i=0; i<mDIM*mDIM; i++) {
         ref[i] = (REAL *)malloc(BSIZE*BSIZE*sizeof(REAL));
      }

      int k,y;
      //initialixe reference values
      for( i = 0; i < lDIM; ++i ) {
         for( j = 0; j < nDIM; ++j ) {
            for( k = 0; k < BSIZE; ++k ) {
               for( y = 0; y < BSIZE; ++y ) {
                  ref[ i*nDIM + j ][ k*BSIZE+y ] = 0.0;
               }
            }
         }
      }
#endif

      gendat( mDIM, lDIM, nDIM, m, l, n, a, b, c );

      if (check_result){
         matmul_reference( m, l, n, mDIM, lDIM, nDIM, a, b, ref );
      }

#ifdef ENABLE_WARMUP
      matmul( m, l, n, mDIM, lDIM, nDIM, a, b, c );
#endif

      time = cclock();
      for( i = 0; i < nrep; i++ ){
#ifdef _EXTRAE_
         Extrae_event(100000, mDIM);
#endif
         matmul( m, l, n, mDIM, lDIM, nDIM, a, b, c ); 
#ifdef _EXTRAE_
         Extrae_event(100000, 0);
#endif
      }

      time = cclock() - time;
      if (check_result) {
#ifdef ENABLE_WARMUP
#ifdef VALS_INT
         err   = check( nrep+1, m, l, n, mDIM, lDIM, nDIM, c, a, b);
#else
         err   = check( nrep+1, m, l, n, mDIM, nDIM, c, ref);
#endif

#else //!enable warmup
#ifdef VALS_INT
         err   = check( nrep, m, l, n, mDIM, lDIM, nDIM, c, a, b);
#else
         err   = check( nrep, m, l, n, mDIM, nDIM, c, ref);
#endif
#endif //enable warmup
      } else {
         err = 0;
      }
      time = time/nrep;
      nops  = (unsigned long) 2*m*l*n;
      prtspeed( m, l, n, BSIZE, time, err, nops );

      for(i=0;i<mDIM*lDIM;i++)
         free( a[i] );

      for(i=0;i<lDIM*nDIM;i++)
         free( b[i] );

      for(i=0;i<mDIM*nDIM;i++)
         free( c[i] );

      free( a ); free( b ); free( c );
   }
#ifdef _EXTRAE_
   Extrae_fini();
#endif
}
