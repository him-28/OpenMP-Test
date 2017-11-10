#include <stdio.h>
#include <time.h>
#include "support.h"

void print_headers(int n)
{
   int i;

   printf("program, threads, version, ");
   for ( i = 0; i<n; i++) {
      printf("time-%d, ",i);
   }
   printf("total, check\n");
}

void print_results(const char* program, const char *version, int threads, double *times, int n, double total, int *test )
{
   int i, check = n;

   for (i=0; i<n; i++ ) if ( !test[i] ) { check = i; break; }

   printf("%s,%d,%s,",program, threads, version);
   for ( i = 0; i<n; i++) {
      printf("%f,", times[i]);
   }
   printf("%f,%s(%d)",total, (check == n)?ANSI_COLOR_GREEN "pass":ANSI_COLOR_RED "fail", check);
   printf(ANSI_COLOR_RESET"\n");
}

void print_matrix ( double *Matrix, int size )
{
   int i,j;

   printf("Matrix %p = { \n", Matrix);
   for ( i = 0; i < size; i++ )
   {
      for ( j = 0; j < size; j++ )
      {
         printf("%06.2f, ", Matrix[i*size+j]);
      }
      printf("\n");
   }
   printf("}\n");
}


int check_matrix_result ( double *M, int size )
{
   int i,j;

   for ( i = 0; i < size; i++ )
      for ( j = 0; j < size; j++ )
         if ( M[i*size+j] != (double) (i*j*size)) return 0;

   return 1;
}

int check_matrix_value_row ( double *M, int size )
{
   int i,j;

   for ( i = 0; i < size; i++ )
      for ( j = 0; j < size; j++ )
         if ( M[i*size+j] != (double) (i) ) return 0;

   return 1;
}

int check_matrix_value_col ( double *M, int size )
{
   int i,j;

   for ( i = 0; i < size; i++ )
      for ( j = 0; j < size; j++ )
         if ( M[i*size+j] != (double) (j) ) return 0;

   return 1;
}

double get_time(void)
{
   struct timespec time_value;
   clock_gettime(CLOCK_MONOTONIC, &time_value);
   return ((double) time_value.tv_sec) + ( (double) time_value.tv_nsec / 1000000000.0 );
}

double compute ( int i, int j, int size)
{
   int idx;
   double ii = (double ) i;
   double jj = (double ) j;
   double value = 0;

   for(idx=i;idx<size;idx++)
   {
      if (idx % 2) value+= ((double)idx) * ii*jj;
      else value+= ((double)idx * -1) * ii*jj;
   }
   for(idx=j;idx<size;idx++)
   {
      if (idx % 2) value+= ((double)idx) * ii*jj;
      else value+= ((double)idx * -1) * ii*jj;
   }

   for(idx=i;idx<size;idx++)
   {
      if (idx % 2) value+= ((double)idx * -1) * ii*jj;
      else value+= ((double)idx) * ii*jj;
   }
   for(idx=j;idx<size;idx++)
   {
      if (idx % 2) value+= ((double)idx * -1) * ii*jj;
      else value+= ((double)idx) * ii*jj;
   }

   for(idx=0;idx<size;idx++)
   {
      value+=ii*jj;
   }

   return value;
}

