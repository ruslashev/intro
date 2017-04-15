#include "std.h"

// https://github.com/gzc/CLRS/blob/master/C15-Dynamic-Programming/optimalBST.cpp

void optimal_bst(std::vector<double> p, std::vector<double> q, size_t n) {
  std::vector<std::vector<double>> e(n + 2, std::vector<double>(n + 1)),
    w(n + 2, std::vector<double>(n + 1)),
    root(n + 1, std::vector<double>(n + 1));
  for (size_t i = 1; i <= n + 1; ++i)
    e[i][i - 1] = q[i - 1],
    w[i][i - 1] = q[i - 1];
  for (size_t l = 1; l <= n; ++l)
    for (size_t i = 1; i <= n - l + 1; ++i) {
      size_t j = i + l - 1;
      e[i][j] = inf;
      w[i][j] = w[i][j - 1] + p[j] + q[j];
      for (size_t r = i; r <= j; ++r) {
        auto t = e[i][r - 1] + e[r + 1][j] + w[i][j];
        if (t < e[i][j]) {
          e[i][j] = t;
          root[i][j] = r;
        }
      }
    }
}

