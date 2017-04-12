#include "std.h"
#include <chrono>

int main() {
  for (int i = 1; i <= 10; ++i)
    printf("%d\t%d\t%d\n", i, fib_dp(i), fib_dp2(i));
}

