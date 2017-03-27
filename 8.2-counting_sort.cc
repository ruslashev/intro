#include "std.h"
#include <vector>

static void counting_sort(array &A, int k) {
  array output(A.length);
  std::vector<int> C(k + 1, 0);
  for (size_t i = 1; i <= A.length; ++i)
    ++C[A[i]];
  for (size_t i = 1; i <= (size_t)k; ++i)
    C[i] += C[i - 1];
  for (size_t i = A.length; i >= 1; --i) {
    output[C[A[i]]] = A[i];
    --C[A[i]];
  }
  A = output;
}

void counting_sort(array &A) {
  int max = A[1];
  for (size_t i = 2; i <= A.length; ++i)
    max = std::max(max, A[i]);
  counting_sort(A, max);
}

