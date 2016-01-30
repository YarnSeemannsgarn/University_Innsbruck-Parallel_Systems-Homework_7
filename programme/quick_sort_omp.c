#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "util.h"

// https://en.wikipedia.org/wiki/Quicksort
void quicksort(int *begin, int *end) {
  int *ptr;
  int *split;
  if (end - begin <= 1) {
    return;
  }

  ptr = begin;
  split = begin + 1;
  while (++ptr <= end) {
    if (*ptr < *begin) {
      swap(ptr, split);
      ++split;
    }
  }
  
  swap(begin, split - 1);
  
  #pragma omp parallel sections
  {
    #pragma omp section
    quicksort(begin, split - 1);
    #pragma omp section
    quicksort(split, end);
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
  if(list == NULL){
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

  // Run quick sort and measure time
  double begin = omp_get_wtime();
  quicksort(&list[0], &list[N-1]);
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
