#include "std.h"
#include <chrono>

int main() {
  bst<int> root(10);
  for (size_t i = 0; i < 20; ++i)
    root.insert(rand_in_range(0, 20));
  root.print();
}

