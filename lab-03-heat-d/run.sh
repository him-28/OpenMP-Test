#!/bin/bash

export OMP_NUM_THREADS=8

./heat-omp test512-jacobi-small.dat test512-jacobi-8.ppm
