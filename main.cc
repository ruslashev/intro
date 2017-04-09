#include "std.h"
#include <chrono>

int main() {
  avl_tree tree;
  for (size_t i = 0; i < 20; ++i) {
    tree.insert(rand_in_range(0, 20));
    tree.print();
  }
  std::vector<int> traversal = tree.level_order(tree.root);
  for (size_t i = 0; i < traversal.size(); ++i)
    printf("%d ", traversal[i]);
  puts("");
}

