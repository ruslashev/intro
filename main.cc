#include "std.h"
#include <cmath>

int main() {
  array A(20);
  A.randomize(10, 99);
  A.print();
  radix_sort(A);
  A.print();
}

