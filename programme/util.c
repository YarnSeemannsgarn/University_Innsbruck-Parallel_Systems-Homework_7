#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"

// List helpers
void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void print_list(int *list, size_t N) {
  int i;
  for (i = 0; i < N; ++i) {
    printf("%i, ", list[i]);
  }
  printf("\n\n");
}

int checkSortedList(int *list, size_t N) {
  int i;
  for (i = 0; i < N-1; i++) {
    if (list[i] > list[i+1]) {
      return 1;
    }
  }
  return 0;
}

// Matrix for parallel counting sort
int **create_matrix(size_t M, size_t N) {
    int *values = calloc(M * N, sizeof(int));
    int **rows = malloc(M * sizeof(int *));
    int i;
    for (i=0; i<M; ++i)
    {
        rows[i] = values + i*N;
    }
    return rows;
}

void destroy_matrix(int **matrix) {
    free(*matrix);
    free(matrix);
}
