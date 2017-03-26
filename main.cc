#include "std.h"
#include <cmath>

int main() {
  array A(20);
  A.randomize();
  A.print();
  counting_sort(A);
  A.print();
}

