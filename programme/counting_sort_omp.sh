#!/bin/bash

if [ $# -ne 2 ]; then
	echo "usage: $0 nprocs problem-size"
	exit 1
fi

nprocs=$1
problemsize=$2

qsub -cwd \
     -o "counting_sort_omp_${nprocs}_${problemsize}.dat" \
     -e "counting_sort_omp_${nprocs}_${problemsize}.dat" \
     -N "counting_sort_omp" \
     -pe openmp $nprocs \
     -b y \
     "export OMP_NUM_THREADS=$nprocs && module load intel/13.0 && ./counting_sort_omp $problemsize"
