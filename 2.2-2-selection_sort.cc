#include "std.h"

/* At the start of each iteratior of the outer loop, the subarray A[1..i]
 * is in sorted order */
void selection_sort(array &A) {
  for (int i = 1; i <= A.length - 1; i++)
    for (int j = i + 1; j <= A.length; j++)
      if (A[j] < A[i])
        std::swap(A[i], A[j]);
}

int main() {
  array A(10);
  A.randomize();

  printf("before: ");
  A.print();

  selection_sort(A);

  printf("after : ");
  A.print();
}

