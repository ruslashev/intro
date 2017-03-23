#include "std.h"
#include <cmath>

int main() {
  array a(32);
  a.randomize(1, 150);
  heap h(a);
  h.print();
}

