#include "std.h"
#include <chrono>

int main() {
  array A(20);
  A.sequence();
  A.scramble();
  array B = A;
  insertion_sort(B);
  A.print();
  B.print();
  for (size_t i = 1; i <= A.length; ++i)
    printf("select(A, %d)=%d\n", (int)i, select(A, i));
}

