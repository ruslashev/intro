#include "std.h"
#include <chrono>

int main() {
  std::vector<int> p = { 30, 35, 15, 5, 10, 20, 25 };
  matrix m, s;
  matrix_chain_order(p, m, s);
  m.print();
}

