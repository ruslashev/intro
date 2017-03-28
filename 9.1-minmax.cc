#include "std.h"

void minmax(array A, int &min, int &max) {
  size_t i, c = 0;
  if (A.length % 2 == 0) {
    ++c;
    if (A[1] > A[2]) {
      max = A[1];
      min = A[2];
    } else {
      min = A[1];
      max = A[2];
    }
    i = 3;
  } else {
    min = max = A[1];
    i = 2;
  }
  for (; i <= A.length; i += 2) {
    int fst = A[i], snd = A[i + 1];
    ++c;
    ++c;
    ++c;
    if (fst > snd) {
      max = std::max(max, fst);
      min = std::min(min, snd);
    } else {
      max = std::max(max, snd);
      min = std::min(min, fst);
    }
  }
  printf("c=%d\n", c);
}

void minmax_naive(array A, int &min, int &max) {
  size_t c = 0;
  min = max = A[1];
  for (size_t i = 2; i <= A.length; ++i) {
    ++c;
    ++c;
    max = std::max(max, A[i]);
    min = std::min(min, A[i]);
  }
  printf("c=%d\n", c);
}

