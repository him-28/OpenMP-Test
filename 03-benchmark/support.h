#ifndef __SUPPORT_H
#define __sUPPORT_H

#define VERSION "initial"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_headers(int n);
void print_results(const char* program, const char* version, int threads, double *times, int n, double total, int *test );
void print_matrix ( double *Matrix, int size );

int check_matrix_result ( double *M, int size );
int check_matrix_value_row ( double *M, int size );
int check_matrix_value_col ( double *M, int size );

double get_time(void);

double compute ( int i, int j, int size);

#endif
