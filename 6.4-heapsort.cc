#include "std.h"

static size_t left(size_t i) {
  return 2 * i;
}

static size_t right(size_t i) {
  return 2 * i + 1;
}

static void max_heapify(array &A, size_t &heap_size, size_t i) {
  while (i < heap_size) {
    size_t l = left(i), r = right(i), largest;
    if (l <= heap_size && A[l] > A[i])
      largest = l;
    else
      largest = i;
    if (r <= heap_size && A[r] > A[largest])
      largest = r;
    if (largest != i) {
      int t = A[i];
      A[i] = A[largest];
      A[largest] = t;
      i = largest;
    } else
      break;
  }
}

static void build_max_heap(array &A, size_t &heap_size) {
  heap_size = A.length;
  for (size_t i = heap_size / 2; i >= 1; --i)
    max_heapify(A, heap_size, i);
}

void heapsort(array &A) {
  size_t heap_size;
  build_max_heap(A, heap_size);
  for (size_t i = A.length; i >= 2; --i) {
    std::swap(A[1], A[i]);
    --heap_size;
    max_heapify(A, heap_size, 1);
  }
}

