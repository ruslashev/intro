#pragma once

template <typename T>
struct gen_avl_node {
  T key;
  size_t height;
  gen_avl_node *left, *right;
  gen_avl_node(T n_key) : key(n_key), height(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class gen_avl_tree {
  gen_avl_node<T>* insert(gen_avl_node<T> *x, T key) {
    if (!x)
      return new gen_avl_node<T>(key);
    if (key < x->key)
      x->left = insert(x->left, key);
    else
      x->right = insert(x->right, key);
    return balance(x);
  }
  gen_avl_node<T>* balance(gen_avl_node<T> *x) {
    x->height = std::max(height(x->left), height(x->right)) + 1;
    if (diff(x) >= 2) {
      if (diff(x->right) < 0)
        x->right = right_rotate(x->right);
      return left_rotate(x);
    } else if (diff(x) <= -2) {
      if (diff(x->left) > 0)
        x->left = left_rotate(x->left);
      return right_rotate(x);
    }
    return x;
  }
  size_t height(gen_avl_node<T> *x) {
    return x != nullptr ? x->height : 0;
  }
  int diff(gen_avl_node<T> *x) {
    return height(x->right) - height(x->left);
  }
  gen_avl_node<T>* right_rotate(gen_avl_node<T> *x) {
    gen_avl_node<T> *y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
  }
  gen_avl_node<T>* left_rotate(gen_avl_node<T> *x) {
    gen_avl_node<T> *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
  }
  gen_avl_node<T>* delete_key(gen_avl_node<T> *x, T key) {
    if (x == nullptr)
      return nullptr;
    if (key < x->key)
      x->left = delete_key(x->left, key);
    else if (key > x->key)
      x->right = delete_key(x->right, key);
    else {
      gen_avl_node<T> *l = x->left, *r = x->right;
      delete x;
      if (r == nullptr)
        return l;
      gen_avl_node<T> *m = min(r);
      m->right = delete_min(r);
      m->left = l;
      return balance(m);
    }
    return balance(x);
  }
  gen_avl_node<T>* min(gen_avl_node<T> *x) {
    return x->left != nullptr ? min(x->left) : x;
  }
  gen_avl_node<T>* delete_min(gen_avl_node<T> *x) {
    if (x->left == nullptr)
      return x->right;
    x->left = delete_min(x->left);
    return balance(x);
  }
  int _print(gen_avl_node<T> *n, bool is_left, int offset, int depth
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
  gen_avl_node<T> *root;
  gen_avl_tree() : root(nullptr) {}
  void insert(T key) {
    root = insert(root, key);
  }
  void delete_key(T key) {
    root = delete_key(root, key);
  }
  void print(size_t width = 80) {
    if (root == nullptr) {
      puts("(null)");
      return;
    }
    std::vector<std::string> s(1, std::string(width, ' '));
    _print(root, 0, 0, 0, s, width);
    for (size_t i = 0; i < s.size(); ++i)
      printf("%s\n", s[i].c_str());
  }
};

typedef gen_avl_node<int> avl_node;
typedef gen_avl_tree<int> avl_tree;

