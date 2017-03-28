#include "std.h"
#include <vector>

static void in_place_counting_sort(array &A, int k) {
  std::vector<int> C(k + 1, 0);
  for (size_t i = 1; i <= A.length; ++i)
    ++C[A[i]];
  for (size_t i = 1; i <= (size_t)k; ++i)
    C[i] += C[i - 1];
  size_t i = A.length;
  while (i >= 1) {
    int e = A[i];
    int pos = C[e];
    if (i > (size_t)pos)
      --i;
    else {
      // if (e != A[pos]) // optimization actually causes branch mispredictions
      std::swap(A[i], A[pos]);
      --C[e];
    }
  }
}

void in_place_counting_sort(array &A) {
  int max = A[1];
  for (size_t i = 2; i <= A.length; ++i)
    max = std::max(max, A[i]);
  in_place_counting_sort(A, max);
}

