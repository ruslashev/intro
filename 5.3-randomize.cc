#include "std.h"

void randomize_in_place(array &A) {
  for (size_t i = 1; i < A.length; ++i)
    std::swap(A[i], A[rand_in_range(i, A.length)]);
}

