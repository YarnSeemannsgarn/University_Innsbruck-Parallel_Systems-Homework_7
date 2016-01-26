Requirements
============

Intel Compiler 13.0 for support of OpenMP 3.1,
which is necessary in selection_sort_omp for min reduction

How to run the programme/s
==========================

First of all build all programmes:

    $ make
    
Afterwards you can run the programme (e.g. bubble_sort_omp) with n threads (e.g. 4) locally as follows:

    $ export OMP_NUM_THREADS=4
    $ ./bubble_sort_omp <problem-size>
    
If you want to submit a job (e.g. counting_sort) you have to run the appropriate script:

    $ ./counting_sort_omp.sh <nprocs> <problem-size>
    
If you want to clean up just do:

    $ make clean
    
Wrong bubble sort (Task 1)
==========================

The proposed paralellization does not work properly for multiple threads, because the swapping of two neighboured numbers in the loop affect the result of the next loop.

An Example from the run:

    $ export OMP_NUM_THREADS=2
    $ ./wrong_bubble_sort 10 debug

    List before sorting:
    521, 9574, 5762, 9970, 8532, 8816, 6873, 72, 6294, 7289, 

    Time spent: 0.000147s

    List after sorting:
    521, 5762, 6294, 6873, 6873, 7289, 8532, 8816, 9574, 9970,

The number 72 is not in the sorted list, but the number 6873 is there twice, although there is only one ocassion of it in the original list. This is because the first swap gets affected by another loop iteration.

### TO BE CHANGED ###

Host machine: LCC Cluster with 5 nodes, where each node contains 8 CPUs
Measurement technique: omp_get_wtime function

Programme: matrix_multiplication with problem size 2000\*2000\*2

Nprocs | Runtime OMP/MPI (in s) | Speedup OMP/MPI | Efficency OMP/MPI
:------|-----------------------:|----------------:|-----------------:
1      |          53.55 / 91.09	|               - |                 -
2      |          35.94 / 46.59 |     1.49 / 1.96 |       0.74 / 0.98
4      |          24.78 / 23.96 |     2.16 / 3.80 |       0.54 / 0.95      
8      |          18.57 / 12.80 |     2.89 / 7.11 |       0.36 / 0.89

The omp runtime for one thread is much smaller than the mpi runtime, even though both implementations use 
the same matrix multiplication algorithm. This difference could be due to the mpi overhead, which is of 
course unnecessary for the one thread version, because it could be done with a pure sequential algorithm.
Both implementation runtimes decrease with the increase of the number of nprocs, while the speedup and 
efficency is much better for the mpi variant. This could mean, that the mpi parallelisation is better/more
effective. For 4 threads the runtime is nearly the same and for 8 threads the mpi runtime "superseeds"
the omp runtime.


Programme: sieve_of_erastothenes with problem size 1000000000

Nprocs | Runtime OMP/MPI (in s) | OMP/MPI Speedup | OMP/MPI Efficency
:------|-----------------------:|----------------:|-----------------:
1      |        429.22 / 143.72 |               - |                 -
2      |        292.29 /  78.89 |     1.47 / 1.82 |       0.73 / 0.91
4      |        258.14 /  38.97 |     1.66 / 3.69 |	  0.41 / 0.92
8      |        124.13 /  30.59 |     3.46 / 4.70 |       0.43 / 0.59

The omp runtime for one thread in this case is much higher than the mpi runtime for one thread. I could
not figure out exactly, why there was such a big difference, because the algorithms are pretty similiar.
I guess the measurement technique for mpi (clock function) should have been replaced by the mpi function 
MPI_Wtime. Maybe also the compiler optimization is better for mpi in this case. The efficencies also are
better for the mpi variant. I tried different pragma placements for the omp version, but there was no 
better result than this.


Programme: dijkstra with problem size 8000 (nodes)

Nprocs | Runtime OMP/MPI (in s) | OMP/MPI Speedup | OMP/MPI Efficency
:------|-----------------------:|----------------:|-----------------:
1      |        1969.99 /  0.75 |               - |                 -
2      |        1343.12 / 19.40 |     1.47 / 0.04 |       0.73 / 0.02  
4      |         977.25 / 18.82 |     2.02 / 0.04 |	  0.50 / 0.01
8      |         489.48 / 17.93 |     4.02 / 0.04 |	  0.50 / 0.01

As mentioned in homework 3, my mpi parallelisation for dijkstra is not efficient at all. For the omp vari-
ant I used the alorithm exactly described by https://en.wikipedia.org/wiki/Dijkstra's_algorithm#Algorithm.
That's why it is probably slower than the mpi version for one thread. Of course the difference here is enor-
mous. Still the parallelisation at least works, even if the 8 thread omp variant is much slower than the
1 thread mpi version.

All in all the matrix_multiplication is for me the best comparable case, because the implementations of the 
algorithms are the most similiar and the speedups and efficencies are the most comprehensible.