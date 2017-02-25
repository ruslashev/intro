#include "std.h"

void insertion_sort(array &A) {
  for (int j = 2; j <= A.length; ++j) {
    int key = A[j];
    int i = j - 1;
    while (i > 0 && key < A[i]) {
      A[i + 1] = A[i];
      --i;
    }
    A[i + 1] = key;
  }
}

