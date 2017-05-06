#include "veb_tree.h"
#include <cassert>

int main() {
  gen_veb_tree<int, 32> T;

  T.insert(5);
  T.insert(10);
  T.insert(3);

  assert(T.lookup(5));
  assert(T.lookup(10));
  assert(!T.lookup(15));

  int three, five, ten;
  assert(T.succ(3, three) == true && three == 3);
  assert(T.succ(4, five)  == true && five == 5);
  assert(T.succ(7, ten)   == true && ten == 10);
  assert(T.succ(100, ten) == false);
}

