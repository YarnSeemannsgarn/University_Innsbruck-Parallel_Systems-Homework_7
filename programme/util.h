#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdio.h>

#define RANGE_MAX 10000
#define MEMORY_MESSAGE "Not enough memory. Choose a smaller problem size!\n"
#define USAGE_MESSAGE "Usage: %s <problem-size> [<debug>]\n"

// list helpers
void print_list(int *list, size_t N);
int checkSortedList(int *list, size_t N);

// matrix for parallel counting sort
int **create_matrix(size_t M, size_t N);
void destroy_matrix(int **matrix);

#endif
