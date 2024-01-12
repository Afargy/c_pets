#include "test.h"

START_TEST(tt_inverse_1) {
  const int rows = getRandom(1, 10, 0), cols = getRandom(10, 20, 0);
  matrix_t m = {0}, check = {0}, res = {0};
  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = getRandom(1, 100, 1);
      m.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }
  ck_assert_int_eq(s21_transpose(&m, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_inverse_2) {
  int rows = getRandom(1, 10, 0), cols = getRandom(10, 20, 0);
  matrix_t m = {0}, check = {0}, res = {0};
  rows = -rows;
  cols = -cols;
  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(cols, rows, &check);
  ck_assert_int_eq(s21_transpose(&m, &res), INCORRECT_MATRIX);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_inverse_3) {
  matrix_t matrix = {0};
  double **pmatrix = matrix.matrix;
  int rows = 3, columns = 7;
  s21_create_matrix(rows, columns, &matrix);
  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(pmatrix);
}
END_TEST

START_TEST(tt_inverse_4) {
  matrix_t temp = {0};
  matrix_t result = {0};
  matrix_t result_defolt = {0};
  s21_create_matrix(3, 2, &temp);
  s21_create_matrix(2, 3, &result_defolt);
  s21_gen_matrix(&temp);
  result_defolt.matrix[0][0] = 1;
  result_defolt.matrix[0][1] = 3;
  result_defolt.matrix[0][2] = 5;
  result_defolt.matrix[1][0] = 2;
  result_defolt.matrix[1][1] = 4;
  result_defolt.matrix[1][2] = 6;
  ck_assert_int_eq(s21_transpose(&temp, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(tt_inverse_5) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 5, &matrix);
  s21_fill(&matrix, -1.75756);
  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_inverse_6) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(-5, 5, &matrix);
  s21_fill(&matrix, 14);
  ck_assert_int_eq(s21_transpose(&matrix, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_inverse_7) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &matrix);
  s21_fill(&matrix, 13);
  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_transpose_matrix(void) {
  Suite *s = suite_create("suite_transpose_matrix");
  TCase *tc = tcase_create("case_transpose_matrix");
  tcase_add_loop_test(tc, tt_inverse_1, 0, 100);
  tcase_add_loop_test(tc, tt_inverse_2, 0, 100);
  tcase_add_test(tc, tt_inverse_3);
  tcase_add_test(tc, tt_inverse_4);
  tcase_add_test(tc, tt_inverse_5);
  tcase_add_test(tc, tt_inverse_6);
  tcase_add_test(tc, tt_inverse_7);
  suite_add_tcase(s, tc);
  return s;
}
