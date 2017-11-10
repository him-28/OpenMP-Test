#ifndef _SUPPORT_H
#define _SUPPORT_H

#define GRAIN  1

#define SIZE 512
#define PHASES 4

#if defined (_OPENMP)
#  include <omp.h>
#  define threads() omp_get_max_threads()
#else
#  define threads()             1
#  define omp_get_num_threads() 1
#  define omp_get_max_threads() 1
#  define omp_get_thread_num()  0
#endif

#endif
