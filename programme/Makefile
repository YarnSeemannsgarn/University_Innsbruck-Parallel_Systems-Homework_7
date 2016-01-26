# Use intel compiler (13.0), because it supports OpenMP 3.1,
# which is necessary in selection_sort_omp for min reduction

CC=icc
CFLAGS=-O2 -openmp
SOURCES=wrong_bubble_sort_omp.c bubble_sort_omp.c counting_sort_omp.c bucket_sort_omp.c selection_sort_omp.c util.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLES=wrong_bubble_sort_omp bubble_sort_omp counting_sort_omp bucket_sort_omp selection_sort_omp

all: $(EXECUTABLES)

wrong_bubble_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) wrong_bubble_sort_omp.o util.o -o $@

bubble_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) bubble_sort_omp.o util.o -o $@

counting_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) counting_sort_omp.o util.o -o $@

bucket_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) bucket_sort_omp.o util.o -o $@ -lm

selection_sort_omp:  $(OBJECTS)
	$(CC) $(CFLAGS) selection_sort_omp.o util.o -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLES) $(OBJECTS) 
