#ifndef _PRECISION_H_
#define _PRECISION_H_

// Configuration depending on floating point precision:
// simple (comment next line) or double (uncomment next line)
//#define DP

// Uncomment for integer
//#define VALS_INT


// Define floating point precision: simple (float) or double (double)
#ifdef DP
#ifdef VALS_INT
#define REAL long long
#error "Check printfs, as currently long long is not really supported"
#else
#define REAL double
#endif
#else
#ifdef VALS_INT
#define REAL int
#else
#define REAL float
#endif
#endif


// Determine which CBLAS/CUBLAS library functions must be called according to floating point precision
#ifdef DP
#define cublas_gemm cublasDgemm_v2
#define cblas_gemm  cblas_dgemm
#else
#define cublas_gemm cublasSgemm_v2
#define cblas_gemm  cblas_sgemm
#endif

#endif //_PRECISION_H_

