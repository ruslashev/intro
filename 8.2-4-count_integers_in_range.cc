#include "std.h"

void preprocess_count_integers_in_range(array &A, std::vector<int> &C, int &max) {
  max = A[1];
  for (size_t i = 2; i <= A.length; ++i)
    max = std::max(max, A[i]);
  C = std::vector<int>(max + 1, 0);
  for (size_t i = 1; i <= A.length; ++i)
    ++C[A[i]];
  for (size_t i = 1; i <= (size_t)max; ++i)
    C[i] += C[i - 1];
}

int count_integers_in_range(array &A, array &C, int max, int a, int b, int &n) {
  if (a > b || b < 0 || a > max || A.length == 0)
    return 0;
  int sum = a <= 0 ? C[0] : 0;
  sum += C[std::min(max, b)] - C[std::max(0, a - 1)];
  return sum;
}

