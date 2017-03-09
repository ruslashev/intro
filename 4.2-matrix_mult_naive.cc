#include "std.h"

matrix square_matrix_mult(matrix &A, matrix &B) {
  matrix C(A.rows);
  for (size_t y = 1; y <= A.rows; y++) {
    for (size_t x = 1; x <= A.rows; x++) {
      int c = 0;
      for (size_t k = 1; x <= A.rows; x++) {
        c += A.at(y, k) * B.at(k, x);
      }
      C.at(y, x) = c;
    }
  }
  return C;
}

