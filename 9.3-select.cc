#include "std.h"

static int median5(array &A, size_t p, size_t r) {
  for (size_t j = p; j <= r; ++j) {
    int key = A[j];
    size_t i = j - 1;
    while (i >= p && key < A[i]) {
      A[i + 1] = A[i];
      --i;
    }
    A[i + 1] = key;
  }
  size_t n = r - p + 1;
  return n % 2 == 0 ? A[p + n / 2 - 1] : A[p + n / 2];
}

int select(array &A, size_t p, size_t r, size_t i) {
  size_t n = r - p + 1, j;
  array medians((n + 4) / 5);
  for (j = 1; j <= n / 5; ++j)
    medians[j] = median5(A, p + (j - 1) * 5, p + (j - 1) * 5 + 4);
  if (n % 5 != 0)
    medians[j] = median5(A, p + (j - 1) * 5, p + (j - 1) * 5 + n % 5 - 1);

  int x = medians.length == 1 ? medians[1]
    : select(medians, 1, medians.length, medians.length / 2);

  size_t k = 0;
  for (size_t j = p, l = p; j <= r; ++j)
    if (A[j] <= x)
      std::swap(A[l++], A[j]), ++k;

  if (i == k)
    return x;
  else if (i < k)
    return select(A, p, p + k - 1, i);
  else
    return select(A, p + k, r, i - k);
}

int select(array A, size_t i) {
  return select(A, 1, A.length, i);
}

