#include "test.h"

START_TEST(tt_sub_1) {
  matrix_t temp = {0}, temp2 = {0}, result = {0}, result_defolt = {0};
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_gen_matrix(&temp);
  s21_anti_gen_matrix(&temp2);
  for (int i = 0; (i < temp.rows); i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] - temp2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(tt_sub_2) {
  matrix_t temp = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_gen_matrix(&temp);
  s21_gen_matrix(&temp2);
  ck_assert_int_eq(s21_sub_matrix(&temp, &temp2, &result), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_sub_3) {
  matrix_t temp = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(3, 1, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_gen_matrix(&temp);
  s21_gen_matrix(&temp2);
  ck_assert_int_eq(s21_sub_matrix(&temp, &temp2, &result), CALCULATION_ERROR);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
}
END_TEST

START_TEST(tt_sub_4) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(4, 3, &temp1);
  s21_create_matrix(4, 3, &temp2);
  s21_fill(&temp1, 2.987865);
  s21_fill(&temp2, 6.098686564653);
  ck_assert_int_eq(s21_sub_matrix(&temp1, &temp2, &result), OK);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_sub_5) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(0, 3, &temp1);
  s21_fill(&temp1, 0);
  s21_create_matrix(4, 3, &temp2);
  s21_fill(&temp2, -4);
  ck_assert_int_eq(s21_sub_matrix(&temp1, &temp2, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_sub_6) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(2, 5, &temp1);
  s21_create_matrix(4, 5, &temp2);
  s21_fill(&temp1, 9);
  s21_fill(&temp2, 0);
  ck_assert_int_eq(s21_sub_matrix(&temp1, &temp2, &result), CALCULATION_ERROR);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_sub_7) {
  int rows = getRandom(1, 100, 0), cols = getRandom(1, 100, 0);
  matrix_t m1 = {0}, m2 = {0}, check = {0}, res = {0};
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(rows, cols, &m2);
  s21_create_matrix(rows, cols, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = getRandom(0, 500, 0);
      m2.matrix[i][j] = getRandom(500, 1000, 1);
      check.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_sub_8) {
  int rows = getRandom(1, 100, 0), cols = getRandom(1, 100, 0);
  matrix_t m1 = {0}, m2 = {0}, res = {0};
  s21_create_matrix(rows + 2, cols + 1, &m1);
  s21_create_matrix(rows, cols, &m2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = getRandom(0, 500, 0);
      m2.matrix[i][j] = getRandom(500, 1000, 1);
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &res), CALCULATION_ERROR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(tt_sub_9) {
  int rows = getRandom(1, 100, 0), cols = getRandom(1, 100, 0);
  matrix_t m1 = {0}, m2 = {0}, res = {0};
  cols = -cols;
  s21_create_matrix(rows + 2, cols + 1, &m1);
  s21_create_matrix(rows, cols, &m2);
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

Suite *suite_sub_matrix(void) {
  Suite *s = suite_create("suite_sub_matrix");
  TCase *tc = tcase_create("case_sub_matrix");
  tcase_add_test(tc, tt_sub_1);
  tcase_add_test(tc, tt_sub_2);
  tcase_add_test(tc, tt_sub_3);
  tcase_add_test(tc, tt_sub_4);
  tcase_add_test(tc, tt_sub_5);
  tcase_add_test(tc, tt_sub_6);
  tcase_add_test(tc, tt_sub_7);
  tcase_add_test(tc, tt_sub_8);
  tcase_add_test(tc, tt_sub_9);
  suite_add_tcase(s, tc);
  return s;
}
