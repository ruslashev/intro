#include "std.h"
#include <chrono>

int main() {
  array A(19);
  A.randomize();
  A.print();
  quicksort(A);
  A.print();
}

