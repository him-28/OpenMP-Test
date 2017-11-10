#!/bin/bash

export OMP_NUM_THREADS=8
export EXTRAE_CONFIG_FILE=extrae.xml

./heat-omp.extrae test512-jacobi-small.dat test512-jacobi-8.ppm
