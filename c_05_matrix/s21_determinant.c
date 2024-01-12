#include "s21_matrix.h"

static void getMatrix(matrix_t *m, matrix_t *res, int line, int col);
static int getDet(matrix_t *m, double *det);

int s21_determinant(matrix_t *m, double *res) {
  int err = OK;
  if (checkEmptyness(m))
    err = INCORRECT_MATRIX;
  else if (notEq(m->columns, m->rows))
    err = CALCULATION_ERROR;

  if (!err) {
    double det = 0;
    err = getDet(m, &det);
    if (!err) {
      *res = det;
    } else
      *res = 0;
  }
  return err;
}

int s21_calc_complements(matrix_t *m, matrix_t *res) {
  int err = OK;
  if (checkEmptyness(m))
    err = INCORRECT_MATRIX;
  else if (notEq(m->columns, m->rows))
    err = CALCULATION_ERROR;

  if (!err) {
    err = s21_create_matrix(m->rows, m->columns, res);
    for (int i = 0; !err && i < m->rows; i++)
      for (int j = 0; !err && j < m->columns; j++) {
        matrix_t m1 = {0};
        err = s21_create_matrix(m->rows - 1, m->columns - 1, &m1);
        if (!err) {
          getMatrix(m, &m1, i, j);
          double det = 0;
          err = getDet(&m1, &det);
          res->matrix[i][j] = pow(-1, i + j + 2) * det;
        }
        s21_remove_matrix(&m1);
      }
  }
  return err;
}

static int getDet(matrix_t *m, double *det) {
  int err = NO;
  if (m->rows == 1) {
    *det = m->matrix[0][0];
  } else {
    for (int i = 0; i < m->rows; i++) {
      matrix_t new = {0};
      err = s21_create_matrix(m->rows - 1, m->columns - 1, &new);
      if (!err) {
        getMatrix(m, &new, i, 0);
        double newDet = 0;
        err = getDet(&new, &newDet);
        if (!err) {
          *det += (m->matrix[i][0] * pow(-1, i + 2) * newDet);
        } else {
          s21_remove_matrix(&new);
        }
        s21_remove_matrix(&new);
      } else {
        s21_remove_matrix(&new);
      }
    }
  }
  return err;
}

void getMatrix(matrix_t *m, matrix_t *res, int line, int col) {
  for (int i = 0; i < res->rows; i++)
    for (int j = 0; j < res->columns; j++) {
      if (i < line && j < col)
        res->matrix[i][j] = m->matrix[i][j];
      else if (i < line && j >= col)
        res->matrix[i][j] = m->matrix[i][j + 1];
      else if (i >= line && j < col)
        res->matrix[i][j] = m->matrix[i + 1][j];
      else if (i >= line && j >= col)
        res->matrix[i][j] = m->matrix[i + 1][j + 1];
    }
}
