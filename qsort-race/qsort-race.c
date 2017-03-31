
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>

int* max(int* a, int* b) {
  if(*a > *b)
    return a;
  else
    return b;
}

// Use the Quick Sort algorithm, implemented using recursive divide and
// conquer.  This function is NOT the same as the Standard C Library qsort()
// function.  This implementation uses Cilk Plus, and has a race condition that
// Cilkscreen will detect.
void my_qsort(int* begin, int* end) {
  if (begin >= end - 1) {
    return;
  }


  // Perform a partition on the first element of the array
  // so that the left consists of elements less than 'begin'
  // and the right consists of elements greater than 'begin'
  int* scan = begin+1;
  int* swap = end;

  while (scan < swap) {
    if (*scan > *begin) {
      swap--;
      int tmp = *swap;
      *swap = *scan;
      *scan = tmp;
    }
    else {
      scan++;
    }
  }

  int* middle = swap - 1;  // Last element of left partition.

  // Swap the element we partitioned on into the middle.
  int tmp = *begin;
  *begin = *middle;
  *middle = tmp;

  // Recurse on the left and right partitions.
  my_qsort(begin, middle);
  my_qsort(max(begin + 1, middle), end);
}

// A simple test harness
int qmain(int n, int iteration) {
  int* a = (int *)malloc(sizeof(int)*n);

  // Fill the array with "random" data
  srand(iteration+1);
  int i;
  for (i = 0; i < n; ++i) {
    a[i] = rand();
  }

  // Do the sort
  my_qsort(a, a + n);

  int sorted = 1;
  for (i = 1; i < n; i++) {
    if (a[i] < a[i-1]) {
      printf("Iteration %d: Error - arrays not sorted at position i=%d: a[i-1]=%d, a[i]=%d.\n", iteration, i, a[i-1], a[i]);
      sorted = 0;
      break;
    }
  }

  if (sorted == 1) {
    printf("Iteration %d: Arrays sorted.\n", iteration);
  }

  free(a);

  return 0;
}


int main(int argc, char* argv[]) {
  int n = 10;
  int iteration_count = 1;
  if (argc > 2) {
    n = atoi(argv[1]);
    if (n > 10000) {
      n = 10000;
      printf("Maximum array size is 10000 \n");
    }
    iteration_count = atoi(argv[2]);
  } else {
    printf("usage ./qsort-race <array_size> <iteration_count>\n");
    return 0;
  }
  int i;
  for (i = 0; i < iteration_count; i++) {
    qmain(n, i);
  }

  return 0;
}
