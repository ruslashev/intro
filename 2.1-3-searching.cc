#include "std.h"

// at the start of each iteration of the for loop, variable result holds true state
mvalue search(array &A, int v) {
  mvalue result;
  for (int i = 1; i <= A.length; ++i)
    if (A[i] == v) {
      result = i;
      break;
    }
  return result;
}

