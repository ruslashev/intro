#include "std.h"
#include <chrono>

int main() {
  array X = { 4, 1, 2, 4, 3 };
  std::vector<int> Y = { 4, 1, 2, 4, 3 };
  longest_monotonically_increasing_subsequence_simple(X);
  longest_monotonically_increasing_subsequence(Y);
}

