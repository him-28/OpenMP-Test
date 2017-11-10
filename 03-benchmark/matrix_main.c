#include <stdlib.h>
#include <assert.h>

#include "matrix_main.h"
#include "matrix_init.h"
#include "matrix_loop.h"
#include "matrix_list.h"

#include "support.h"

double *A, *B, *C, *S, *T;

double time[PHASES];
int    test[PHASES];

void synthetic_init ()
{
   double ref_time = get_time();

   // Allocating global matrices
   A = (double *) malloc (SIZE * SIZE * sizeof(double));
   B = (double *) malloc (SIZE * SIZE * sizeof(double));
   C = (double *) malloc (SIZE * SIZE * sizeof(double));
   S = (double *) malloc (SIZE * SIZE * sizeof(double));
   T = (double *) malloc (SIZE * SIZE * sizeof(double));

   // Initializing global matrices
   matrix_2D_init_val(A, SIZE, 0.0);
   matrix_2D_init_row(B, SIZE);
   matrix_2D_init_col(C, SIZE);
   matrix_2D_init_val(S, SIZE, 0.0);
   matrix_2D_init_val(T, SIZE, 0.0);

   time[0] = get_time() - ref_time;
}

int synthetic_check ()
{
   assert(PHASES==4 && "synthetic_check() not verifying all phases" );

   // Checking matrix initialization (phase 0 - init)
   test[0] =            check_matrix_value_row(B,SIZE);
   test[0] = test[0] && check_matrix_value_col(C,SIZE);

   // Checking matrix results (phases 1, 2 and 3)
   test[1] = check_matrix_result(A,SIZE);
   test[2] = check_matrix_result(S,SIZE);
   test[3] = check_matrix_result(T,SIZE);

}

void synthetic_phase1 () 
{
   double ref = get_time();
   matrix_multiply(A, B, C, SIZE);
   time[1] = get_time() - ref;
}

void synthetic_phase2 ()
{
   double ref_time = get_time();
   matrix_compute(S,SIZE);
   time[2] = get_time() - ref_time;
}

void synthetic_phase3 ()
{
   double ref_time = get_time();
   matrix_list_compute(T,B,C,SIZE);
   time[3] = get_time() - ref_time;
}


int main (int argc, char* argv[] )
{
   double ref_time = get_time();

   // Program initialization
   synthetic_init();
 #pragma omp parallel 
{ 
   // (3) Independant phases
  // int id = omp_get_thread_num();
#pragma omp sections
    {
        #pragma omp section
{
   //if(id == 0 ) 
   synthetic_phase1(); }

   //if(id == 1 ) 
 #pragma omp section
{  synthetic_phase2();
 }  //if(id == 2 ) 
  #pragma omp section
{ synthetic_phase3();
}
}
} 

/*
#pragma omp parallel 
{
   // (3) Independant phases
    int id = omp_get_thread_num();
      if(id == 0 )  synthetic_phase1(); 
      if(id == 1 || omp_get_num_threads() < 2)  synthetic_phase2();
      if(id == 2 || omp_get_num_threads() < 3 && id == 0)  synthetic_phase3();
                               
                               
                               } */
   // Program check results
   synthetic_check();

   double total = get_time() - ref_time;

   // Execution summary (print)
   print_results (argv[0], VERSION, threads(), time, PHASES, total, test );

   return 0;
}
