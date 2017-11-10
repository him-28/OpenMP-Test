./matrix-head

export OMP_NUM_THREADS
for OMP_NUM_THREADS in `seq 1 8`; do
./matrix-par
done

./matrix-seq
