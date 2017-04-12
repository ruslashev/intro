#include "std.h"

int cut_rod1(array p, size_t n) {
  if (n == 0)
    return 0;
  int q = neginf;
  for (size_t i = 1; i <= n; ++i)
    q = std::max(q, p[i] + cut_rod1(p, n - i));
  return q;
}

static int cut_rod2_aux(array p, size_t n, std::vector<int> &r) {
  if (r[n] >= 0)
    return r[n];
  int q;
  if (n == 0)
    q = 0;
  else {
    q = neginf;
    for (size_t i = 1; i <= n; ++i)
      q = std::max(q, p[i] + cut_rod2_aux(p, n - i, r));
  }
  r[n] = q;
  return q;
}

int cut_rod2(array p, size_t n) {
  std::vector<int> r(n + 1, neginf);
  return cut_rod2_aux(p, n, r);
}

int cut_rod3(array p, size_t n) {
  std::vector<int> r(n + 1);
  r[0] = 0;
  for (size_t j = 1; j <= n; ++j) {
    int q = neginf;
    for (size_t i = 1; i <= j; ++i)
      q = std::max(q, p[i] + r[j - i]);
    r[j] = q;
  }
  return r[n];
}

