#include "std.h"

subarray find_maximum_subarray_lin(array &A) {
  // int max_ending_here = A[1], max_so_far = A[1];
  // for (size_t i = 2; i <= A.length; ++i) {
  //   int v = A[i];
  //   max_ending_here = std::max(v, max_ending_here + v);
  //   max_so_far = std::max(max_so_far, max_ending_here);
  // }
  // return max_so_far;
  int max_sum_ending_here = A[1], max_sum_so_far = A[1];
  int max_start_here = 1, max_end_here = 1,
      max_start_so_far = 1, max_end_so_far = 1;
  for (size_t i = 2; i <= A.length; ++i) {
    int v = A[i];
    if (v > max_sum_ending_here + v) {
      max_sum_ending_here = v;
      max_start_here = i;
      max_end_here = i;
    } else {
      max_sum_ending_here = max_sum_ending_here + v;
      max_end_here = i;
    }
    if (max_sum_ending_here > max_sum_so_far) {
      max_sum_so_far = max_sum_ending_here;
      max_start_so_far = max_start_here;
      max_end_so_far = max_end_here;
    }
  }
  return { max_start_so_far, max_end_so_far, max_sum_so_far };
}

