#include "std.h"

/* anon 1:
 * #define SIZE 1000
 * int div_sum(int n) {
 *   int m = SIZE / n;
 *   return n * (m * (m + 1)) / 2;
 * }
 * int main() {
 *   printf("%d\n", div_sum(3) + div_sum(5) - div_sum(15));
 * }
 */

/* anon 2:
 * x = floor(1000 / 3)
 * y = floor(1000 / 5)
 * z = floor(1000 / 15)
 * sum(1 to x) * 3 + sum(1 to y) * 5 - sum(1 to z) * 15
 */

int arithmetic_progression_sum(int a1, int d, size_t n) {
  return ((2 * a1 + d * (n - 1)) * n) / 2;
}

int int_sequence_sum(size_t n) {
  return arithmetic_progression_sum(1, 1, n);
  // return ((n + 1) * n) / 2;
}

size_t sum_of_multiples_of(size_t N, size_t x) {
  size_t a = N / x;
  return int_sequence_sum(a) * x;
}

size_t sum_of_multiples() {
  // sum of all multiples of 3 and 5 below 1000
  return sum_of_multiples_of(1000, 3) + sum_of_multiples_of(1000, 5)
    - sum_of_multiples_of(1000, 15);
}

