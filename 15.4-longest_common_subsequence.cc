#include "std.h"

void longest_common_subsequence(array X, array Y) {
  size_t m = X.length, n = Y.length;
  std::vector<std::vector<int>> c(m + 1, std::vector<int>(n + 1));
  std::vector<std::vector<char>> b(m + 1, std::vector<char>(n + 1));
  for (size_t i = 1; i <= m; ++i)
    c[i][0] = 0;
  for (size_t j = 1; j <= n; ++j)
    c[0][j] = 0;
  for (size_t i = 1; i <= m; ++i)
    for (size_t j = 1; j <= n; ++j)
      if (X[i] == Y[j]) {
        c[i][j] = c[i - 1][j - 1] + 1;
        b[i][j] = 'd';
      } else if (c[i - 1][j] >= c[i][j - 1]) {
        c[i][j] = c[i - 1][j];
        b[i][j] = 'u';
      } else {
        c[i][j] = c[i][j - 1];
        b[i][j] = 'l';
      }
  std::vector<int> lcs;
  size_t i = m, j = n;
  while (i != 0 and j != 0) {
    switch (b[i][j]) {
      case 'u':
        --i;
        break;
      case 'l':
        --j;
        break;
      default:
        lcs.push_back(X[i]);
        --i, --j;
    }
  }
  printf("lcs: ");
  for (int i = lcs.size() - 1; i >= 0; --i)
    printf("%d ", lcs[i]);
  puts("");
}

// not even working
/*
static void longest_common_subsequence_bad(array X) {
  array s(X.length);
  for (size_t i = 1; i <= s.length; ++i)
    s[i] = 0;

  bool b = false;
  while (!b) {
    s.print();

    size_t i = 1;
    while (1)
      if (i > s.length) {
        b = true;
        break;
      } else if (s[i] == 1)
        s[i++] = 0;
      else {
        s[i] = 1;
        break;
      }
  }
}
*/

