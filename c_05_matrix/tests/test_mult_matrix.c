#include "test.h"

START_TEST(tt_mul_mat_1) {
  const int rows = getRandom(1, 10, 0), cols = getRandom(11, 16, 0);
  matrix_t m1 = {0}, m2 = {0}, check = {0}, res = {0};
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(cols, rows, &m2);
  s21_create_matrix(m1.rows, m2.columns, &check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = getRandom(-100, 100, 1);
    }
  }
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      m2.matrix[i][j] = getRandom(-100, 100, 1);
    }
  }
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < m1.columns; k++)
        check.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_mul_mat_2) {
  const int rows = 2, cols = 3;
  matrix_t m1 = {0}, m2 = {0}, check = {0}, res = {0};
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(cols, rows, &m2);
  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m1.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) m2.matrix[i][j] = c++;

  s21_create_matrix(m1.rows, m2.columns, &check);
  check.matrix[0][0] = 58;
  check.matrix[0][1] = 64;
  check.matrix[1][0] = 139;
  check.matrix[1][1] = 154;
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_mul_mat_3) {
  int rows = getRandom(1, 100, 0), cols = getRandom(1, 100, 0);
  rows = -rows;
  cols = -cols;
  matrix_t m1 = {0}, m2 = {0}, check = {0}, res = {0};
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(cols, rows, &m2);
  s21_create_matrix(m1.rows, m2.columns, &check);
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_mul_mat_4) {
  matrix_t m1 = {0}, m2 = {0}, check = {0}, res = {0};
  int rows = 2, cols = 3, rows1 = 4, cols1 = 5;
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(rows1, cols1, &m2);
  s21_create_matrix(m1.rows, m2.columns, &check);
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), CALCULATION_ERROR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_mul_mat_5) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0}, result_default = {0};
  s21_create_matrix(4, 4, &temp1);
  s21_create_matrix(4, 4, &temp2);
  s21_fill(&temp1, 3);
  s21_fill(&temp2, 3);
  int expected_result = s21_create_matrix(4, 4, &result);
  s21_fill(&result, 36);
  int actual_result = s21_mult_matrix(&temp1, &temp2, &result_default);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(result.matrix[i][j], result_default.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result_default);
  s21_remove_matrix(&result);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&temp1);
}
END_TEST

START_TEST(tt_mul_mat_6) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0}, result_defolt = {0};
  s21_create_matrix(3, 2, &temp1);
  s21_create_matrix(2, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_gen_matrix(&temp1);
  s21_gen_matrix(&temp2);
  result_defolt.matrix[0][0] = 9;
  result_defolt.matrix[0][1] = 12;
  result_defolt.matrix[0][2] = 15;
  result_defolt.matrix[1][0] = 19;
  result_defolt.matrix[1][1] = 26;
  result_defolt.matrix[1][2] = 33;
  result_defolt.matrix[2][0] = 29;
  result_defolt.matrix[2][1] = 40;
  result_defolt.matrix[2][2] = 51;
  ck_assert_int_eq(s21_mult_matrix(&temp1, &temp2, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(tt_mul_mat_7) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(3, 3, &temp1);
  s21_create_matrix(3, 3, &temp2);
  s21_gen_matrix(&temp1);
  s21_gen_matrix(&temp2);
  ck_assert_int_eq(s21_mult_matrix(&temp1, &temp2, &result), 0);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_mul_mat_8) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0}, result_defolt = {0};
  s21_create_matrix(2, 3, &temp1);
  s21_create_matrix(3, 2, &temp2);
  s21_create_matrix(2, 2, &result_defolt);
  s21_gen_matrix(&temp1);
  s21_gen_matrix(&temp2);
  result_defolt.matrix[0][0] = 22;
  result_defolt.matrix[0][1] = 28;
  result_defolt.matrix[1][0] = 49;
  result_defolt.matrix[1][1] = 64;
  ck_assert_int_eq(s21_mult_matrix(&temp1, &temp2, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(tt_mul_mat_9) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(7, 4, &temp1);
  s21_create_matrix(4, 3, &temp2);
  s21_fill(&temp1, 9);
  s21_fill(&temp2, 6);
  ck_assert_int_eq(s21_mult_matrix(&temp1, &temp2, &result), OK);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_mul_mat_10) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(4, 3, &temp1);
  s21_fill(&temp1, 1);
  s21_create_matrix(-3, 5, &temp2);
  s21_fill(&temp2, 6);
  ck_assert_int_eq(s21_mult_matrix(&temp1, &temp2, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_mul_mat_11) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(2, 8, &temp1);
  s21_create_matrix(4, 5, &temp2);
  s21_fill(&temp1, 2);
  s21_fill(&temp2, 5);
  ck_assert_int_eq(s21_mult_matrix(&temp1, &temp2, &result), CALCULATION_ERROR);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_mul_mat_12) {
  matrix_t temp1 = {0}, temp2 = {0}, result = {0};
  s21_create_matrix(4, 6, &temp1);
  s21_create_matrix(3, 4, &temp2);
  s21_fill(&temp1, -5);
  s21_fill(&temp2, 6);
  ck_assert_int_eq(s21_mult_matrix(&temp1, &temp2, &result), CALCULATION_ERROR);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_mult_matrix(void) {
  Suite *s = suite_create("suite_mult_matrix");
  TCase *tc = tcase_create("case_mult_matrix");
  tcase_add_test(tc, tt_mul_mat_1);
  tcase_add_test(tc, tt_mul_mat_2);
  tcase_add_test(tc, tt_mul_mat_3);
  tcase_add_test(tc, tt_mul_mat_4);
  tcase_add_test(tc, tt_mul_mat_5);
  tcase_add_test(tc, tt_mul_mat_6);
  tcase_add_test(tc, tt_mul_mat_7);
  tcase_add_test(tc, tt_mul_mat_8);
  tcase_add_test(tc, tt_mul_mat_9);
  tcase_add_test(tc, tt_mul_mat_10);
  tcase_add_test(tc, tt_mul_mat_11);
  tcase_add_test(tc, tt_mul_mat_12);
  suite_add_tcase(s, tc);
  return s;
}
