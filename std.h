#pragma once

#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
#include <cmath>

#include "rb_tree.h"
#include "avl_tree.h"
#include "avl_os_tree.h"

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

typedef long long int ll;
typedef unsigned long long int ull;

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
    die("gen_array: failed to allocate memory for constructor");
  }
  gen_array(size_t n_length, T initial_value) try : length(n_length) {
    _data = new T [length];
    for (size_t i = 0; i < length; ++i)
      _data[i] = initial_value;
  } catch (...) {
    die("gen_array: failed to allocate memory for constructor with value");
  }
  gen_array(std::initializer_list<T> l) try : length(l.size()) {
    _data = new T [length];
    size_t i = 0;
    for (const auto &e : l)
      _data[i++] = e;
  } catch (...) {
    die("gen_array: failed to allocate memory from initializer list");
  }
  gen_array(const gen_array &other) {
    operator=(other);
  }
  ~gen_array() {
    if (!_data)
      delete [] _data;
  }
  gen_array& operator=(const gen_array &other) {
    try {
      length = other.length;
      if (!_data)
        delete [] _data;
      _data = new T [length];
      std::memcpy(_data, other._data, other.length * sizeof(T));
    } catch (...) {
      die("gen_array: failed to allocate memory for assignment copy");
    }
    return *this;
  }
  T& operator[](size_t i) const {
    if (i >= 1 && i <= length)
      return _data[i - 1];
    else
      die("gen_array: indexing array out of bounds (%d)", (int)i);
  }
  inline bool operator==(const gen_array<T> &o) {
    if (length != o.length)
      return false;
    for (size_t i = 1; i < length; ++i)
      if (_data[i - 1] != o[i])
        return false;
    return true;
  }
  void randomize(int min, int max) {
    for (size_t i = 0; i < length; ++i)
      _data[i] = rand_in_range(min, max);
  }
  void randomize() {
    randomize(1, 30);
  }
  void randomize_walk(int min, int max) {
    int prev = 0;
    for (size_t i = 0; i < length; ++i) {
      _data[i] = prev + rand_in_range(min, max);
      prev = _data[i];
    }
  }
  void randomize_walk() {
    randomize_walk(-3, 5);
  }
  void sequence() {
    for (size_t i = 0; i < length; ++i)
      _data[i] = i + 1;
  }
  void scramble() {
    for (size_t i = 0; i < length; ++i)
      std::swap(_data[i], _data[rand_in_range(0, length - 1)]);
  }
  void print() {
    printf("[");
    for (size_t i = 0; i < length; ++i)
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
  size_t rows, columns;
  gen_matrix() : _data(nullptr), rows(0) {};
  gen_matrix(size_t n_rows, size_t n_columns) try
    : rows(n_rows)
    , columns(n_columns) {
    _data = new T [rows * columns];
  } catch (...) {
    die("gen_matrix: failed to allocate memory for constructor");
  }
  gen_matrix(size_t n_rows, size_t n_columns, std::initializer_list<T> l) try
    : rows(n_rows)
    , columns(n_columns) {
    _data = new T [rows * columns];
    size_t i = 0;
    for (const auto &e : l)
      _data[i++] = e;
  } catch (...) {
    die("gen_matrix: failed to allocate memory for initializer list");
  }
  gen_matrix(const gen_matrix &other) {
    operator=(other);
  }
  ~gen_matrix() {
    if (!_data)
      delete [] _data;
  }
  gen_matrix& operator=(gen_matrix other) {
    try {
      rows = other.rows;
      columns = other.columns;
      if (!_data)
        delete [] _data;
      _data = new T [rows * columns];
      std::memcpy(_data, other._data, other.rows * other.columns * sizeof(T));
    } catch (...) {
      die("gen_matrix: failed to allocate memory for assignment copy");
    }
    return *this;
  }
  T& at(size_t y, size_t x) {
    if (y >= 1 && y <= rows && x >= 1 && x <= columns)
      return _data[(y - 1) * columns + (x - 1)];
    else
      die("gen_matrix: indexing matrix out of bounds (%d, %d)", (int)y, (int)x);
  }
  void randomize(int min, int max) {
    for (size_t y = 1; y <= rows; ++y)
      for (size_t x = 1; x <= columns; ++x)
        at(y, x) = rand_in_range(min, max);
  }
  void randomize() {
    randomize(1, 50);
  }
  void print() {
    for (size_t y = 1; y <= rows; ++y) {
      for (size_t x = 1; x <= columns; ++x)
        if (at(y, x) == inf)
          printf("inf\t");
        else
          printf("%d\t", at(y, x));
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

    for (int i = 0; i < node_info_w; ++i)
      s[2 * depth][offset + left_w + i] = node_info[i];

    if (depth && is_left) {
      for (int i = 0; i < node_info_w + right_w - 1; ++i)
        s[2 * depth - 2][offset + left_w + node_info_w/2 + i + 1] = '_';
      s[2 * depth - 1][offset + left_w + node_info_w/2] = '/';
    } else if (depth && !is_left) {
      for (int i = 0; i < left_w + node_info_w - 3; ++i)
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
class gen_max_priority_queue : public gen_heap<T> {
public:
  T maximum() {
    return this->_data[1];
  }
  T extract_max() {
    if (this->heap_size < 1)
      die("heap underflow");
    T max = this->_data[1];
    this->_data[1] = this->_data[this->heap_size];
    --this->heap_size;
    this->max_heapify(1);
    return max;
  }
  void increase_key(size_t i, T k) {
    if (k < this->_data[i])
      die("new key is smalller than current");
    this->_data[i] = k;
    while (i > 1 && this->_data[this->parent(i)] < this->_data[i]) {
      std::swap(this->_data[i], this->_data[this->parent(i)]);
      i = this->parent(i);
    }
  }
  void insert(T k) {
    ++this->heap_size;
    this->_data[this->heap_size] = neginf;
    this->increase_key(this->heap_size, k);
  }
};

typedef gen_max_priority_queue<int> max_priority_queue;

template <typename T>
class gen_young_tableau {
  gen_matrix<T> _data;
public:
  size_t records;
  gen_young_tableau(size_t rows, size_t columns)
    : _data(rows, columns)
    , records(0) {
    for (size_t y = 1; y <= rows; ++y)
      for (size_t x = 1; x <= columns; ++x)
        _data.at(y, x) = inf;
  }
  gen_young_tableau(size_t rows, size_t columns, gen_array<T> array_elems)
    : gen_young_tableau(rows, columns) {
    gen_array<T> array_copy = array_elems;
    insertion_sort(array_copy);
    for (size_t i = 1, y = 1; y <= rows; ++y)
      for (size_t x = 1; x <= columns; ++x)
        _data.at(y, x) = i <= array_copy.length ? array_copy[i++] : inf;
  }
  bool empty() {
    return _data.at(1, 1) == inf;
  }
  bool full() {
    return _data.at(_data.rows, _data.columns) < inf;
  }
  T extract_min() {
    T val = _data.at(1, 1);
    _data.at(1, 1) = inf;
    youngify(1, 1);
    return val;
  }
  void youngify(size_t y, size_t x) {
    size_t smallest_y = y, smallest_x = x;
    if (y + 1 <= _data.rows && _data.at(y + 1, x) < _data.at(y, x)) {
      smallest_y = y + 1;
      smallest_x = x;
    }
    if (x + 1 <= _data.columns && _data.at(y, x + 1) < _data.at(y, x)) {
      smallest_y = y;
      smallest_x = x + 1;
    }
    if (smallest_y != y || smallest_x != x) {
      std::swap(_data.at(y, x), _data.at(smallest_y, smallest_x));
      youngify(smallest_y, smallest_x);
    }
  }
  void insert(T k) {
    // decrease_key(rows, columns, k);
    _data.at(_data.rows, _data.columns) = k;
  }
  void decrease_key(size_t i, size_t j, T k) {
    if (_data.at(i, j) <= k)
      die("error");
    _data.at(i, j) = k;
    T threshold = inf;
    size_t largest_i = i, largest_j = j;
    while ((i > 1 || j > 1) && _data.at(i, j) < threshold) {
      std::swap(_data.at(i, j), _data.at(largest_i, largest_j));
      i = largest_i;
      j = largest_j;
      if (i - 1 >= 1 && _data.at(i, j) < _data.at(i - 1, j)) {
        largest_i = i - 1;
        largest_j = j;
      }
      if (j - 1 >= 1 && _data.at(i, j) < _data.at(i, j - 1)) {
        largest_i = i;
        largest_j = j - 1;
      }
      threshold = _data.at(largest_i, largest_j);
    }
  }
  void youngify_rev(size_t y, size_t x) {
    size_t largest_y = y, largest_x = x;
    if (y - 1 >= 1 && _data.at(y, x) < _data.at(y - 1, x)) {
      largest_y = y - 1;
      largest_x = x;
    }
    if (x - 1 >= 1 && _data.at(y, x) < _data.at(y, x - 1)) {
      largest_y = y;
      largest_x = x - 1;
    }
    if (largest_y != y || largest_x != x) {
      std::swap(_data.at(y, x), _data.at(largest_y, largest_x));
      youngify_rev(largest_y, largest_x);
    }
  }
  bool search(T k) {
    size_t y = 1, x = _data.columns;
    while (1) {
      T element = _data.at(y, x);
      if (element == k)
        return true;
      else if (element > k) {
        if (x > 1)
          --x;
        else
          return false;
      } else if (element < k) {
        if (y < _data.rows)
          ++y;
        else
          return false;
      }
    }
  }
  void print() {
    _data.print();
  }
};

typedef gen_young_tableau<int> young_tableau;

struct interval {
  float l, r;
};

// untested
#if 0
template <typename T>
struct lcrs_tree_node {
  T val;
  lcrs_tree_node *parent, *left, *right;
  lcrs_tree_node(const T &n_val, lcrs_tree_node *n_parent = nullptr
      , lcrs_tree_node *n_right = nullptr, lcrs_tree_node *n_left = nullptr)
    : val(n_val), parent(n_parent), left(n_left), right(n_right) {}
  void add_child(const T &c_val) {
    if (left == nullptr)
      left = new lcrs_tree_node(c_val, this);
    else {
      lcrs_tree_node *w = left;
      while (w->right != nullptr)
        w = w->right;
      w->right = new lcrs_tree_node(c_val, this, w);
    }
  }
  void child(size_t i) {
    lcrs_tree_node *c = left;
    while (i-- - 1 != 0)
      c = c->right;
    return c;
  }
};

template <typename T>
class heapy_bst {
  std::vector<T> _data;
  size_t occupied;
  void expand(size_t i) {
    if (i >= _data.size())
      _data.resize(i + 1);
  }
public:
  heapy_bst() : occupied(0) {}
  size_t parent(size_t i) {
    return i / 2;
  }
  size_t left(size_t i) {
    return 2 * i;
  }
  size_t right(size_t i) {
    return 2 * i + 1;
  }
  void insert(T val) {
    if (occupied == 0)
      _data[1] = val;
    size_t i = 1, new_idx;
    if (val < _data[i]) {
      size_t new_idx = left(i);
      expand(new_idx);
      _data[new_idx] = val;
    }
  }
};
#endif

// should not be used, since some parts (delete) have bugs
template <typename T>
class gen_bst {
  int _print(gen_bst *n, bool is_left, int offset, int depth
      , std::vector<std::string> &s, size_t width) {
    if (n == nullptr)
      return 0;
    std::string node_info = std::to_string(n->key);
    int node_info_w = (int)node_info.size();

    int left_w = _print(n->left, 1, offset, depth + 1, s, width);
    int right_w = _print(n->right, 0, offset + left_w + node_info_w, depth + 1
        , s, width);

    if (2 * (size_t)depth + 1 > s.size())
      s.resize(2 * depth + 1, std::string(width, ' '));

    for (int i = 0; i < node_info_w; ++i)
      s[2 * depth][offset + left_w + i] = node_info[i];

    if (depth && is_left) {
      for (int i = 0; i < node_info_w + right_w - 1; ++i)
        s[2 * depth - 2][offset + left_w + node_info_w/2 + i + 1] = '_';
      s[2 * depth - 1][offset + left_w + node_info_w/2] = '/';
    } else if (depth && !is_left) {
      for (int i = 0; i < left_w + node_info_w - 3; ++i)
        s[2 * depth - 2][offset - node_info_w/2 + i + 1] = '_';
      s[2 * depth - 1][offset + left_w + node_info_w/2 - 1] = '\\';
    }

    return left_w + node_info_w + right_w;
  }
public:
  gen_bst *left, *right, *parent;
  T key;
  gen_bst(T n_key)
    : left(nullptr)
    , right(nullptr)
    , parent(nullptr)
    , key(n_key) {}
  gen_bst(T n_key, gen_bst *n_parent)
    : left(nullptr)
    , right(nullptr)
    , parent(n_parent)
    , key(n_key) {}
  gen_bst(T n_key, gen_bst *n_left, gen_bst *n_right, gen_bst *n_parent)
    : left(n_left)
    , right(n_right)
    , parent(n_parent)
    , key(n_key) {}
  void insert_rec(T new_key) {
    if (new_key < key) {
      if (left == nullptr)
        left = new gen_bst(new_key, this);
      else
        left->insert(new_key);
    } else {
      if (right == nullptr)
        right = new gen_bst(new_key, this);
      else
        right->insert(new_key);
    }
  }
  void insert(T new_key) {
    gen_bst *y = nullptr, *x = this;
    while (x != nullptr) {
      y = x;
      if (new_key < x->key)
        x = x->left;
      else
        x = x->right;
    }
    if (new_key < y->key)
      y->left = new gen_bst(new_key, y);
    else
      y->right = new gen_bst(new_key, y);
  }
  void transplant(gen_bst *u, gen_bst *v) {
    if (u->parent == nullptr)
      u = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;
    if (v != nullptr)
      v->parent = u->parent;
  }
  void delete_node(gen_bst *z) {
    if (z->left == nullptr)
      transplant(z, z->right);
    else if (z->right == nullptr)
      transplant(z, z->left);
    else {
      gen_bst *y = z->right->min();
      if (y->parent != z) {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
    }
  }
  gen_bst* search(T query_key) {
    gen_bst *q = this;
    while (q != nullptr && query_key != q->key)
      if (query_key < q->key)
        q = q->left;
      else
        q = q->right;
    return q;
  }
  gen_bst* min() {
    gen_bst *q = this;
    while (q->left != nullptr)
      q = q->left;
    return q;
  }
  gen_bst* max() {
    gen_bst *q = this;
    while (q->right != nullptr)
      q = q->right;
    return q;
  }
  T succ() {
    gen_bst *x = this;
    if (x->right != nullptr)
      return x->right->min();
    gen_bst *y = x->parent;
    while (y != nullptr && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y->key;
  }
  T pred() {
    gen_bst *x = this;
    if (x->left != nullptr)
      return x->left->max();
    gen_bst *y = x->parent;
    while (y != nullptr && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y->key;
  }
  void print(size_t width = 80) {
    std::vector<std::string> s(1, std::string(width, ' '));
    _print(this, 0, 0, 0, s, width);
    for (size_t i = 0; i < s.size(); ++i)
      printf("%s\n", s[i].c_str());
  }
};

typedef gen_bst<int> bst;

int array_equilibrium(array A);
size_t sum_of_multiples();

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
void quicksort(array &A);
void randomized_quicksort(array &A);
void quicksort_hoare(array &A);
// void fuzzy_sort(gen_array<interval> &A);
void counting_sort(array &A);
void preprocess_count_integers_in_range(array &A, std::vector<int> &C, int &max);
int count_integers_in_range(array &A, array &C, int max, int a, int b);
void radix_sort(array &A);
void in_place_counting_sort(array &A);
void minmax(array A, int &min, int &max);
int second_smallest(array A);
int randomized_select(array A, size_t i);
int randomized_select_iterative(array A, size_t i);
int select(array A, size_t i);
void k_closest_to_median(array A, size_t k);
// int small_order_select(array A, size_t i);
int cut_rod1(array p, size_t n);
int cut_rod2(array p, size_t n);
int cut_rod3(array p, size_t n);
int cut_rod_with_cost(array p, int c, size_t n);
ull fib(int i);
ull fib_dp(int i);
ull fib_dp2(int i);
void matrix_chain_order(std::vector<int> p, matrix &m, matrix &s);
void longest_common_subsequence(array X, array Y);
void longest_monotonically_increasing_subsequence_simple(array X);
void longest_monotonically_increasing_subsequence(std::vector<int> X);

