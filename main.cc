#include "std.h"
#include <chrono>

int main() {
  array p = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
  array p2(2000);
  p2.randomize_walk(0, 3);
  int n = 1100;
  printf("cut_rod3(p2, %d)=%d\n", n, cut_rod3(p2, n));
}

