#include "std.h"

int coin_streak(int n) {
  int last = 0, streak = 0, max_streak = 0;
  for (int i = 1; i <= n; ++i) {
    int coin = rand_in_range(0, 1);
    if (coin == last || i == 1) {
      ++streak;
      max_streak = std::max(max_streak, streak);
    } else
      streak = 0;
    last = coin;
  }
  return max_streak;
}

