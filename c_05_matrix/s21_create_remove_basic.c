#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *m) {
  int err = OK;
  if (rows < 1 || columns < 1 || isNullM(m)) err = INCORRECT_MATRIX;
  if (!err) {
    m->matrix = (double **)calloc(rows, sizeof(double *));
    if (m->matrix == NULL) err = INCORRECT_MATRIX;
    if (!err) {
      int i = 0;
      while (!err && i < rows) {
        m->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (m->matrix == NULL) err = INCORRECT_MATRIX;
        i++;
      }
      if (!err) {
        m->rows = rows;
        m->columns = columns;
      } else {
        for (int j = 0; err && j < i; j++) free(m->matrix[j]);
        free(m->matrix);
        m->rows = 0;
        m->columns = 0;
        m->matrix = NULL;
      }
    }
  }
  return err;
}

void s21_remove_matrix(matrix_t *m) {
  if (notNullM(m)) {
    if (m->matrix != NULL) {
      for (int i = 0; i < m->rows; i++) {
        if (m->matrix[i] != NULL) free(m->matrix[i]);
      }
      free(m->matrix);
      m->matrix = NULL;
      m->rows = 0;
      m->columns = 0;
    }
  }
}

int notNullM(matrix_t *m) { return (m != NULL) ? YES : NO; }

int isNullM(matrix_t *m) { return (m == NULL) ? YES : NO; }

int notEq(int a, int b) { return (a != b) ? YES : NO; }

int checkEmptyness(matrix_t *m) {
  int res = 0;
  if (m == NULL || m->matrix == NULL || m->columns < 1 || m->rows < 1) res = 1;
  return res;
}
