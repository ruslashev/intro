#pragma once

#include <vector>
#include <string>

template <typename T>
struct gen_fib_heap_node {
  T value;
  bool marked;
  int degree;
  gen_fib_heap_node<T> *left, *right, *children, *parent;
  gen_fib_heap_node(T n_value)
    : value(n_value)
    , marked(false)
    , degree(0)
    , left(this)
    , right(this)
    , children(nullptr)
    , parent(nullptr) {
  }
  gen_fib_heap_node(gen_fib_heap_node<T> *x)
    : value(x->value)
    , marked(x->marked)
    , degree(0)
    , left(this)
    , right(this)
    , parent(nullptr) {
    if (x->children != nullptr) {
      gen_fib_heap_node<T> *y = x->children;
      do {
        add_child(y);
        y = y->right;
      } while (y != x->children);
    } else
      children = nullptr;
  }
  gen_fib_heap_node<T>* unlink() {
    gen_fib_heap_node<T> *x, *y;
    if (right == this) {
      if (parent != nullptr) {
        parent->children = nullptr;
        if (parent->marked) {
          x = parent;
          y = x;
          while (y->parent != nullptr)
            y = y->parent;
          if (x != y) {
            x->marked = false;
            y->append_node(x);
            x->unlink();
          }
        } else
          parent->marked = true;
        parent = nullptr;
      }
      return this;
    } else {
      right->left = left;
      left->right = right;
      if (parent && parent->children == this)
        parent->children = right;
      if (parent && parent->marked) {
        x = parent;
        y = x;
        while (y->parent)
          y = y->parent;
        if (x != y) {
          x->marked = false;
          y->append_node(x);
        }
        x->unlink();
      } else if (parent)
        parent->marked = true;
      right = this;
      left = this;
      parent = nullptr;
    }
    return this;
  }
  gen_fib_heap_node<T>* append_node(gen_fib_heap_node<T> *x) {
    gen_fib_heap_node<T> *n = new gen_fib_heap_node<T>(x);
    n->right = right;
    n->left = this;
    if (right != this)
      right->left = n;
    else
      left = n;
    right = n;
    return n;
  }
  gen_fib_heap_node<T>* add_child(gen_fib_heap_node<T> *x) {
    gen_fib_heap_node<T> *n = new gen_fib_heap_node<T>(x);
    if (children == nullptr) {
      children = new gen_fib_heap_node<T>(x);
      children->parent = this;
      children->marked = false;
    } else
      children->append_node(n)->parent = this;
    degree++;
    return n;
  }
  gen_fib_heap_node<T>* add_child(T i) {
    return add_child(new gen_fib_heap_node<T>(i));
  }
  gen_fib_heap_node<T>* find_in_children(T key){
    if (key == value){
      return this;
    } else if (children){
      gen_fib_heap_node<T> *x = children;
      do {
        gen_fib_heap_node<T> *test = x->find_in_children(key);
        if (test != nullptr)
          return test;
        else
          x = x->right;
      } while (x != children);
    }
    return nullptr;
  }
};

template <typename T>
class gen_fib_heap {
  gen_fib_heap_node<T> *root;

