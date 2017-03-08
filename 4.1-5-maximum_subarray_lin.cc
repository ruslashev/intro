#include "std.h"

subarray find_maximum_subarray_lin(array &A) {
  int best_sum = 0, best_now = 0, best_start_so_far = -1, best_stop_so_far = -1,
      bestStartIndexNow = -1;
  for (size_t i = 1; i <= A.length; ++i) {
    int value = best_now + A[i];
    if (value > 0) {
      if (best_now == 0)
        bestStartIndexNow = i;
      best_now = value;
    } else
      best_now = 0;
    if (best_now > best_sum) {
      best_sum = best_now;
      best_stop_so_far = i;
      best_start_so_far = bestStartIndexNow;
    }
  }
  return { best_start_so_far, best_stop_so_far, best_sum };
}

