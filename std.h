#pragma once

#include <fstream>
#include <cstring>

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

template <typename T>
class gen_array {
  T *_data;
  gen_array& operator=(gen_array other) {
    this->swap(other);
    return *this;
  }
  void swap(gen_array& other) {
    std::swap(_data, other._data);
    std::swap(length, other.length);
  }
public:
  size_t length;
  gen_array(size_t n_length) try : length(n_length) {
    _data = new T [length];
  } catch (...) {
    die("gen_array: failed to allocate memory");
  }
  gen_array(std::initializer_list<T> l) try {
    length = l.size();
    _data = new T [length];
    size_t j = 0;
    for (const auto &i : l)
      _data[j++] = i;
  } catch (...) {
    die("gen_array: failed to allocate memory from initializer list");
  }
  gen_array(const gen_array &other) try {
    length = other.length;
    _data = new T [length];
    std::memcpy(_data, other._data, length);
  } catch (...) {
    die("gen_array: failed to allocate memory for copy");
  }
  ~gen_array() {
    delete [] _data;
  }
  T& operator[](size_t i) {
    if (i >= 1 && i <= length)
      return _data[i - 1];
    else
      die("gen_array: indexing array out of bounds (%d)", i);
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

typedef gen_array<int> array;

// maybe value
struct mvalue {
  int v;
  bool nil;
  mvalue() : nil(true) {}
  mvalue* operator=(int n_v) {
    v = n_v;
    nil = false;
  }
  void print() {
    if (nil)
      puts("nil");
    else
      printf("%d\n", v);
  }
};

mvalue search(array &A, int v);
void insertion_sort(array &A);
void selection_sort(array &A);
void merge_sort(array &A);
mvalue bsearch(array &A, int v);
bool sum_exists(array &S, int x);

