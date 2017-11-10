#include <stdio.h>
#include <stdlib.h>
#include "matrix_list.h"
#include "matrix_main.h"

typedef struct mlist_s {
   struct mlist_s *next;
   double *tile;
   int ti;
   int tj;
} mlist_t;


void matrix_2D_tile_multiply ( double *A, double *B, double *C, int size)
{
   int i,j,k;

   for(i=0;i<size;i++) {
      for(j=0;j<size;j++) {
         for( k=0;k<size;k++) {
            A[i*size+j] = A[i*size+j] + B[i*size+k]*C[k*size+j];
         }
      }
   }
}

mlist_t * matrix_2D_list_allocate ( int NT, int TS )
{
   mlist_t  *first   = 0;
   mlist_t **current = &first;

   int ti = 0; int tj = 0;
   while ( ti < NT ) {
      (*current) = (mlist_t *) malloc(sizeof(mlist_t));
      (*current)->tile = malloc(TS*TS*sizeof(double));
      (*current)->ti = ti;
      (*current)->tj = tj;
      tj++;
      if (tj == NT ) { ti++; tj=0; }
      current = &(*current)->next;
   }

   (*current) = 0;
   return first;
}

mlist_t * matrix_2D_list_find ( mlist_t *node, int i, int j )
{
   while ( node && !(node->ti == i && node->tj == j) ) {
      node = node->next;
   }
   return node;
}

void matrix_2D_to_tiles ( mlist_t *node, int TS, double *M, int size )
{
   int i,j;

   for (i = 0; i<TS; i++ )
   {
      for (j = 0; j<TS; j++ )
      {
         node->tile[i*TS+j] = M[((node->ti*TS)+i)*size+(node->tj*TS)+j];
      }
   }
}

void matrix_2D_from_tiles ( mlist_t *node, int TS, double *M, int size )
{
   int i,j;

   for (i = 0; i<TS; i++ )
   {
      for (j = 0; j<TS; j++ )
      {
         M[((node->ti*TS)+i)*size+(node->tj*TS)+j] = node->tile[i*TS+j];
      }
   }
}

void matrix_list_compute ( double *A, double *B, double *C, int size )
{
   int NT = 4, TS = size/4;
   int i, j, k;
   mlist_t *mlist_A = 0;
   mlist_t *mlist_B = 0;
   mlist_t *mlist_C = 0;
 
   // Matrix List: allocate
   mlist_A = matrix_2D_list_allocate(NT,TS);
   mlist_B = matrix_2D_list_allocate(NT,TS);
   mlist_C = matrix_2D_list_allocate(NT,TS);

   mlist_t *cA = mlist_A;
   mlist_t *cB = mlist_B;
   mlist_t *cC = mlist_C;

   // Matrix List: copy values from matrix to tiles
   while ( cA ) {
      matrix_2D_to_tiles(cA, TS, A, size);
      cA = cA->next;
   }
   // Matrix List: copy values from matrix to tiles
   while ( cB ) {
      matrix_2D_to_tiles(cB, TS, B, size);
      cB = cB->next;
   }

   // Matrix List: copy values from matrix to tiles
   while ( cC ) {
      matrix_2D_to_tiles(cC, TS, C, size);
      cC = cC->next;
   }

   // Matrix List: compute matrix multiplication 
      i = 0;
      while ( i < NT )
      {
         j = 0;
         while ( j < NT )
         {
            mlist_t *tmpA = matrix_2D_list_find(mlist_A, i, j);
            double *tileA = tmpA->tile;

            k = 0;
            while  ( k < NT ) {
               mlist_t *tmpB = matrix_2D_list_find(mlist_B, i, k);
               double *tileB = tmpB->tile;
               mlist_t *tmpC = matrix_2D_list_find(mlist_C, k, j);
               double *tileC = tmpC->tile;
               matrix_2D_tile_multiply(tileA, tileB, tileC, TS);
               k++;
            }
            j++;
         }
         i++; 
      }

   // Matrix List: copy result from tiles to matrix
   cA = mlist_A;
   while ( cA ) {
      matrix_2D_from_tiles(cA, TS, A, size);
      cA = cA->next;
   }
   
   
}
