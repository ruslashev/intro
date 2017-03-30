#include "std.h"

static size_t partition(array &A, size_t p, size_t r) {
  size_t i = p;
  for (size_t j = p; j <= r - 1; ++j)
    if (A[j] <= A[r])
      std::swap(A[i++], A[j]);
  std::swap(A[i], A[r]);
  return i;
}

static size_t randomized_partition(array &A, size_t p, size_t r) {
  size_t i = rand_in_range(p, r);
  std::swap(A[i], A[r]);
  return partition(A, p, r);
}

static void randomized_quicksort(array &A, size_t p, size_t r) {
  if (p < r) {
    size_t q = randomized_partition(A, p, r);
    randomized_quicksort(A, p, q - 1);
    randomized_quicksort(A, q + 1, r);
  }
}

void randomized_quicksort(array &A) {
  randomized_quicksort(A, 1, A.length);
}

