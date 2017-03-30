#include "std.h"

void k_closest_to_median(array A, size_t k) {
  int median = select(A, A.length / 2);
  array B = A;
  for (size_t i = 1; i <= A.length; ++i) {
    B[i] -= median;
    B[i] *= B[i] < 0 ? -1 : 1;
  }
  int max = select(B, k);
  for (size_t i = 1; i <= A.length; ++i)
    if (B[i] <= max)
      printf("%d\n", A[i]);
}