  std::string print_cycle(gen_fib_heap_node<T> *x) {
    std::string result = "";
    gen_fib_heap_node<T> *y = x;
    int childrenCycles = 0, childrenIndex = 0;
    if (!x)
      throw "print_cycle/1 called with nullptr";
    do {
      if (y->children)
        ++childrenCycles;
      y = y->right;
    } while (y != x);
    std::vector<gen_fib_heap_node<T>*> next(childrenCycles);
    if (childrenCycles > 0)
      for (int i = 0; i < childrenCycles; ++i)
        next[i] = nullptr;
    do {
      result += std::to_string(y->value) + (y->marked ? "*" : "");
      if (y->parent)
        result += "(" + std::to_string(y->parent->value) + ")";
      result += " ";
      if (childrenCycles > 0 && y->children){
        next[childrenIndex] = y->children;
        ++childrenIndex;
      }
      y = y->right;
    } while (y != x);
    if (childrenCycles > 0)
      for (int i = 0; i < childrenCycles; ++i)
        if (next[i]) {
          if (i == 0)
            result += "\n";
          result += print_cycle(next[i]);
        }
    if (childrenCycles > 0)
      result += "\n";
    return result;
  }
public:
  gen_fib_heap() : root(nullptr) {
  }
  ~gen_fib_heap() {
    /*
    gen_fib_heap_node<T> *x = root, *y;
    while (x) {
      y = x->right;
      delete x;
      x = y;
    }
    */
  }
  gen_fib_heap<T>* operator=(gen_fib_heap<T> *x){
    if (this != x) {
      root = new gen_fib_heap_node<T>(x->get_min()->value);
      root->right = root;
      root->left = root;
      for (gen_fib_heap_node<T> *i = x->get_min(); i->right != x->get_min(); ) {
        gen_fib_heap_node<T> *new_node = new gen_fib_heap_node<T>(i->value);
        insert(new_node);
      }
    }
    return this;
  }
  void insert(T key){
    insert(new gen_fib_heap_node<T>(key));
  }
  void insert(gen_fib_heap_node<T> *x) {
    if (root == nullptr)
      root = new gen_fib_heap_node<T>(x);
    else {
      if (find(x->value) != nullptr)
        return;
      gen_fib_heap<T> *h = new gen_fib_heap<T>();
      h->insert(x);
      meld_with(h);
    }
  }
  gen_fib_heap_node<T>* find(T key) {
    gen_fib_heap_node<T> *x = root, *t;
    do {
      t = x->find_in_children(key);
      if (t)
        return t;
      x = x->right;
    } while (x != root);
    return nullptr;
  }
  gen_fib_heap_node<T> *get_min() {
    return root;
  }
  void extract_min() {
    if (root == nullptr)
      return;
    gen_fib_heap_node<T> *tmp_root, *x, *y;
    int roots = 0;
    if (root->right == root && root->children == nullptr){
      delete root->unlink();
      root = nullptr;
      return;
    } else if (root->right == root)
      tmp_root = nullptr;
    else
      tmp_root = root->right;
    root->unlink();
    x = root->children;
    while (x) {
      if (tmp_root == nullptr)
        tmp_root = new gen_fib_heap_node<T>(x);
      else
        tmp_root->append_node(x);
      x->parent = nullptr;
      x = x->right;
      if (x == root->children)
        break;
    }
    x = tmp_root;
    do {
      ++roots;
      x = x->right;
    } while (x != tmp_root);
    root = tmp_root;
    std::vector<int> root_degs(roots + 1, 0);
    for (int i = 0; i < roots + 1; ++i) {
      tmp_root = root;
      x = tmp_root;
      do {
        if (x->value < root->value)
          root = x;
        if (x->degree == i) {
          if (root_degs[i] == 0) {
            root_degs[i] = x->value;
            x = x->right;
          } else {
            y = find(root_degs[i]);
            if (y->value <= x->value){
              y->add_child(x);
              y = x->right;
              x->unlink();
              x = y;
            } else {
              root_degs[i] = x->value;
              x->add_child(y);
              if (y == tmp_root)
                tmp_root = y->left;
              y->unlink();
              x = x->right;
            }
          }
        } else
          x = x->right;
      } while (x != tmp_root);
    }
  }
  void delete_node(T key) {
    gen_fib_heap_node<T> *x = find(key);
    if (x == root)
      extract_min();
    else {
      gen_fib_heap_node<T> *y = x->children;
      x->unlink();
      if (y)
        do {
          root->append_node(y);
          y = y->right;
        } while (y != x->children);
    }
  }
  void decrease_key(T key, int delta) {
    gen_fib_heap_node<T> *t = find(key);
    if (t == nullptr || find(key - delta) != nullptr)
      return;
    if (t == root) {
      root->value = root->value - delta;
      return;
    }
    gen_fib_heap_node<T> *x = new gen_fib_heap_node<T>(t);
    x->value = t->value - delta;
    root->append_node(x);
    if (root->value > x->value)
      root = find(x->value);
    delete x;
    t->unlink();
  }
  void set_key(T key, T new_key){
    gen_fib_heap_node<T> *x = find(key);
    if (!x)
      return;
    decrease_key(key, x->value - new_key);
  }
  void meld_with(gen_fib_heap<T> *x) {
    if (x->get_min()) {
      gen_fib_heap_node<T> *y = x->get_min();
      do {
        root->append_node(y);
        y = y->right;
      } while (y && y != x->get_min());
      T t = x->get_min()->value;
      if (root->value > t)
        root = find(t);
    }
  }
  void print() {
    if (root == nullptr)
      printf("(empty heap)");
    else
      printf("%s\n", print_cycle(root).c_str());
  }
};

typedef gen_fib_heap<int> fib_heap;

