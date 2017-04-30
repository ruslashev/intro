#include "std.h"

static std::vector<activity> activity_selection_rec(std::vector<activity> S, int k, int n) {
  int m = k + 1;
  while (m <= n && S[m].s < S[k].f)
    ++m;
  if (m < n) {
    std::vector<activity> r = activity_selection_rec(S, m, n);
    r.push_back(S[m]);
    return r;
  } else {
    std::vector<activity> e;
    return e;
  }
}

std::vector<activity> activity_selection_rec(std::vector<activity> S) {
  return activity_selection_rec(S, -1, S.size());
}

std::vector<activity> activity_selection_gr(std::vector<activity> S) {
  size_t k = 0;
  std::vector<activity> A = { S[0] };
  for (size_t m = 1; m < S.size(); ++m)
    if (S[m].s >= S[k].f) {
      A.push_back(S[m]);
      k = m;
    }
  return A;
}

/*
std::vector<activity> activity_selection_dp(std::vector<activity> S) {
  size_t n = S.size();
  matrix c(n, n, 0);
  for (size_t i = 1; i <= n; ++i)
    for (size_t j = 2; j <= n; ++j)
      if (i > j)
        c.at(i, j) = 0;
      else
        for (size_t k = i + 1; k <= j - 1; ++k)
          if (c.at(i, j) < c.at(i, k) + c.at(k, j) + 1)
            c.at(i, j) = c.at(i, k) + c.at(k, j) + 1;

  for (size_t l = 2; l <= n; ++l)
    for (size_t i = 1; i <= n - l + 1; ++i) {
      size_t j = i + l - 1;
      c.at(i, j) = inf;
      for (size_t si = 1; si <= n; ++si) {
        size_t k = si;
        int q = c.at(i, k) + c.at(k, j) + 1;
        if (q < c.at(i, j))
          c.at(i, j) = q;
      }
    }
  printf("c.at(1, n)=%d\n", c.at(1, n));
}
*/

