# Do not make selection_sort on lcc, because it uses stuff from OpenMP 4.0
# The gcc, pgcc and icc versions on lcc are not up to date enough to compile it
# See http://openmp.org/wp/openmp-compilers/

CC=gcc
CFLAGS=-O2 -fopenmp
SOURCES=wrong_bubble_sort_omp.c bubble_sort_omp.c counting_sort_omp.c bucket_sort_omp.c quick_sort_omp.c util.c # selection_sort_omp.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLES=wrong_bubble_sort_omp bubble_sort_omp counting_sort_omp bucket_sort_omp quick_sort_omp # selection sort

all: $(EXECUTABLES)

wrong_bubble_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) wrong_bubble_sort_omp.o util.o -o $@

bubble_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) bubble_sort_omp.o util.o -o $@

counting_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) counting_sort_omp.o util.o -o $@

bucket_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) bucket_sort_omp.o util.o -o $@ -lm

selection_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) selection_sort_omp.o util.o -o $@

quick_sort_omp: $(OBJECTS)
	$(CC) $(CFLAGS) quick_sort_omp.o util.o -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLES) $(OBJECTS) 
