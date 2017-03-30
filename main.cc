#include "std.h"
#include <chrono>

int main() {
  array A(10);
  A.sequence();
  A.scramble();
  A.print();
  printf("k_closest_to_median(A, 3)=%d\n", k_closest_to_median(A, 3));
}

