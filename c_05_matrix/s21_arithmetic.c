#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *m1, matrix_t *m2, matrix_t *result) {
  int err = OK;
  if (checkEmptyness(m1) || checkEmptyness(m2))
    err = INCORRECT_MATRIX;
  else if (notEq(m1->rows, m2->rows) || notEq(m1->columns, m2->columns))
    err = CALCULATION_ERROR;

  if (!err) {
    err = s21_create_matrix(m1->rows, m1->columns, result);
    for (int i = 0; !err && i < m1->rows; i++) {
      for (int j = 0; j < m1->columns; j++) {
        result->matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
      }
    }
  }
  return err;
}

int s21_sub_matrix(matrix_t *m1, matrix_t *m2, matrix_t *result) {
  int err = OK;
  if (checkEmptyness(m1) || checkEmptyness(m2))
    err = INCORRECT_MATRIX;
  else if (notEq(m1->rows, m2->rows) || notEq(m1->columns, m2->columns))
    err = CALCULATION_ERROR;

  if (!err) {
    err = s21_create_matrix(m1->rows, m1->columns, result);
    for (int i = 0; !err && i < m1->rows; i++) {
      for (int j = 0; j < m1->columns; j++) {
        result->matrix[i][j] = m1->matrix[i][j] - m2->matrix[i][j];
      }
    }
  }
  return err;
}

int s21_mult_number(matrix_t *m, double number, matrix_t *result) {
  int err = OK;
  if (checkEmptyness(m)) err = INCORRECT_MATRIX;

  if (!err) {
    err = s21_create_matrix(m->rows, m->columns, result);
    for (int i = 0; !err && i < m->rows; i++) {
      for (int j = 0; j < m->columns; j++) {
        result->matrix[i][j] = m->matrix[i][j] * number;
      }
    }
  }
  return err;
}

int s21_mult_matrix(matrix_t *m1, matrix_t *m2, matrix_t *result) {
  int err = OK;
  if (checkEmptyness(m1) || checkEmptyness(m2))
    err = INCORRECT_MATRIX;
  else if (notEq(m1->columns, m2->rows))
    err = CALCULATION_ERROR;

  if (!err) {
    err = s21_create_matrix(m1->rows, m2->columns, result);
    for (int i = 0; !err && i < m1->rows; i++) {
      for (int j = 0; j < m2->columns; j++) {
        for (int k = 0; k < m2->rows; k++)
          result->matrix[i][j] += m1->matrix[i][k] * m2->matrix[k][j];
      }
    }
  }
  return err;
}
