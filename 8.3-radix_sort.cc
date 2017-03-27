#include "std.h"

int get_digit(int num, int d) {
  while (d > 1) {
    --d;
    num /= 10;
  }
  return num % 10;
}

static void counting_sort_on_digit(array &A, int d) {
  array output(A.length);
  std::vector<int> C(11, 0);
  for (size_t j = 1; j <= A.length; ++j)
    ++C[get_digit(A[j], d)];
  for (size_t i = 1; i <= 10; ++i)
    C[i] += C[i - 1];
  for (size_t i = A.length; i >= 1; --i) {
    output[C[get_digit(A[i], d)]] = A[i];
    --C[get_digit(A[i], d)];
  }
  A = output;
}

void radix_sort(array &A) {
  int max = A[1];
  for (size_t i = 2; i <= A.length; ++i)
    max = std::max(max, A[i]);
  int digits = 0;
  while (max != 0) {
    max /= 10;
    ++digits;
  }
  for (int d = 1; d <= digits; ++d)
    counting_sort_on_digit(A, d);
}

