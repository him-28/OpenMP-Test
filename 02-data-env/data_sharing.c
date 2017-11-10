#include <stdio.h>
#include <string.h>
#include "omp.h"

// -------------------------------------------------------------------------------------------------
// Each thread in the parallel region should have their own private 'a' variable
// -------------------------------------------------------------------------------------------------
char data_parallel_01 ( void )
{
   int a = 0;

   #pragma omp parallel private(a)
   {
      a = 1;
   }

   return ( a == 0 );
}


// -------------------------------------------------------------------------------------------------
// All the threads in the parallel region must share 'a' variable
// -------------------------------------------------------------------------------------------------
char data_parallel_02 ( void )
{
   int a = 0;

   #pragma omp parallel shared(a)
   {
      a = 1;
   }

   return ( a == 1 );
}


// -------------------------------------------------------------------------------------------------
// All threads must share variabe 'a' and privatize 'b' and 'c', but when entering the parallel
// region all private copies of 'b' must have the same value than original 'b'. In this case we
// do not care about 'c' initial value (inside the parallel region), so we DO NOT want to pay the
// cost of have it.
// -------------------------------------------------------------------------------------------------
char data_parallel_03 ( void )
{
   int a = 0, b = 5, c = 7;

   #pragma omp parallel shared(a) firstprivate(b) private(c) 
   {
      if ( b != 5 ) a = 1;
      b = b + 1;
      if ( c == 7 ) a = 1;
      if ( a != 1 ) a = 2;
      c = 1;
      if ( b != 6 ) a = 3;
   }

   return ( ( a == 2 ) && (b == 5) && ( c == 7) );
}


// -------------------------------------------------------------------------------------------------
// We want to accumulate into 'result' variable 100 increments per thread. As there is NO work
// distribution the final result must be 100 multiplied by the number of threads participating in
// the parallel region. You must notice that 'result' variable is protected with a critical
// construct so no extra synchronization is requiered.
// -------------------------------------------------------------------------------------------------
char data_parallel_04 ( void )
{
   int i, result = 0;
  // int NT = 100;
   #pragma omp parallel shared(result) private(i)
   {
	
      for ( i = 0; i < 100; i++ ) {
         #pragma omp critical
         result += 1;
      }
   }

   return ( result == omp_get_max_threads() * 100 );
}

// -------------------------------------------------------------------------------------------------
// We want to distribute a 'vector increment' among all the threads participating in the parallel
// region. We try to use number of threads and the thread id to compute lower and upper bound
// but it seems still have some problems.
// -------------------------------------------------------------------------------------------------
char data_parallel_05 ( void )
{
   int i, SIZE = 1000;
   int A[SIZE];
   int id, nt, lb, ub;

   for ( i = 0; i < SIZE; i++ ) A[i] = 1;

   #pragma omp parallel default(none) shared(SIZE,A) private(id,nt,lb,ub, i) 
   {
      id = omp_get_thread_num();
      nt = omp_get_num_threads();
      lb = id*(SIZE/nt);
      ub = (id+1)*(SIZE/nt)+((id==nt-1)?(SIZE%nt):0);

      for ( i = lb; i < ub; i++ ) A[i]++;
   }

   for ( i = 0; i < SIZE; i++ ) if ( A[i] != 2 ) return 0;

   return 1 ;
}

// -------------------------------------------------------------------------------------------------
// We want to accumulate the addition of the first 1000 natural numbers into 'result' variable.
// -------------------------------------------------------------------------------------------------
char data_parallel_06 ( void )
{
   int i, SIZE = 1000;
   int A[SIZE], result = 0;
   int id, nt, lb, ub;

   for ( i = 0; i < SIZE; i++ ) A[i] = i+1;

   #pragma omp parallel reduction(+:result) default(none) shared(SIZE,A) private(id,nt,lb,ub, i) 
   {
      
      id = omp_get_thread_num();
      nt = omp_get_num_threads();
      lb = id*(SIZE/nt);
      ub = (id+1)*(SIZE/nt)+((id==nt-1)?(SIZE%nt):0);

      for ( i = lb; i < ub; i++ ) result += A[i];
   }

   return ( result == (SIZE/2) * (SIZE+1) );
}

// =================================================================================================

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_result ( char *test, char result )
{
   int i, width = 30, length = strlen(test);

   printf("%s",test);
   for ( i = width - length; i<width;i++) printf(".");
   printf(" %s", result? ANSI_COLOR_GREEN "pass": ANSI_COLOR_RED "fail");
   printf(ANSI_COLOR_RESET"\n");
}

int main ( int argc, char *argv[] )
{
   
   print_result("data_parallel_01", data_parallel_01());
   print_result("data_parallel_02", data_parallel_02());
   print_result("data_parallel_03", data_parallel_03());
   print_result("data_parallel_04", data_parallel_04());
   print_result("data_parallel_05", data_parallel_05());
   print_result("data_parallel_06", data_parallel_06());

   return 0;
}
