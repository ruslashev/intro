#include "std.h"
#include <chrono>

int main() {
  int q = change_arb_coins(6, { { 1, 10 }, { 3, 10 }, { 4, 10 } });
  printf("q=%d\n", q);
}

