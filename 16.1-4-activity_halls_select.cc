#include "std.h"
#include <algorithm>

// file:///home/ruslashev/Downloads/Intro_to_Algo_Selected_Solutions.pdf#page=49&zoom=90,-487,792

void activity_halls_select(std::vector<activity> S) {
  std::sort(S.begin(), S.end(),
      [](const activity &a, const activity &b) {
        return a.s < b.s;
      });
  int next_free = 1;
  std::vector<std::set<int>> F, B; // indexed by time
  for (activity &a : S) {
    if (F[a.s].empty()) {
      int h = next_free++;
      for (int i = a.s; i < a.f; ++i)
        B[i].insert(h);
    }
  }
  for (activity &a : S)
    printf("%d %d\n", a.s, a.f);
}

