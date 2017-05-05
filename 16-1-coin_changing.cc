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
        q = change_arb_coins_naive(x - coin, coins) + 1;
    if (q < m)
      m = q;
  }
  return m;
}

static int change_arb_coins_memo_aux(int x,
    std::vector<std::pair<int,int>> coins, std::vector<int> S) {
  if (S[x] >= 0)
    return S[x];
  int r;
  if (x <= 0)
    r = 0;
  else {
    r = inf;
    for (size_t i = 0; i < coins.size(); ++i) {
      int coin = coins[i].first,
          q = change_arb_coins_memo_aux(x - coin, coins, S) + 1;
      if (q < r)
        r = q;
    }
  }
  S[x] = r;
  return r;
}

int change_arb_coins_memo(int x, std::vector<std::pair<int,int>> coins) {
  std::vector<int> S(x + 1, -1);
  S[0] = 0;
  return change_arb_coins_memo_aux(x, coins, S);
}

int change_arb_coins_bu(int x, std::vector<std::pair<int,int>> coins) {
  std::vector<int> S(x + 1), history(x + 1);
  for (int i = 0; i <= x; ++i) {
    // copy coins vector for this iteration?
    if (i == 0)
      S[i] = 0;
    else {
      int m = inf, c = -1;
      for (size_t j = 0; j < coins.size(); ++j) {
        if (coins[j].second <= 0)
          continue;
        int coin = coins[j].first;
        if (i - coin >= 0) {
          int q = S[i - coin] + 1;
          if (q < m) {
            m = q;
            c = j;
          }
        }
      }
      if (c == -1)
        die("no more coins");
      --coins[c].second;
      S[i] = m;
      history[i] = coins[c].first;
    }
  }
  for (size_t i = x; i != 0;) {
    int c = history[i];
    printf("%d ", c);
    i -= c;
  }
  puts("");
  return S[x];
}

