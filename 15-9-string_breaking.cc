#include "std.h"

void string_breaking(size_t n, array p) {
  matrix S(n, n);
  for (size_t i = 1; i <= n; ++i)
    S.at(i, i) = 1;
  for (size_t l = 2; l <= n; ++l)
    for (size_t i = 1; i <= n - l + 1; ++i) {
      size_t j = i + l - 1;
      S.at(i, j) = inf;
      for (size_t pi = 1; pi <= p.length; ++pi) {
        size_t k = p[pi];
        int q = S.at(i, k) + S.at(k + 1, j) + j - i + 1;
        if (q < S.at(i, j))
          S.at(i, j) = q;
      }
    }
  printf("S.at(1, n)=%d\n", S.at(1, n));
}

