#include "std.h"
#include <chrono>

int main() {
  std::vector<activity> S = { { 1, 4 }, { 3, 5 }, { 0, 6 }, { 5, 7 }, { 3, 9 },
    { 5, 9 }, { 6, 10 }, { 8, 11 }, { 8, 12 }, { 2, 14 }, { 12, 16 } };
  activity_halls_select(S);
}

