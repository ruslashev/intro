#include "std.h"

bool sum_exists(array &S, int x) {
  merge_sort(S);
  bool exists = false;
  for (size_t i = 1; i <= S.length; ++i)
    if (!bsearch(S, x - S[i]).nil) {
      exists = true;
      break;
    }
  return exists;
}

