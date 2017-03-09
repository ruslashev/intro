#include "std.h"
#include <chrono>

// 1
#include <cmath>
// 1 end

// 2
const int tab64[64] = {
  63,  0, 58,  1, 59, 47, 53,  2,
  60, 39, 48, 27, 54, 33, 42,  3,
  61, 51, 37, 40, 49, 18, 28, 20,
  55, 30, 34, 11, 43, 14, 22,  4,
  62, 57, 46, 52, 38, 26, 32, 41,
  50, 36, 17, 19, 29, 10, 13, 21,
  56, 45, 25, 31, 35, 16,  9, 12,
  44, 24, 15,  8, 23,  7,  6,  5
};
int log2_64(uint64_t value) {
  value |= value >> 1;
  value |= value >> 2;
  value |= value >> 4;
  value |= value >> 8;
  value |= value >> 16;
  value |= value >> 32;
  return tab64[((uint64_t)((value - (value >> 1)) * 0x07EDD5E59A4E28C2)) >> 58];
}
// 2 end

// 3
#define LOG2(X) ((unsigned)(8 * sizeof(unsigned long long) - __builtin_clzll((X)) - 1))
// 3 end

// 4
inline uint32_t log2(const uint32_t x) {
  uint32_t y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}
// 4 end

void log2_benchmark() {
  int iterations = 1e7, range = 1e6;
  auto begin = std::chrono::high_resolution_clock::now(),
       end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::nano> duration;

  begin = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    uint64_t num = rand_in_range(1, range);
    float result = std::log2(num);
  }
  end = std::chrono::high_resolution_clock::now();
  duration = end - begin;
  double t1 = duration.count() / iterations;

  begin = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    uint64_t num = rand_in_range(1, range);
    int result = log2_64(num);
  }
  end = std::chrono::high_resolution_clock::now();
  duration = end - begin;
  double t2 = duration.count() / iterations;

  begin = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    uint64_t num = rand_in_range(1, range);
    unsigned result = LOG2(num);
  }
  end = std::chrono::high_resolution_clock::now();
  duration = end - begin;
  double t3 = duration.count() / iterations;

  begin = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    uint32_t num = rand_in_range(1, range);
    uint32_t result = log2(num);
  }
  end = std::chrono::high_resolution_clock::now();
  duration = end - begin;
  double t4 = duration.count() / iterations;

  printf("iterations: %d, range: %d\n", iterations, range);
  printf("t1=%f\nt2=%f\nt3=%f\nt4=%f\n", t1, t2, t3, t4);
}

