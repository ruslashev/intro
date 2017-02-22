#include "std.h"

void merge(array &A, int p, int q, int r) {
  int ll = q - p + 1, rl = r - q;
  array L(ll), R(rl);
  for (int i = 1; i <= ll; ++i)
    L[i] = A[p + i - 1];
  for (int j = 1; j <= rl; ++j)
    R[j] = A[q + j];
  int i = 1, j = 1, k = p;
  while (i <= ll && j <= rl) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      ++i;
    } else {
      A[k] = R[j];
      ++j;
    }
    ++k;
  }
  while (j != rl + 1)
    A[k++] = R[j++];
  while (i != ll + 1)
    A[k++] = L[i++];
}

void merge_sort(array &A, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    merge_sort(A, p, q);
    merge_sort(A, q + 1, r);
    merge(A, p, q, r);
  }
}

int main() {
  array A(11);
  A.randomize();

  printf("before: ");
  A.print();

  merge_sort(A, 1, A.length);

  printf("after : ");
  A.print();
}

