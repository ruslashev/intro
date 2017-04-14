#include "std.h"

void longest_monotonically_increasing_subsequence_simple(array X) {
  array Y = X;
  quicksort(Y);
  longest_common_subsequence(X, Y);
}

void longest_monotonically_increasing_subsequence(std::vector<int> X) {
  std::vector<int> Y(X.size()), I(1, 0);
  for (size_t i = 1; i < X.size(); ++i) {
    if (X[I.back()] < X[i]) {
      Y[i] = I.back();
      I.push_back(i);
      continue;
    }
    size_t l, r;
    for (l = 0, r = I.size() - 1; l < r;) {
      size_t m = (l + r) / 2;
      if (X[I[m]] < X[i])
        l = m + 1;
      else
        r = m;
    }
    if (X[i] < X[I[l]]) {
      if (l > 0)
        Y[i] = I[l - 1];
      I[l] = i;
    }
  }
  for (size_t u = I.size(), v = I.back(); u--; v = Y[v])
    I[u] = v;
  for (size_t i = 0; i < I.size(); ++i)
    printf("%d ", X[I[i]]);
  puts("");
}

