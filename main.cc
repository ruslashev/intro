#include "std.h"
#include <chrono>

int main() {
  int q = change_arb_coins_bu(6, { { 1, 100 }, { 3, 100 }, { 4, 100 } });
  printf("q=%d\n", q);
}

