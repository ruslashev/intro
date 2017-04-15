#include "std.h"

std::string chop(std::string x) {
  x.pop_back();
  return x;
}

template<typename T>
T min3(T x, T y, T z) {
  return std::min(std::min(x, y), z);
}

size_t edit_distance_simple(std::string a, std::string b) {
  size_t m = a.length(), n = b.length();

  if (m == 0)
    return n; // n insertions

  if (n == 0)
    return m; // m deletions

  if (a[m - 1] == b[n - 1])
    return edit_distance_simple(chop(a), chop(b));

  return 1 + min3(edit_distance_simple(a,       chop(b)),
                  edit_distance_simple(chop(a), b),
                  edit_distance_simple(chop(a), chop(b)));
}

size_t edit_distance(std::string a, std::string b) {
  size_t m = a.length(), n = b.length();
  std::vector<std::vector<size_t>> d(m + 1, std::vector<size_t>(n + 1));
  for (size_t i = 0; i <= m; ++i)
    for (size_t j = 0; j <= n; ++j) {
      if (i == 0)
        d[i][j] = j;
      else if (j == 0)
        d[i][j] = i;
      else if (a[i - 1] == b[j - 1])
        d[i][j] = d[i - 1][j - 1];
      else
        d[i][j] = 1 + min3(d[i][j - 1], d[i - 1][j], d[i - 1][j - 1]);
    }
  return d[m][n];
}

