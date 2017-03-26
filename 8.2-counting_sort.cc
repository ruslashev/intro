#include "std.h"
#include <vector>

static void counting_sort(array A, array &B, int k) {
  std::vector<int> C(k, 0);
  for (size_t j = 1; j <= A.length; ++j)
    ++C[A[j]];
  for (size_t i = 1; i <= (size_t)k; ++i)
    C[i] = C[i] + C[i - 1];
  for (size_t j = A.length; j >= 1; --j) {
    B[C[A[j]]] = A[j];
    --C[A[j]];
  }
}

void counting_sort(array &A) {
  int max = A[1];
  for (size_t i = 2; i <= A.length; ++i)
    max = std::max(max, A[i]);
  array output(A.length);
  counting_sort(A, output, max);
  A = output;
}

