#include "std.h"
#include <chrono>

int main() {
  fib_heap h;
  h.insert(3);
  h.insert(5);
  h.insert(1);
  h.insert(2);
  h.print();
  printf("h.get_min()->value=%d\n", h.get_min()->value);
  h.extract_min();
  printf("h.get_min()->value=%d\n", h.get_min()->value);
  h.extract_min();
  printf("h.get_min()->value=%d\n", h.get_min()->value);
  h.extract_min();
  printf("h.get_min()->value=%d\n", h.get_min()->value);
  h.extract_min();
}

