#ifndef SRC_TESTS_COMMON_H_
#define SRC_TESTS_COMMON_H_

#include <check.h>

#include "../s21_matrix.h"

void s21_gen_matrix(matrix_t *A);
void s21_anti_gen_matrix(matrix_t *A);
void s21_fill(matrix_t *matrixStruct, double value);
double getRandom(unsigned min, unsigned max, unsigned minus);
int create_test(int rows, int cols, matrix_t *arr);

Suite *suite_create_matrix(void);
Suite *suite_eq_matrix(void);
Suite *suite_sum_matrix(void);
Suite *suite_sub_matrix(void);
Suite *suite_mult_number(void);
Suite *suite_mult_matrix(void);
Suite *suite_mult_number(void);
Suite *suite_transpose_matrix(void);
Suite *suite_determinant(void);
Suite *suite_calc_complements(void);
Suite *suite_inverse_matrix(void);

#endif  // SRC_TESTS_COMMON_H_
