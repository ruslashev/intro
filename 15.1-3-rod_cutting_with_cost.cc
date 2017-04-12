#include "std.h"

int cut_rod_with_cost(array p, int c, size_t n) {
  std::vector<int> r(n + 1);
  r[0] = 0;
  for (size_t j = 1; j <= n; ++j) {
    int q = neginf;
    for (size_t i = 1; i <= j; ++i)
      q = std::max(q, p[i] + r[j - i] - c);
    r[j] = q;
  }
  return r[n];
}

