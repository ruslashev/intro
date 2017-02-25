#include "std.h"

int main() {
  array A(10);
  A.randomize_walk();

  printf("array: ");
  A.print();

  subarray max = find_maximum_subarray(A);
  printf("max subarray = A[%d..%d] = %d\n", max.start, max.end, max.sum);
}

