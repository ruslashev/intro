#include "std.h"
#include <chrono>

int main() {
  btree T(2);
  T.insert(1);
  T.insert(5);
  T.insert(3);
  T.insert(2);
  T.print();
}

