#include "std.h"

ull fib(int i) {
  if (i <= 2)
    return 1;
  return fib(i - 1) + fib(i - 2);
}

ull fib_dp(int i) {
  std::vector<ull> r(i + 1);
  for (int j = 1; j <= i; ++j) {
    ull q;
    if (j <= 2)
      q = 1;
    else
      q = r[j - 1] + r[j - 2];
    r[j] = q;
  }
  return r[i];
}

ull fib_dp2(int i) {
  ull rp = 0, rpp = 0;
  for (int j = 1; j <= i; ++j) {
    ull q;
    if (j == 1)
      q = 1;
    else if (j == 2) {
      rp = 1;
      q = 1;
    } else
      q = rp + rpp;
    rpp = rp;
    rp = q;
  }
  return rp;
}

