#include "std.h"

// in-place: https://gist.github.com/andlima/1774060

static int median(array A) {
  insertion_sort(A);
  return A.length % 2 == 0 ? A[A.length / 2] : A[A.length / 2 + 1];
}

#if 0
int select(array A, size_t p, size_t r, size_t i) {
  puts("given:");
  printf("[");
  for (size_t j = p; j <= r; ++j)
    printf("%d ", A[j]);
  printf("], i=%d\n", (int)i);

  size_t len = r - p + 1, num_groups = len / 5, num_whole_groups = num_groups;

  if (len == 1)
    return A[p];

  if (len % 5 != 0)
    ++num_groups;

  puts("groups");
  array medians(num_groups);
  for (size_t g = 1; g <= num_whole_groups; ++g) {
    array group(5);
    for (size_t w = 1, j = 1; j <= 5; ++j, ++w)
      group[w] = A[p + (g - 1) * 5 + j - 1];
    group.print();
    medians[g] = median(group);
  }

  if (len % 5 != 0) {
    array extra_group(len % 5);
    for (size_t w = 1, j = 1; j <= extra_group.length; ++j, ++w)
      extra_group[w] = A[p + (num_groups - 1) * 5 + j - 1];
    extra_group.print();
    medians[medians.length] = median(extra_group);
  }

  puts("medians:");
  medians.print();

  puts("go");
  puts("");
  int x = select(medians, 1, medians.length, i);
  printf("return x=%d\n", x);

  for (size_t j = p; j <= r; ++j)
    if (A[j] == x)
      std::swap(A[j], A[r]);

  size_t k = p;
  for (size_t j = p; j <= r - 1; ++j)
    if (A[j] <= A[r])
      std::swap(A[k++], A[j]);
  std::swap(A[k], A[r]);

  printf("partition for x=%d\n", x);
  printf("[");
  for (size_t j = p; j <= r; ++j)
    printf("%d ", A[j]);
  puts("]");

  if (i == k) {
    puts("exact");
    return x;
  } else if (i < k) {
    puts("lower");
    return select(A, p, p + k - 2, i);
  } else {
    puts("higher");
    return select(A, p + k, r, i - k);
  }
}
#endif

int select(array A, size_t i) {
  size_t num_groups = A.length / 5, num_whole_groups = num_groups;

  if (A.length == 1)
    return A[1];

  if (A.length % 5 != 0)
    ++num_groups;

  array medians(num_groups);
  for (size_t g = 1; g <= num_whole_groups; ++g) {
    array group(5);
    for (size_t w = 1, j = 1; j <= 5; ++j, ++w)
      group[w] = A[(g - 1) * 5 + j];
    medians[g] = median(group);
  }

  if (A.length % 5 != 0) {
    array extra_group(A.length % 5);
    for (size_t w = 1, j = 1; j <= extra_group.length; ++j, ++w)
      extra_group[w] = A[(num_groups - 1) * 5 + j];
    medians[medians.length] = median(extra_group);
  }

  int x = select(medians, i);

  array lower(A.length), higher(A.length);
  size_t l = 1, h = 1;
  for (size_t j = 1; j <= A.length; ++j)
    if (A[j] < x)
      lower[l++] = A[j];
    else if (A[j] > x)
      higher[h++] = A[j];
  array actual_lower(l - 1), actual_higher(h - 1);
  for (size_t j = 1; j <= actual_lower.length; ++j)
    actual_lower[j] = lower[j];
  for (size_t j = 1; j <= actual_higher.length; ++j)
    actual_higher[j] = higher[j];

  if (i == l)
    return x;
  else if (i < l)
    return select(actual_lower, i);
  else
    return select(actual_higher, i - l);
}

#if 0
int select(array A, size_t i) {
  return select(A, 1, A.length, i);
}
#endif

