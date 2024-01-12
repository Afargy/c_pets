#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *m1, matrix_t *m2) {
  int lres = SUCCESS;
  if (checkEmptyness(m1) || checkEmptyness(m2))
    lres = FAILURE;
  else if (notEq(m1->rows, m2->rows) || notEq(m1->columns, m2->columns))
    lres = FAILURE;

  if (lres) {
    for (int i = 0; lres == SUCCESS && i < m1->rows; i++) {
      for (int j = 0; lres == SUCCESS && j < m1->columns; j++) {
        int res = (fabs(m1->matrix[i][j] - m2->matrix[i][j]) > TOLERANCE);
        if (res) lres = FAILURE;
      }
    }
  }
  return lres;
}
