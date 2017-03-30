#include "std.h"

static size_t partition(array &A, size_t p, size_t r) {
  size_t i = p;
  for (size_t j = p; j <= r - 1; ++j)
    if (A[j] <= A[r])
      std::swap(A[i++], A[j]);
  std::swap(A[i], A[r]);
  return i;
}

static void quicksort(array &A, size_t p, size_t r) {
  if (p < r) {
    size_t q = partition(A, p, r);
    quicksort(A, p, q - 1);
    quicksort(A, q + 1, r);
  }
}

void quicksort(array &A) {
  quicksort(A, 1, A.length);
}

