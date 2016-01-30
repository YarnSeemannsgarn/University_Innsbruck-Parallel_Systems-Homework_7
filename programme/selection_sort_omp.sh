#!/bin/bash

if [ $# -ne 2 ]; then
	echo "usage: $0 nprocs problem-size"
	exit 1
fi

nprocs=$1
problemsize=$2

qsub -cwd \
     -o "selection_sort_omp_${nprocs}_${problemsize}.dat" \
     -e "selection_sort_omp_${nprocs}_${problemsize}.dat" \
     -N "selection_sort_omp" \
     -pe openmp $nprocs \
     -b y \
     "export OMP_NUM_THREADS=$nprocs && ./selection_sort_omp $problemsize"
