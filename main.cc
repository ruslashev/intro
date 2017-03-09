#include "std.h"
#include <cmath>

int main() {
  int throws = 1e6;
  printf("throws: %d\nstreak: %d\nlog2 = %f\n", throws, coin_streak(throws),
      std::log2(throws));
}

