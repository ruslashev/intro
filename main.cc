#include "std.h"

int main() {
  array A(10);

  printf("array: ");
  A.print();

  randomize_in_place(A);
  printf("array: ");
  A.print();
}

