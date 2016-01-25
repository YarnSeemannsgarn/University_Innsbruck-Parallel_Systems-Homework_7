#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"

// List helpers
void print_list(int *list, size_t N) {
  int i;
  for (i = 0; i < N; ++i) {
    printf("%i, ", list[i]);
  }
  printf("\n\n");
}
