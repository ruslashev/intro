#pragma once

#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
#include <cmath>

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

const int neginf = INT_MIN, inf = INT_MAX;

static int rand_in_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

template <typename T>
class gen_array {
  T *_data;
public:
  size_t length;
  gen_array() : _data(nullptr), length(0) {}
  gen_array(size_t n_length) try : length(n_length) {
    _data = new T [length];
  } catch (...) {
    die("gen_array: failed to allocate memory");
  }
  gen_array(std::initializer_list<T> l) try : length(l.size()) {
    _data = new T [length];
    size_t i = 0;
    for (const auto &e : l)
      _data[i++] = e;
  } catch (...) {
    die("gen_array: failed to allocate memory from initializer list");
  }
  gen_array(const gen_array &other) try {
    operator=(other);
  } catch (...) {
    die("gen_array: failed to allocate memory for copy");
  }
  ~gen_array() {
    delete [] _data;
  }
  gen_array& operator=(const gen_array &other) {
    length = other.length;
    if (!_data)
      delete [] _data;
    _data = new T [length];
    std::memcpy(_data, other._data, other.length * sizeof(T));
    return *this;
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
    randomize(1, 30);
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
    printf("[");
    for (size_t i = 0; i < length; i++)
      printf("%d%s", _data[i], i == length - 1 ? "" : " ");
    printf("]\n");
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
public:
  size_t rows;
  gen_matrix() : _data(nullptr), rows(0);
  gen_matrix(size_t n_rows) try : rows(n_rows) {
    _data = new T [rows * rows];
  } catch (...) {
    die("gen_matrix: failed to allocate memory");
  }
  gen_matrix(const gen_matrix &other) try {
    operator=(other);
  } catch (...) {
    die("gen_matrix: failed to allocate memory for copy");
  }
  ~gen_matrix() {
    delete [] _data;
  }
  gen_matrix& operator=(gen_matrix other) {
    rows = other.rows;
    if (!_data)
      delete [] _data;
    _data = new T [rows * rows];
    std::memcpy(_data, other._data, other.rows * other.rows * sizeof(T));
    return *this;
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
  void print() const {
    for (size_t y = 0; y < rows; y++) {
      for (size_t x = 0; x < rows; x++)
        printf("%d ", at(y, x));
      printf("\n");
    }
  }
};

typedef gen_matrix<int> matrix;

template <typename T>
class gen_heap {
protected:
  gen_array<T> _data;
  int _print(size_t idx, bool is_left, int offset, int depth, std::vector<std::string> &s) {
    if (idx > heap_size)
      return 0;
    std::string node_info = std::to_string(_data[idx]);
    int node_info_w = (int)node_info.size();

    int left_w = _print(left(idx), 1, offset, depth + 1, s);
    int right_w = _print(right(idx), 0, offset + left_w + node_info_w, depth + 1, s);

    for (int i = 0; i < node_info_w; i++)
      s[2 * depth][offset + left_w + i] = node_info[i];

    if (depth && is_left) {
      for (int i = 0; i < node_info_w + right_w - 1; i++)
        s[2 * depth - 2][offset + left_w + node_info_w/2 + i + 1] = '_';
      s[2 * depth - 1][offset + left_w + node_info_w/2] = '/';
    } else if (depth && !is_left) {
      for (int i = 0; i < left_w + node_info_w - 3; i++)
        s[2 * depth - 2][offset - node_info_w/2 + i + 1] = '_';
      s[2 * depth - 1][offset + left_w + node_info_w/2 - 1] = '\\';
    }

    return left_w + node_info_w + right_w;
  }
public:
  size_t heap_size;
  gen_heap() : heap_size(0) {}
  gen_heap(const gen_array<T> &A) : _data(A), heap_size(A.length) {
    build_max_heap();
  }
  gen_heap(std::initializer_list<T> l) : _data(l), heap_size(l.size()) {
    build_max_heap();
  }
  size_t parent(size_t i) {
    return i / 2;
  }
  size_t left(size_t i) {
    return 2 * i;
  }
  size_t right(size_t i) {
    return 2 * i + 1;
  }
  void max_heapify_rec(size_t i) {
    size_t l = left(i), r = right(i), largest;
    if (l <= heap_size && _data[l] > _data[i])
      largest = l;
    else
      largest = i;
    if (r <= heap_size && _data[r] > _data[largest])
      largest = r;
    if (largest != i) {
      T t = _data[i];
      _data[i] = _data[largest];
      _data[largest] = t;
      max_heapify(largest);
    }
  }
  void max_heapify(size_t i) {
    while (i < heap_size) {
      size_t l = left(i), r = right(i), largest;
      if (l <= heap_size && _data[l] > _data[i])
        largest = l;
      else
        largest = i;
      if (r <= heap_size && _data[r] > _data[largest])
        largest = r;
      if (largest != i) {
        T t = _data[i];
        _data[i] = _data[largest];
        _data[largest] = t;
        i = largest;
      } else
        break;
    }
  }
  void build_max_heap() {
    for (size_t i = heap_size / 2; i >= 1; --i)
      max_heapify(i);
  }
  void heapsort() {
    for (size_t i = heap_size; i >= 2; --i) {
      std::swap(_data[1], _data[i]);
      --heap_size;
      max_heapify(1);
    }
  }
  size_t height() {
    if (heap_size == 0)
      return 0;
    else
      return std::floor(std::log2(heap_size));
  }
  size_t depth() {
    size_t i = 1, depth = 0;
    while (i <= heap_size) {
      i = left(i);
      ++depth;
    }
    return depth;
  }
  void print(size_t width = 80) {
    _data.print();
    std::vector<std::string> s(depth() * 2 - 1, std::string(width, ' '));
    _print(1, 0, 0, 0, s);
    for (size_t i = 0; i < depth() * 2 - 1; ++i)
      printf("%s\n", s[i].c_str());
  }
};

typedef gen_heap<int> heap;

template <typename T>
class gen_priority_queue : public gen_heap<T> {
public:
  T maximum() {
    return _data[1];
  }
  T extract_max() {
    if (heap_size < 1)
      die("heap underflow");
    T max = _data[1];
    _data[1] = _data[heap_size];
    --heap_size;
    max_heapify(1);
    return max;
  }
  void increase_key(size_t i, T k) {
    if (k < _data[i])
      die("new key is smalller than current");
    _data[i] = k;
    while (i > 1 && A[parent(i)] < A[i]) {
      std::swap(A[i], A[parent(i)]);
      i = parent(i);
    }
  }
  void insert(T k) {
    ++heap_size;
    _data[heap_size] = neginf;
    increase_key(heap_size, k);
  }
};

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
int coin_streak(int n);
void log2_benchmark();
void heapsort(array &A);

