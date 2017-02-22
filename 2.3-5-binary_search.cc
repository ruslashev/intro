#include "std.h"

struct value {
  int v;
  bool nil;
  value() : nil(true) {}
  value* operator=(int n_v) {
    v = n_v;
    nil = false;
  }
  void print() {
    if (nil)
      puts("nil");
    else
      printf("%d\n", v);
  }
};

/* binary-search(A, v, p, r)
 *   if p < r
 *     q = floor((p + r) / 2)
 *     if v <= A[q]
 *       binary-search(A, v, p, q)
 *     else
 *       binary-search(A, v, q + 1, r)
 *   else
 *     if A[p] == v
 *       return p
 *     else
 *       return nil
 */

value bsearch(array &A, int v, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    if (v <= A[q])
      return bsearch(A, v, p, q);
    else
      return bsearch(A, v, q + 1, r);
  } else {
    value result;
    if (A[p] == v)
      result = p;
    return result;
  }
}

int main() {
  array A = { 1, 2, 3, 4, 5, 6, 7 };

  printf("before: ");
  A.print();

  value x = bsearch(A, 6, 1, A.length);
  x.print();
}

