#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#include "util.h"

// Bucket structure
struct bucket_t {
  int *values;
  int counter;
};

// For quicksort
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

// Construckt buckets
// Algorithm from https://en.wikipedia.org/wiki/Bucket_sort#Pseudocode
struct bucket_t *construct_buckets(int *list, size_t N, int bucket_count) {
  struct bucket_t *buckets = malloc(sizeof(struct bucket_t) * bucket_count);
  int i;
  for (i = 0; i < bucket_count; ++i) {
    buckets[i].values = malloc(N * sizeof(int)); // allocate initial list size memory for each bucket, 
                                              // because one bucket could contain all values... 
                                              // can be optimized with linked list, but than the sorting is
                                              // more complicated
    if (buckets[i].values == NULL) {
      fprintf(stderr, MEMORY_MESSAGE);
      return NULL;
    }
    buckets[i].counter = 0;
  }
  
  // Scatter: Go over the original array, putting each object in its bucket.
  struct bucket_t *current_bucket;
  int bucket_size = (int) ceil(((double) RANGE_MAX) / ((double) bucket_count));
  int *elem;
  for (i = 0; i < N; ++i) {
    elem = &list[i];
    current_bucket = &buckets[*elem / bucket_size];
    current_bucket->values[current_bucket->counter] = *elem;
    current_bucket->counter++;
  }

  return buckets;
}


int main(int argc, char *argv[]) {
  // Handle parameter
  if (argc != 2 && argc != 3) {
    fprintf(stderr, USAGE_MESSAGE, argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // Create and initialise list
  int *list = (int *) malloc(N * sizeof(int));
  if (list == NULL) {
    fprintf(stderr, MEMORY_MESSAGE);
    return EXIT_FAILURE;
  }
  int i;
  srand48(time(NULL));
  for (i = 0; i < N; ++i) {
    list[i] = lrand48() % RANGE_MAX;
  }

  // Print list before sorting
  if (argc == 3) {
    printf("List before sorting:\n");
    print_list(list, N);
  }

  int *sortedList = malloc(N*sizeof(int));

  // Run bucket sort and measure time
  double begin = omp_get_wtime();
  int bucket_count = omp_get_max_threads();
  struct bucket_t *buckets = construct_buckets(list, N, bucket_count);
  #pragma omp parallel num_threads(bucket_count)
  {
    int iam = omp_get_thread_num();
    qsort(buckets[iam].values, buckets[iam].counter, sizeof(int), cmpfunc);

    // Calculate start in list
    int offset = 0;
    int i_par;
    for (i_par = 0; i_par < iam; i_par++) {
      offset += buckets[i_par].counter;
    }
    
    for (i_par = 0; i_par < buckets[iam].counter; i_par++) {
      sortedList[offset] = buckets[iam].values[i_par];
      offset++;
    }
  }

  double end = omp_get_wtime();
  printf("Time spent: %fs\n", end-begin);

  // Print list after sorting
  if (argc == 3) {
    printf("\nList after sorting:\n");
    print_list(sortedList, N);
  }

  // Check list
  if (checkSortedList(sortedList, N) == 1) {
    fprintf(stderr, "List was not sorted correctly!\n");
    free(list);
    free(sortedList);
    return EXIT_FAILURE;
  }

  // Free memory
  free(list);
  free(sortedList);

  return EXIT_SUCCESS;
}
