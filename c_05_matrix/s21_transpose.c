#include "s21_matrix.h"

int s21_transpose(matrix_t *m, matrix_t *res) {
  int err = OK;
  if (checkEmptyness(m)) err = INCORRECT_MATRIX;
  if (!err) err = s21_create_matrix(m->columns, m->rows, res);

  if (!err) {
    for (int i = 0; i < res->rows; i++)
      for (int j = 0; j < res->columns; j++)
        res->matrix[i][j] = m->matrix[j][i];
  }
  return err;
}
