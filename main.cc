#include "std.h"
#include <chrono>

int main() {
  avl_os_tree tree;
  for (size_t i = 0; i < 20; ++i)
    tree.insert(rand_in_range(0, 20));
  tree.print(100);
  for (size_t i = 1; i <= 20; ++i)
    printf("tree.select(%d)->key=%d\n", (int)i, tree.select(i)->key);
}

