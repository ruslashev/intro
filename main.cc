#include "std.h"

int main() {
  array A = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };

  printf("array: ");
  A.print();

  subarray max = find_maximum_subarray_lin(A);
  printf("max subarray = A[%d..%d] = %d\n", max.start, max.end, max.sum);
}

