#include "std.h"

static subarray find_max_crossing_subarray(array &A, size_t low, size_t mid, size_t high) {
  int left_sum = neginf
    , max_left
    , sum = 0;
  for (size_t i = mid; i >= low; --i) {
    sum += A[i];
    if (sum > left_sum) {
      left_sum = sum;
      max_left = i;
    }
  }
  int right_sum = neginf
    , max_right;
  sum = 0;
  for (size_t i = mid + 1; i <= high; ++i) {
    sum += A[i];
    if (sum > right_sum) {
      right_sum = sum;
      max_right = i;
    }
  }
  return { max_left, max_right, left_sum + right_sum };
}

static subarray find_maximum_subarray(array &A, int low, int high) {
  if (high == low)
    return { low, high, A[low] };
  else {
    int mid = (low + high) / 2;
    subarray left = find_maximum_subarray(A, low, mid)
      , right = find_maximum_subarray(A, mid + 1, high)
      , crossing = find_max_crossing_subarray(A, low, mid, high);
    if (left.sum >= right.sum && left.sum >= crossing.sum)
      return { left.start, left.end, left.sum };
    else if (right.sum >= left.sum && right.sum >= crossing.sum)
      return { right.start, right.end, right.sum };
    else
      return { crossing.start, crossing.end, crossing.sum };
  }
}

subarray find_maximum_subarray(array &A) {
  return find_maximum_subarray(A, 1, A.length);
}

