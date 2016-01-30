#!/bin/bash

if [ $# -ne 2 ]; then
	echo "usage: $0 nprocs problem-size"
	exit 1
fi

nprocs=$1
problemsize=$2

qsub -cwd \
     -o "bucket_sort_omp_${nprocs}_${problemsize}.dat" \
     -e "bucket_sort_omp_${nprocs}_${problemsize}.dat" \
     -N "bucket_sort_omp" \
     -pe openmp $nprocs \
     -b y \
     "export OMP_NUM_THREADS=$nprocs && ./bucket_sort_omp $problemsize"
