#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <omp.h>

#include "util.h"

// Taken from https://en.wikipedia.org/wiki/Counting_sort, adapted for parallelization
int *counting_sort(int *list, size_t N, int keys) {
  int num_threads = omp_get_max_threads();
  int **thread_counters = create_matrix(num_threads, keys);

  int numbers_per_thread = N / num_threads;

  // Count in parallel
  #pragma omp parallel num_threads(num_threads) 
  {
    int iam = omp_get_thread_num();
    int *count = thread_counters[iam];

    int start = iam * numbers_per_thread;
    int end = start + numbers_per_thread;
    int i;
    for (i = start; i < end; i++) {
      count[list[i]%keys]++;
    }
  }

  int total = 0;
  int old_count;
  int i_out, j_out;
  // Not parallel, because there are "only" keys * num_threads iterations
  for (i_out = 0; i_out < keys; ++i_out) {
    for (j_out = 0; j_out < num_threads; j_out++) {
          old_count = thread_counters[j_out][i_out];
	  thread_counters[j_out][i_out] = total;
	  total += old_count;
    }
  }

  // Sort in parallel
  int *sortedList = malloc(N*sizeof(int));
  #pragma omp parallel num_threads(num_threads)
  {
    int iam = omp_get_thread_num();
    int *count = thread_counters[iam];

    int start = iam * numbers_per_thread;
    int end = start + numbers_per_thread;
    int i;
    for (i = start; i < end; ++i) {
      sortedList[count[list[i]%keys]] = list[i];
      count[list[i]%keys] += 1;
    }
  }

  free(list);
  return sortedList;
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

  // Run counting sort and measure time
  double begin = omp_get_wtime();
  list = counting_sort(list, N, RANGE_MAX);
  double end = omp_get_wtime();
  printf("Time spent: %fs\n", end-begin);

  // Print list after sorting
  if (argc == 3) {
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
