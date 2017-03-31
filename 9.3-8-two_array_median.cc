#include "std.h"

size_t median_idx(size_t p, size_t r) {
  size_t n = r - p + 1;
  if (n % 2 == 0)
    return n / 2;
  else
    return n / 2 + 1;
}

int two_array_median(array X, size_t xp, size_t xr, array Y, size_t yp
    , size_t yr) {
  if (xr - xp + 1 == 1)
    return std::min(X[xp], Y[yp]);
  size_t xm = median_idx(xp, xr), ym = median_idx(yp, yr);
  if (X[xm] < Y[ym])
    return two_array_median(X, xm, xr, Y, yp, ym);
  else
    return two_array_median(X, xp, xm, Y, ym, yr);
}

