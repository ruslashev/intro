#include "std.h"

int main() {
  array A(4);
  A.randomize();

  printf("array: ");
  A.print();

  printf("inversions = %d\n", inversions(A));
}

