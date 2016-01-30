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


Measurements (Task 5)
=====================

Host machine: LCC Cluster with 5 nodes, where each node contains 8 CPUs
Measurement technique: omp_get_wtime function

Programme: bubble_sort_omp with problem size 1000000

Nprocs | Runtime (in s) | Speedup | Efficency
:------|----------------|--------:|----------:
1      |        1549.72 |       - |         
2      |         774.53 |      		  |
4      |         479.26 |      |      
8      |         288.17 |      |

Programme: selection_sort_omp with problem size 1000000
This runtimes for this programme were measured under a different system, because the lcc cluster does not have a compiler which supports OpenMP4.0 (gcc, icc and pgcc have not the needed version).
More information: http://openmp.org/wp/openmp-compilers/
Used host machine: single machine with 4 CPUs

Nprocs | Runtime (in s) | Speedup | Efficency
:------|----------------|--------:|----------:
1      |         727.84 |       - |         -
2      |         366.66 |    1.99 |      0.99
4      |         187.77 |    3.88 |      0.97      
8      |         389.74 |    1.87 |	 0.23

Because the machine has only 4 CPUs, the efficency for 8 threads is lower than the efficency of 2 and 4 threads. Still there is a recognizable speedup.