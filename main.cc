#include "std.h"
#include <chrono>

int main() {
  std::vector<int> Y = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
  array X(Y);
  longest_monotonically_increasing_subsequence_simple(X);
  longest_monotonically_increasing_subsequence(Y);
}

