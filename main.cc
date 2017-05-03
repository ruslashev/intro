#include "std.h"
#include <chrono>

int main() {
  array weights = { 10, 20, 30 }, values = { 60, 100, 120 };
  binary_knapsack(50, weights, values);
}

