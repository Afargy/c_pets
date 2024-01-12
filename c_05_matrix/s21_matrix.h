#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUCCESS 1
#define FAILURE 0
#define TOLERANCE 0.00000005

enum matrix_func_result {
  OK,
  INCORRECT_MATRIX,
  CALCULATION_ERROR,
  NO = 0,
  YES = 1
};

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// main functions
int s21_create_matrix(int rows, int columns, matrix_t *m);
void s21_remove_matrix(matrix_t *m);
int s21_eq_matrix(matrix_t *m1, matrix_t *m2);
int s21_sum_matrix(matrix_t *m1, matrix_t *m2, matrix_t *res);
int s21_sub_matrix(matrix_t *m1, matrix_t *m2, matrix_t *res);
int s21_mult_number(matrix_t *m, double number, matrix_t *res);
int s21_mult_matrix(matrix_t *m1, matrix_t *m2, matrix_t *res);
int s21_transpose(matrix_t *m, matrix_t *res);
int s21_determinant(matrix_t *m, double *res);
int s21_calc_complements(matrix_t *m, matrix_t *res);
int s21_inverse_matrix(matrix_t *m, matrix_t *res);

// helping functions
double getRandom(unsigned min, unsigned max, unsigned minus);
int checkEmptyness(matrix_t *m);
int notNullM(matrix_t *m);
int isNullM(matrix_t *m);
int notEq(int a, int b);

#endif  // SRC_S21_MATRIX_H_
