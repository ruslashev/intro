#pragma once

template <typename T>
struct gen_rb_node {
  bool black;
  gen_rb_node *left, *right, *parent;
  T key;
  gen_rb_node()
    : black(true)
    , left(nullptr)
    , right(nullptr)
    , parent(nullptr) {}
  gen_rb_node(T n_key, gen_rb_node *n_parent = nullptr, bool n_black = true
      , gen_rb_node *n_left = nullptr, gen_rb_node *n_right = nullptr)
    : black(n_black)
    , left(n_left)
    , right(n_right)
    , parent(n_parent)
    , key(n_key) {}
};

template <typename T>
class gen_rb_tree {
  int _print(gen_rb_node<T> *n, bool is_left, int offset, int depth
      , std::vector<std::string> &s, size_t width) {
    if (n == nullptr)
      return 0;
    std::string node_info = (n->black ? "b" : "r") + std::to_string(n->key);
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
  gen_rb_node<T> *root;
  gen_rb_tree() : root(nullptr) {}
  void print(size_t width = 80) {
    std::vector<std::string> s(1, std::string(width, ' '));
    _print(root, 0, 0, 0, s, width);
    for (size_t i = 0; i < s.size(); ++i)
      printf("%s\n", s[i].c_str());
  }
};

template <typename T>
gen_rb_node<T>* tree_minimum(gen_rb_node<T> *x) {
  while (x->left != nullptr)
    x = x->left;
  return x;
}

template <typename T>
gen_rb_node<T>* tree_maximum(gen_rb_node<T> *x) {
  while (x->right != nullptr)
    x = x->right;
  return x;
}

template <typename T>
gen_rb_node<T>* tree_succ(gen_rb_node<T> *x) {
  if (x->right != nullptr)
    return tree_minimum(x->right);
  gen_rb_node<T> *y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename T>
gen_rb_node<T>* tree_pred(gen_rb_node<T> *x) {
  if (x->left != nullptr)
    return tree_maximum(x->left);
  gen_rb_node<T> *y = x->parent;
  while (y != nullptr && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename T>
void left_rotate(gen_rb_tree<T> &t, gen_rb_node<T> *x) {
  gen_rb_node<T> *y = x->right;
  x->right = y->left;
  if (y->left != nullptr)
    y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    t.root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename T>
void right_rotate(gen_rb_tree<T> &t, gen_rb_node<T> *x) {
  gen_rb_node<T> *y = x->left;
  x->left = y->right;
  if (y->right != nullptr)
    y->right->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    t.root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->right = x;
  x->parent = y;
}

template <typename T>
void rb_insert(gen_rb_tree<T> &t, gen_rb_node<T> *z) {
  gen_rb_node<T> *y = nullptr, *x = t.root;
  while (x != nullptr) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (y == nullptr)
    t.root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  z->left = nullptr;
  z->right = nullptr;
  z->black = false;
  rb_insert_fixup(t, z);
}

template <typename T>
void rb_insert_fixup(gen_rb_tree<T> &t, gen_rb_node<T> *z) {
  while (z->parent != nullptr && z->parent->black == false)
    if (z->parent == z->parent->parent->left) {
      gen_rb_node<T> *y = z->parent->parent->right;
      if (y != nullptr && y->black == false) {
        z->parent->black = true;
        y->black = true;
        z->parent->parent->black = false;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->black = true;
        z->parent->parent->black = false;
        right_rotate(t, z->parent->parent);
      }
    } else {
      gen_rb_node<T> *y = z->parent->parent->left;
      if (y != nullptr && y->black == false) {
        z->parent->black = true;
        y->black = true;
        z->parent->parent->black = false;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
        }
        z->parent->black = true;
        z->parent->parent->black = false;
        left_rotate(t, z->parent->parent);
      }
    }
  t.root->black = true;
}

template <typename T>
void rb_transplant(gen_rb_tree<T> &t, gen_rb_node<T> *u, gen_rb_node<T> *v) {
  if (u->parent == nullptr)
    t.root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr)
    v->parent = u->parent;
}

template <typename T>
void rb_delete(gen_rb_tree<T> &t, gen_rb_node<T> *z) {
  gen_rb_node<T> *y = z, *x;
  bool y_orig_color = y->black;
  if (z->left == nullptr) {
    x = z->right;
    rb_transplant(t, z, z->right);
  } else if (z->right == nullptr) {
    x = z->left;
    rb_transplant(t, z, z->left);
  } else {
    y = tree_minimum(z->right);
    y_orig_color = y->black;
    x = y->right;
    if (y->parent == z) {
      if (x != nullptr)
        x->parent = y;
    } else {
      rb_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rb_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->black = z->black;
  }
  if (y_orig_color == true)
    rb_delete_fixup(t, x);
}

// does not work correctly: uses nullptrs and so is prone to segfaults
template <typename T>
void rb_delete_fixup(gen_rb_tree<T> &t, gen_rb_node<T> *x) {
  while (x != t.root && x->black == true) {
    if (x == x->parent->left) {
      gen_rb_node<T> *w = x->parent->right;
      if (w->black == false) {
        w->black = true;
        x->parent->black = false;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      if (w->left->black == true && w->right->black == true) {
        w->black = false;
        x = x->parent;
      } else {
        if (w->right->black == true) {
          w->left->black = true;
          w->black = false;
          right_rotate(t, w);
          w = x->parent->right;
        }
        w->black = x->parent->black;
        x->parent->black = true;
        w->right->black = true;
        left_rotate(t, x->parent);
        x = t.root;
      }
    } else {
      gen_rb_node<T> *w = x->parent->left;
      if (w->black == false) {
        w->black = true;
        x->parent->black = false;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if (w->right->black == true && w->left->black == true) {
        w->black = false;
        x = x->parent;
      } else {
        if (w->left->black == true) {
          w->right->black = true;
          w->black = false;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->black = x->parent->black;
        x->parent->black = true;
        w->right->black = true;
        right_rotate(t, x->parent);
        x = t.root;
      }
    }
  }
  x->black = true;
}

typedef gen_rb_tree<int> rb_tree;
typedef gen_rb_node<int> rb_node;

