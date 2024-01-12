#include "test.h"

START_TEST(tt_mul_num_1) {
  int rows = getRandom(1, 15, 0), cols = getRandom(10, 20, 0);
  matrix_t check = {0}, res = {0}, m = {0};
  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(rows, cols, &check);
  double mult_number = getRandom(0, 100, 1);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = getRandom(0, 100, 1);

      check.matrix[i][j] = m.matrix[i][j] * mult_number;
    }
  }
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_mul_num_2) {
  int rows = getRandom(1, 15, 0), cols = getRandom(10, 20, 0);
  matrix_t check = {0}, res = {0}, m = {0};
  rows = -rows;
  cols = -cols;
  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(rows, cols, &check);
  double mult_number = getRandom(0, 100, 1);
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(tt_mul_num_3) {
  matrix_t temp1 = {0};
  matrix_t temp2 = {0};
  matrix_t result = {0};
  matrix_t result_defolt = {0};
  double num = 777.777;
  s21_create_matrix(3, 3, &temp1);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_gen_matrix(&temp1);
  s21_gen_matrix(&temp2);
  for (int i = 0; (i < temp1.rows); i++) {
    for (int j = 0; j < temp1.columns; j++) {
      result_defolt.matrix[i][j] = temp1.matrix[i][j] * 777.777;
    }
  }
  ck_assert_int_eq(s21_mult_number(&temp1, num, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(tt_mul_num_4) {
  matrix_t temp1 = {0};
  matrix_t temp2 = {0};
  matrix_t result = {0};
  matrix_t result_defolt = {0};
  double num = 777.777;
  s21_create_matrix(3, 3, &temp1);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_gen_matrix(&temp1);
  s21_gen_matrix(&temp2);
  for (int i = 0; i < temp1.rows; i++) {
    for (int j = 0; j < temp1.columns; j++) {
      result_defolt.matrix[i][j] = temp1.matrix[i][j] * 777.777;
    }
  }
  ck_assert_int_eq(s21_mult_number(&temp1, num, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(tt_mul_num_5) {
  matrix_t temp1 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &temp1);
  s21_fill(&temp1, -1);
  ck_assert_int_eq(s21_mult_number(&temp1, 2, &result), OK);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_mul_num_6) {
  matrix_t temp1 = {0};
  matrix_t result = {0};
  s21_create_matrix(0, 3, &temp1);
  ck_assert_int_eq(s21_mult_number(&temp1, 2, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_mul_num_7) {
  matrix_t temp1 = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 3, &temp1);
  s21_fill(&temp1, 1);
  ck_assert_int_eq(s21_mult_number(&temp1, 2.2222222, &result), OK);
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_mult_number(void) {
  Suite *s = suite_create("suite_mult_number_matrix");
  TCase *tc = tcase_create("case_mult_number_matrix");

  tcase_add_test(tc, tt_mul_num_1);
  tcase_add_test(tc, tt_mul_num_2);
  tcase_add_test(tc, tt_mul_num_3);
  tcase_add_test(tc, tt_mul_num_4);
  tcase_add_test(tc, tt_mul_num_5);
  tcase_add_test(tc, tt_mul_num_6);
  tcase_add_test(tc, tt_mul_num_7);

  suite_add_tcase(s, tc);
  return s;
}
