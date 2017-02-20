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

// at the start of each iteration of the for loop, variable result holds true state
value search(array &A, int v) {
  value result;
  for (int i = 1; i <= A.length; ++i)
    if (A[i] == v) {
      result = i;
      break;
    }
  return result;
}

int main() {
  array A(10);
  A.randomize();

  printf("before: ");
  A.print();

  value x = search(A, 22);
  x.print();
}

