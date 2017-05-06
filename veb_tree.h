#pragma once

#include <fstream> // std::swap
#include <memory.h>

template <typename T, size_t k>
class gen_veb_tree {
  bool _empty;
  T _min, _max;
  gen_veb_tree<T, (k >> 1)> *_cluster[1ull << (k >> 1)], *_summary;
  inline T high(T x) const {
    return x >> (k >> 1);
  }
  inline T low(T x) const {
    return x & ((1ull << (k >> 1)) - 1ull);
  }
  inline T index(T high, T low) const {
    return (high << (k >> 1)) + low;
  }
public:
  gen_veb_tree(): _empty(true), _summary(nullptr) {
    memset(_cluster, 0, sizeof(_cluster));
  }
  ~gen_veb_tree() {
    delete _summary;
    for (size_t i = 0; i < (1ull << (k >> 1)); ++i)
      delete _cluster[i];
  }
  inline bool empty() const {
    return _empty;
  }
  inline T get_min() const {
    return _min;
  }
  inline T get_max() const {
    return _max;
  }
  void insert(T x) {
    if (empty()) {
      _min = _max = x;
      _empty = false;
    } else {
      if (x < _min)
        std::swap(x, _min);
      if (x > _max)
        _max = x;
      if (k != 1) {
        if (_cluster[high(x)] == nullptr)
          _cluster[high(x)] = new gen_veb_tree<T, (k >> 1)>();
        if (_cluster[high(x)]->empty()) {
          if (_summary == nullptr)
            _summary = new gen_veb_tree<T, (k >> 1)>();
          _summary->insert(high(x));
        }
        _cluster[high(x)]->insert(low(x));
      }
    }
  }
  bool succ(T x, T &result) {
    if (x <= _min) {
      result = _min;
      return true;
    }
    if (empty() || x > _max)
      return false;
    if (k == 1) {
      if (_max == x) {
        result = x;
        return true;
      } else
        return false;
    }
    if (_cluster[high(x)] != nullptr && low(x)
        <= _cluster[high(x)]->get_max()) {
      T offset;
      if (_cluster[high(x)]->succ(low(x), offset)) {
        result = index(high(x), offset);
        return true;
      } else
        return false;
    } else if (_summary != nullptr) {
      T succ_cluster;
      if (_summary->succ(high(x) + 1, succ_cluster)) {
        result = index(succ_cluster, _cluster[succ_cluster]->get_min());
        return true;
      } else
        return false;
    }
    return false;
  }
  bool lookup(T x) {
    if (x == _min || x == _max)
      return true;
    else
      return _cluster[high(x)] != nullptr
        && _cluster[high(x)]->lookup(low(x));
  }
};

