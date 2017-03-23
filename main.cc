#include "std.h"
#include <cmath>

int main() {
  array a(32);
  a.randomize();
  a.print();
  heap h(a);
  h.print();
  h.heapsort();
  h.print();
}

