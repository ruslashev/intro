#pragma once

#include <fstream>
#include <cstring>
#include <climits>

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

const int neginf = INT_MIN, inf = INT_MAX;

static int rand_in_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

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
    for (size_t i = 0; i < length; i++)
      _data[i] = i + 1;
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
      die("gen_array: indexing array out of bounds (%d)", (int)i);
  }
  void randomize(int min, int max) {
    for (size_t i = 0; i < length; i++)
      _data[i] = rand_in_range(min, max);
  }
  void randomize() {
    randomize(1, 50);
  }
  void randomize_walk(int min, int max) {
    int prev = 0;
    for (size_t i = 0; i < length; i++) {
      _data[i] = prev + rand_in_range(min, max);
      prev = _data[i];
    }
  }
  void randomize_walk() {
    randomize_walk(-3, 5);
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
  mvalue& operator=(int n_v) {
    v = n_v;
    nil = false;
    return *this;
  }
  void print() {
    if (nil)
      puts("nil");
    else
      printf("%d\n", v);
  }
};

struct subarray {
  int start, end, sum;
};

template <typename T>
class gen_matrix {
  T *_data;
  gen_matrix& operator=(gen_matrix other) {
    this->swap(other);
    return *this;
  }
  void swap(gen_matrix& other) {
    std::swap(_data, other._data);
    std::swap(rows, other.rows);
  }
public:
  size_t rows;
  gen_matrix(size_t n_rows) try : rows(n_rows) {
    _data = new T [rows * rows];
  } catch (...) {
    die("gen_matrix: failed to allocate memory");
  }
  /*
  gen_matrix(std::initializer_list<T> l) try {
    rows = l.size();
    _data = new T [rows];
    size_t j = 0;
    for (const auto &i : l)
      _data[j++] = i;
  } catch (...) {
    die("gen_matrix: failed to allocate memory from initializer list");
  }
  */
  gen_matrix(const gen_matrix &other) try {
    rows = other.rows;
    _data = new T [rows * rows];
    std::memcpy(_data, other._data, rows * rows);
  } catch (...) {
    die("gen_matrix: failed to allocate memory for copy");
  }
  ~gen_matrix() {
    delete [] _data;
  }
  T& at(size_t y, size_t x) {
    if (y >= 1 && y <= rows && x >= 1 && x <= rows)
      return _data[y * rows + x];
    else
      die("gen_matrix: indexing array out of bounds (%d, %d)", (int)y, (int)x);
  }
  void randomize(int min, int max) {
    for (size_t y = 0; y < rows; y++)
      for (size_t x = 0; x < rows; x++)
        at(y, x) = rand_in_range(min, max);
  }
  void randomize() {
    randomize(1, 50);
  }
  void print() {
    for (size_t y = 0; y < rows; y++) {
      for (size_t x = 0; x < rows; x++)
        printf("%d ", at(y, x));
      printf("\n");
    }
  }
};

typedef gen_matrix<int> matrix;

mvalue search(array &A, int v);
void insertion_sort(array &A);
void selection_sort(array &A);
void merge_sort(array &A);
mvalue bsearch(array &A, int v);
bool sum_exists(array &S, int x);
int inversions(array &A);
subarray find_maximum_subarray(array &A);
subarray find_maximum_subarray_lin(array &A);
matrix square_matrix_mult(matrix &A, matrix &B);
void randomize_in_place(array &A);

