#pragma once

#include <fstream>
#include <cstring>

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

class array {
  int *_data;
  array& operator=(array other) {
    this->swap(other);
    return *this;
  }
  void swap(array& other) {
    std::swap(_data, other._data);
    std::swap(length, other.length);
  }
public:
  size_t length;
  array(size_t n_length) try : length(n_length) {
    _data = new int [length];
  } catch (...) {
    die("array: failed to allocate memory");
  }
  array(const array &other) try {
    length = other.length;
    _data = new int [length];
    std::memcpy(_data, other._data, length);
  } catch (...) {
    die("array: failed to allocate memory for copy");
  }
  ~array() {
    delete [] _data;
  }
  int& operator[](size_t i) {
    if (i >= 1 && i <= length)
      return _data[i - 1];
    else
      die("array: indexing array out of bounds (%d)\n", i);
  }
  void randomize() {
    randomize(1, 50);
  }
  void randomize(int min, int max) {
    for (size_t i = 0; i < length; i++)
      _data[i] = min + rand() % (max - min + 1);
  }
  void print() {
    for (size_t i = 0; i < length; i++)
      printf("%d ", _data[i]);
    printf("\n");
  }
};

