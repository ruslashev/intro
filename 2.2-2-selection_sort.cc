#include "std.h"

/* At the start of each iteratior of the outer loop, the subarray A[1..i]
 * is in sorted order */
void selection_sort(array &A) {
  for (size_t i = 1; i <= A.length - 1; i++)
    for (size_t j = i + 1; j <= A.length; j++)
      if (A[j] < A[i])
        std::swap(A[i], A[j]);
}

