#include "std.h"
#include "rb_tree.h"
#include <chrono>

int main() {
  rb_tree tree;
  for (size_t i = 0; i < 20; ++i)
    rb_insert(tree, new rb_node(rand_in_range(0, 20)));
  tree.print();
}

