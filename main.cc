#include "std.h"
#include <chrono>

int main() {
  printf("edit_distance(\"kitten\", \"sitting\")=%d\n", (int)edit_distance("kitten", "sitting"));
}

