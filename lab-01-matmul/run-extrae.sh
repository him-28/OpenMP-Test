#!/bin/bash

export OMP_NUM_THREADS=4
export EXTRAE_CONFIG_FILE=extrae.xml

./matmul.extrae 1
