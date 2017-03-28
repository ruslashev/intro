#include "std.h"

static size_t partition(array &A, size_t p, size_t r) {
  size_t i = p - 1;
  for (size_t j = p; j <= r - 1; ++j)
    if (A[j] <= A[r]) {
      ++i;
      std::swap(A[i], A[j]);
    }
  std::swap(A[i + 1], A[r]);
  return i + 1;
}

static size_t randomized_partition(array &A, size_t p, size_t r) {
  size_t i = rand_in_range(p, r);
  std::swap(A[i], A[r]);
  return partition(A, p, r);
}

static int randomized_select_iterative(array A, size_t p, size_t r, size_t i) {
  while (p < r) {
    size_t q = randomized_partition(A, p, r);
    size_t k = q - p + 1;
    if (i == k)
      return A[q];
    else if (i < k)
      r = q - 1;
    else {
      p = q + 1;
      i = i - k;
    }
  }
  return A[p];
}

int randomized_select_iterative(array A, size_t i) {
  return randomized_select_iterative(A, 1, A.length, i);
}

