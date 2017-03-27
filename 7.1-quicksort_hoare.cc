#include "std.h"

static size_t hoare_partition(array &A, size_t p, size_t r) {
  size_t i = p - 1, j = r + 1;
  while (1) {
    do {
      --j;
    } while (!(A[j] <= A[p]));
    do {
      i++;
    } while (!(A[i] >= A[p]));
    if (i < j)
      std::swap(A[i], A[j]);
    else
      return j;
  }
}

static void quicksort_hoare(array &A, size_t p, size_t r) {
  if (p < r) {
    size_t q = hoare_partition(A, p, r);
    quicksort_hoare(A, p, q);
    quicksort_hoare(A, q + 1, r);
  }
}

void quicksort_hoare(array &A) {
  quicksort_hoare(A, 1, A.length);
}

