#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "util.h"

// https://en.wikipedia.org/wiki/Selection_sort#Implementation
// Adapted for parallelization
void selection_sort_parallel(int *list, size_t N) {
  int i, j, iMin;
  for (j = 0; j < N-1; ++j){
    iMin = j;
    #pragma omp parallel for reduction(min: iMin)
    for (i = j + 1; i < N; ++i) {
      if (list[i] < list[iMin]) {
	iMin = i;
      }
    }

    if (iMin != j) {
      swap(&list[j], &list[iMin]);
    }
  }
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
  for (i=0; i<N; ++i) {
    list[i] = lrand48() % RANGE_MAX;
  }

  // Print list before sorting
  if (argc == 3) {
    printf("List before sorting:\n");
    print_list(list, N);
  }

  // Run bubble sort and measure time
  double begin = omp_get_wtime();
  selection_sort_parallel(list, N);
  double end = omp_get_wtime();
  printf("Time spent: %fs\n", end-begin);

  // Print list after sorting
  if(argc == 3){
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
