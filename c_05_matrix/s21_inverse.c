#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *m, matrix_t *res) {
  int err = OK;
  if (checkEmptyness(m))
    err = INCORRECT_MATRIX;
  else if (m->rows != m->columns)
    err = CALCULATION_ERROR;

  if (!err) {
    double det = 0;
    s21_determinant(m, &det);
    if (det != 0) {
      matrix_t temp1 = {0};
      if (!err) {
        err = s21_calc_complements(m, &temp1);
        matrix_t temp2 = {0};
        if (!err) {
          err = s21_transpose(&temp1, &temp2);
          if (!err) s21_mult_number(&temp2, 1 / det, res);
          s21_remove_matrix(&temp2);
          if (err) s21_remove_matrix(res);
        }
        s21_remove_matrix(&temp1);
        if (err) s21_remove_matrix(res);
      }
      s21_remove_matrix(&temp1);
      if (err) s21_remove_matrix(res);
    } else {
      if (err) s21_remove_matrix(res);
      err = CALCULATION_ERROR;
    }
  }
  if (err) s21_remove_matrix(res);

  return err;
}
