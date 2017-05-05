#include "std.h"

int change_coins(int x, int q, int d, int n, int p) {
  int c = 0;
  while (x != 0) {
    if (x >= 25 && q > 0)
      x -= 25;
    else if (x >= 10 && d > 0)
      x -= 10;
    else if (x >= 5 && n > 0)
      x -= 5;
    else if (p > 0)
      x -= 1;
    else
      die("no more change");
    ++c;
  }
  return c;
}

int change_arb_coins_naive(int x, std::vector<std::pair<int,int>> coins) {
  if (x <= 0)
    return 0;
  int m = inf;
  for (size_t i = 0; i < coins.size(); ++i) {
    int coin = coins[i].first,
        q = change_arb_coins(x - coin, coins) + 1;
    if (q < m)
      m = q;
  }
  return m;
}

