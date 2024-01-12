#include "test.h"

START_TEST(tt_sum_1) {
  matrix_t temp = {0}, temp2 = {0}, result = {0}, result_defolt = {0};
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_gen_matrix(&temp);
  s21_anti_gen_matrix(&temp2);
  for (int i = 0; (i < temp.rows); i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] + temp2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(tt_sum_2) {
  matrix_t temp = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_gen_matrix(&temp);
  s21_gen_matrix(&temp2);
  ck_assert_int_eq(s21_sum_matrix(&temp, &temp2, &result), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_sum_3) {
  matrix_t temp = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(3, 1, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_gen_matrix(&temp);
  s21_gen_matrix(&temp2);
  ck_assert_int_eq(s21_sum_matrix(&temp, &temp2, &result), CALCULATION_ERROR);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
}
END_TEST

START_TEST(tt_sum_4) {  // сложение матриц
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(2, 8, &temp1);
  s21_create_matrix(2, 8, &temp2);
  s21_fill(&temp1, 1.986875765);
  s21_fill(&temp2, 5.9867576);
  ck_assert_int_eq(s21_sum_matrix(&temp1, &temp2, &result), OK);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_sum_5) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(2, 8, &temp1);
  s21_fill(&temp1, 1);
  s21_create_matrix(0, 8, &temp2);
  ck_assert_int_eq(s21_sum_matrix(&temp1, &temp2, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_sum_6) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(2, 8, &temp1);
  s21_create_matrix(2, 7, &temp2);
  s21_fill(&temp1, 1);
  s21_fill(&temp2, 2);
  ck_assert_int_eq(s21_sum_matrix(&temp1, &temp2, &result), CALCULATION_ERROR);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_sum_7) {
  int rows = getRandom(1, 100, 0), cols = getRandom(1, 100, 0);
  matrix_t m1 = {0}, m2 = {0}, check = {0}, res = {0};
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(rows, cols, &m2);
  s21_create_matrix(rows, cols, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = getRandom(0, 500, 0);
      m2.matrix[i][j] = getRandom(500, 1000, 1);
      check.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_sum_8) {
  matrix_t m1 = {0}, m2 = {0}, res = {0};
  int rows = getRandom(1, 10, 0), cols = getRandom(12, 15, 0);
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(rows + 1, cols + 1, &m2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = getRandom(0, 500, 0);
      m2.matrix[i][j] = getRandom(500, 1000, 1);
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &res), CALCULATION_ERROR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(tt_sum_9) {
  matrix_t m1 = {0}, m2 = {0}, res = {0};
  int rows = getRandom(1, 10, 0), cols = getRandom(12, 15, 0),
      rows1 = getRandom(1, 100, 0), cols1 = getRandom(0, 100, 0);
  cols = -cols;
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(rows1, cols1, &m2);
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

Suite *suite_sum_matrix(void) {
  Suite *s = suite_create("suite_sum_matrix");
  TCase *tc = tcase_create("case_sum_matrix");
  tcase_add_test(tc, tt_sum_1);
  tcase_add_test(tc, tt_sum_2);
  tcase_add_test(tc, tt_sum_3);
  tcase_add_test(tc, tt_sum_4);
  tcase_add_test(tc, tt_sum_5);
  tcase_add_test(tc, tt_sum_6);
  tcase_add_loop_test(tc, tt_sum_7, 0, 10);
  tcase_add_loop_test(tc, tt_sum_8, 0, 10);
  tcase_add_loop_test(tc, tt_sum_9, 0, 10);
  suite_add_tcase(s, tc);
  return s;
}
