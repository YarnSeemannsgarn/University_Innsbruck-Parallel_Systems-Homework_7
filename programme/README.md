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
