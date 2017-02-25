#include "std.h"

static int count_inversions(array &A, int p, int q, int r) {
  int ll = q - p + 1, rl = r - q;
  array L(ll), R(rl);
  for (int i = 1; i <= ll; ++i)
    L[i] = A[p + i - 1];
  for (int j = 1; j <= rl; ++j)
    R[j] = A[q + j];
  int i = 1, j = 1, k = p, inversions = 0;
  while (i <= ll && j <= rl) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      ++i;
    } else {
      A[k] = R[j];
      ++j;
      inversions += ll - i + 1;
    }
    ++k;
  }
  while (j != rl + 1) {
    A[k++] = R[j++];
    // inversions += ll - i + 1;
  }
  while (i != ll + 1)
    A[k++] = L[i++];
  return inversions;
}

static int inversions(array &A, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2, count;
    count  = inversions(A, p, q);
    count += inversions(A, q + 1, r);
    count += count_inversions(A, p, q, r);
    return count;
  } else
    return 0;
}

int inversions(array &A) {
  return inversions(A, 1, A.length);
}

