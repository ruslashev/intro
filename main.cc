#include "std.h"
#include <chrono>

int main() {
  avl_tree tree;
  for (size_t i = 0; i < 20; ++i) {
    tree.insert(rand_in_range(0, 20));
    tree.print();
  }
  puts("deleting");
  for (size_t i = 0; i < 20; ++i) {
    tree.delete_key(tree.root->key);
    tree.print();
  }
}

