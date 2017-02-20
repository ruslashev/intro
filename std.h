#pragma once

#include <fstream>

template <int _size>
struct array {
  int data[_size];
  int size = _size;
  int& operator[](size_t i) {
    if (i >= 1 && i <= _size)
      return data[i - 1];
    else {
      printf("error: indexing array out of bounds (%d)\n", i);
      exit(1);
    }
  }
  void randomize() {
    randomize(1, 30);
  }
  void randomize(int min, int max) {
    for (size_t i = 0; i < _size; i++)
      data[i] = min + rand() % (max - min + 1);
  }
  void print() {
    for (int i = 0; i < _size; i++)
      printf("%d ", data[i]);
    printf("\n");
  }
};

