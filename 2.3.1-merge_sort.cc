#include "std.h"

struct value {
  int v;
  bool inf;
  value() : inf(true) {}
  value* operator=(int n_v) {
    v = n_v;
    inf = false;
  }
  bool operator<=(const value &o) {
    if (inf)
      return false;
    else if (o.inf)
      return true;
    else
      return v < o.v;
  }
  void print() {
    if (inf)
      puts("inf");
    else
      printf("%d\n", v);
  }
};

typedef gen_array<value> varray;

void merge(varray &A, int p, int q, int r) {
  int ll = q - p + 1, rl = r - q;
  varray L(ll + 1), R(rl + 1);
  for (int i = 1; i <= ll; ++i)
    L[i] = A[p + i - 1];
  for (int j = 1; j <= rl; ++j)
    R[j] = A[q + j];
  L[ll + 1].inf = R[rl + 1].inf = true;
  int i = 1, j = 1;
  for (int k = p; k <= r; ++k)
    if (L[i] <= R[j]) {
      A[k] = L[i];
      ++i;
    } else {
      A[k] = R[j];
      ++j;
    }
}

void merge_sort(varray &A, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    merge_sort(A, p, q);
    merge_sort(A, q + 1, r);
    merge(A, p, q, r);
  }
}

int main() {
  varray A(10);
  A.randomize();

  printf("before: ");
  A.print();

  merge_sort(A, 1, A.length);

  printf("after : ");
  A.print();
}

