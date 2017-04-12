#include "std.h"

int array_equilibrium(array A) {
  int r = 0, l = 0;
  for (size_t i = 1; i <= A.length; ++i)
    r += A[i];
  for (size_t i = 1; i <= A.length; ++i) {
    r -= A[i];
    if (l == r)
      return i;
    l += A[i];
  }
  return -1;
}

int array_equilibrium2(array A) {
  double l = 0, sum = 0;
  for (size_t i = 1; i <= A.length; ++i)
    sum += A[i];
  for (size_t i = 1; i <= A.length; ++i) {
    if (l == sum / 2.)
      return i;
    l += A[i];
  }
  return -1;
}

