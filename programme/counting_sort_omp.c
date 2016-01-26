#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <omp.h>

#include "util.h"

// https://en.wikipedia.org/wiki/Counting_sort
int *counting_sort(int *list, size_t N, int keys) {
  /* TODO
  int nthreads = omp_get_max_threads();
  int **thread_counters = create_matrix(nthreads, keys);
  */

  int *count = calloc(keys, sizeof(int));
  
  int i;
  for (i = 0; i < N; ++i) {
    count[list[i]%keys] += 1;
  }

  int total = 0;
  int old_count;
  for (i = 0; i < keys; ++i) {
    old_count = count[i];
    count[i] = total;
    total += old_count;
  }

  int *sortedList = malloc(N*sizeof(int));
  for (i = 0; i < N; ++i) {
    sortedList[count[list[i]%keys]] = list[i];
    count[list[i]%keys] += 1;
  }

  free(count);
  free(list);
  return sortedList;
}

// Part of counting sort
int *count_elements(int *list, size_t N, int keys){
  int *count = calloc(keys, sizeof(int));
  
  int i;
  for(i=0; i<N; ++i){
    count[list[i]%keys] += 1;
  }

  return count;
}


int main(int argc, char *argv[]) {
  // Handle parameter
  if(argc != 2 && argc != 3){
    fprintf(stderr, USAGE_MESSAGE, argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // Create and initialise list
  int *list = (int *) malloc(N * sizeof(int));
  if(list == NULL) {
    fprintf(stderr, MEMORY_MESSAGE);
    return EXIT_FAILURE;
  }
  int i;
  srand48(time(NULL));
  for(i=0; i<N; ++i) {
    list[i] = lrand48() % RANGE_MAX;
  }

  // Print list before sorting
  if (argc == 3) {
    printf("List before sorting:\n");
    print_list(list, N);
  }

  // Run counting sort and measure time
  double begin = omp_get_wtime();
  list = counting_sort(list, N, RANGE_MAX);
  double end = omp_get_wtime();
  printf("Time spent: %fs\n", end-begin);

  // Print list after sorting
  if(argc == 3) {
    printf("\nList after sorting:\n");
    print_list(list, N);
  }

  // Check list
  if (checkSortedList(list, N) == 1) {
    fprintf(stderr, "List was not sorted correctly!\n");
    free(list);
    return EXIT_FAILURE;
  }

  // Free memory
  free(list);

  return EXIT_SUCCESS;
}
