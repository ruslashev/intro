#include "std.h"
#include <cmath>

int main() {
  young_tableau t(5, 5,
      {  1,  4,  7, 11, 15
      ,  2,  5,  8, 12, 19
      ,  3,  6,  9, 16, 22
      , 10, 13, 14, 17, 24
      , 18, 21, 23, 26, 30 });
  printf("t.search(9)=%d\n", t.search(9));
  printf("t.search(10)=%d\n", t.search(10));
  printf("t.search(4)=%d\n", t.search(4));
}

