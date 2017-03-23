#include "std.h"
#include <cmath>

int main() {
  // heap h({ 1, 2, 3, 4, 5 });
  // h.print();
  array a(10);
  a.randomize();
  a.print();
  merge_sort(a);
  a.print();
}

