#include "std.h"
#include <cmath>

int main() {
  young_tableau t(4, 4, { 9, 16, 3, 2, 4, 8, 5, 14, 12 });
  t.print();
  for (int i = 1; i <= 9; ++i) {
    int v = t.extract_min();
    printf("v=%d\n", v);
    t.print();
  }
}

