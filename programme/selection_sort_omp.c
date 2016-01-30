#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "util.h"

// Works since OpenMP 4.0
struct Compare { int val; int index; };
#pragma omp declare reduction(maximum : struct Compare : omp_out = omp_in.val > omp_out.val ? omp_in : omp_out)

void selection_sort_parallel(int* list, int size) {
  int i;
  for (i = size - 1; i > 0; --i) {
    struct Compare max;
    max.val = list[i];
    max.index = i;
    int j;

    #pragma omp parallel for reduction(maximum:max)
    for (j = i - 1; j >= 0; --j) {
      if (list[j] > max.val) {
	max.val = list[j];
	max.index = j;
      }
    }
    
    if (i != max.index) {
      int tmp = list[i];
      list[i] = max.val;
      list[max.index] = tmp;
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
