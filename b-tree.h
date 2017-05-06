#pragma once

template <typename T>
struct gen_btree_node {
  bool leaf;
  size_t n;
  std::vector<T> keys;
  std::vector<gen_btree_node*> children;
  void sort_keys();
  gen_btree_node(size_t t) : n(0) {
    keys.resize(2 * t - 1);
    children.resize(2 * t);
  }
};

template <typename T>
struct gen_btree {
  size_t t;
  void search(gen_btree_node<T> *x, T key, gen_btree_node<T> **result
      , size_t *result_idx) {
    size_t i = 0;
    while (i <= x->n && key > x->keys[i])
      ++i;
    if (i <= x->n && key == x->keys[i]) {
      *result = x;
      *result_idx = i;
    } else if (x->leaf)
      *result = nullptr;
    else
      search(x->children[i], key, result, result_idx);
  }
  void split_child(gen_btree_node<T> *x, size_t i, gen_btree_node<T> *y) {
    gen_btree_node<T> *z = new gen_btree_node<T>(t);
    z->leaf = y->leaf;
    z->n = t - 1;
    for (size_t j = 0; j < t - 1; ++j)
      z->keys[j] = y->keys[j + t];
    if (!y->leaf)
      for (size_t j = 0; j < t; ++j)
        z->children[j] = y->children[j + t];
    y->n = t - 1;
    for (size_t j = x->n; j >= i + 1; --j)
      x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;
    for (int j = x->n - 1; j >= (int)i; --j)
      x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[t - 1];
    ++x->n;
  }
  void insert_nonfull(gen_btree_node<T> *x, T key) {
    int i = x->n - 1;
    if (x->leaf) {
      while (i >= 0 && key < x->keys[i]) {
        x->keys[i + 1] = x->keys[i];
        --i;
      }
      x->keys[i + 1] = key;
      ++x->n;
    } else {
      while (i >= 0 && key < x->keys[i])
        --i;
      ++i;
      if (x->children[i]->n == 2 * t - 1) {
        split_child(x, i, x->children[i]);
        if (key > x->keys[i])
          ++i;
      }
      insert_nonfull(x->children[i], key);
    }
  }
  void print_node(gen_btree_node<T> *x, int indent) {
    for (int j = 0; j < indent; ++j)
      printf("  ");
    if (!x) {
      printf("(nil)\n");
      return;
    }
    printf("(");
    for (size_t i = 0; i < x->n; ++i) {
      printf("%d", x->keys[i]);
      if (i != x->n - 1)
        printf(",");
    }
    if (x->children.size() == 0)
      printf(") -x\n");
    else {
      printf(") ->\n");
      for (size_t i = 0; i < x->children.size(); ++i)
        print_node(x->children[i], indent + 1);
    }
  }
public:
  gen_btree_node<T> *root;
  gen_btree(size_t n_t) : t(n_t), root(nullptr) {}
  void insert(T key) {
    if (root == nullptr) {
      root = new gen_btree_node<T>(t);
      root->leaf = true;
      root->keys[0] = key;
      root->n = 1;
    } else {
      if (root->n == 2 * t - 1) {
        gen_btree_node<T> *s = new gen_btree_node<T>(t);
        s->leaf = false;
        s->children[0] = root;
        split_child(s, 0, root);
        size_t i = 0;
        if (s->keys[0] < key)
          ++i;
        insert_nonfull(s->children[i], key);
        root = s;
      } else
        insert_nonfull(root, key);
    }
  }
  void search(T key, gen_btree_node<T> **result , size_t *result_idx) {
    return search(root, key);
  }
  void print() {
    print_node(root, 0);
  }
};

typedef gen_btree<int> btree;

