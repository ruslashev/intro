#include "std.h"

void binary_knapsack(int max_weight, array weights, array values) {
  size_t n = weights.length;
  std::vector<std::vector<int>> c(n + 1, std::vector<int>(max_weight + 1));
  for (int w = 0; w <= max_weight; ++w)
    c[0][w] = 0;
  for (size_t i = 1; i <= n; ++i) {
    c[i][0] = 0;
    for (int w = 1; w <= max_weight; ++w)
      if (weights[i] <= w) {
        int take = values[i] + c[i - 1][w - weights[i]]
          , leave = c[i - 1][w];
        c[i][w] = std::max(take, leave);
      } else
        c[i][w] = c[i - 1][w];
  }
  printf("c[n][max_weight]=%d\n", c[n][max_weight]);
}

