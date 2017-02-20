#include "std.h"

void insertion_sort(int *A, int length) {
  for (int j = 1; j < length; j++) {
    int key = A[j];
    int i = j - 1;
    while (i >= 0 && key < A[i]) {
      A[i + 1] = A[i];
      --i;
    }
    A[i + 1] = key;
  }
}

int main() {
  array<10> A;
  A.randomize();

  printf("before: ");
  A.print();

  insertion_sort(A.data, A.size);

  printf("after : ");
  A.print();
}

