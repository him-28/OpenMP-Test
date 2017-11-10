#include "matrix_init.h"
#include "matrix_main.h"

void matrix_2D_init_val ( double *A, int size, double value )
{
   int i,j; // loop index variables

   // Initializing matrix elements with value
   for ( i = 0; i < size; i++ )
   {
      for ( j = 0; j < size; j++ )
      {
         A[i*size+j] = value;
      }
   }
}

void matrix_2D_init_row ( double *A, int size )
{
   int i,j; // loop index variables

   // Initializing matrix elements with its row value
   for ( i = 0; i < size; i++ )
   {
      for ( j = 0; j < size; j++ )
      {
         A[i*size+j] = i;
      }
   }
}

void matrix_2D_init_col ( double *A, int size )
{
   int i,j; // loop index variables

   // Initializing matrix elements with its col value
   for ( i = 0; i < size; i++ )
   {
      for ( j = 0; j < size; j++ )
      {
         A[i*size+j] = j;
      }
   }
}
