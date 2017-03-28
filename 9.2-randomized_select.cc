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

static int randomized_select(array A, size_t p, size_t r, size_t i) {
  if (p == r)
    return A[p];
  size_t q = randomized_partition(A, p, r);
  size_t k = q - p + 1;
  if (i == k)
    return A[q];
  else if (i < k)
    return randomized_select(A, p, q - 1, i);
  else
    return randomized_select(A, q + 1, r, i - k);
}

int randomized_select(array A, size_t i) {
  return randomized_select(A, 1, A.length, i);
}

