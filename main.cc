#include "std.h"
#include <chrono>

int main() {
  array A(19);
  A.randomize(1, 32);
  A.print();
  printf("second_smallest(A)=%d\n", second_smallest(A));
}

