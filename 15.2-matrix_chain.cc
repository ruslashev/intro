#include "std.h"

void matrix_chain_order(std::vector<int> p, matrix &m, matrix &s) {
  size_t n = p.size() - 1;
  m = matrix(n, n);
  s = matrix(n - 1, n);
  for (size_t i = 1; i <= n; ++i)
    m.at(i, i) = 0;
  for (size_t l = 2; l <= n; ++l)
    for (size_t i = 1; i <= n - l + 1; ++i) {
      size_t j = i + l - 1;
      m.at(i, j) = inf;
      for (size_t k = i; k < j; ++k) {
        int q = m.at(i, k) + m.at(k + 1, j) + p[i - 1] * p[k] * p[j];
        if (q < m.at(i, j)) {
          m.at(i, j) = q;
          s.at(i, j) = k;
        }
      }
    }
}

