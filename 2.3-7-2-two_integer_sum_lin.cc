#include "std.h"
#include <map>

bool sum_exists_lin(array &S, int x) {
  std::map<int, int> numbers_seen;
  for (size_t i = 1; i <= S.length; ++i) {
    int this_num = S[i], required = x - this_num;
    if (numbers_seen.count(required) > 0)
      return true;
    numbers_seen[this_num] = i;
  }
  return false;
}

