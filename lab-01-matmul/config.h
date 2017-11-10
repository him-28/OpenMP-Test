#ifndef _CONFIG_H_
#define _CONFIG_H_

// General configuration file

// Matrix block size will be BSIZExBSIZE
#define BSIZE 64
//#define BSIZE 128
// Other examples are:
//#define BSIZE 512
//#define BSIZE 2048
//#define BSIZE 4096

// Uncomment if cblas is not available... change also the Makefile appropriately
//#define CBLAS_GEMM

// Uncomment next line to allocate host memory through Nanos++ runtime to enhance 
// memory transfers between host and device memory spaces (comment next line to 
// use regular malloc() and free() functions
//#define USE_PINNED

#ifdef USE_PINNED
#define malloc nanos_malloc_pinned_cuda
#define free nanos_free_pinned_cuda
#endif


// Uncomment next line to initialize data in parallel (through task creation)
//#define INIT_TASKS


// Uncomment next line to check for kernel errors after each kernel launch
// (makes the application run slower)
// #define SAFE


#endif // _CONFIG_H_

