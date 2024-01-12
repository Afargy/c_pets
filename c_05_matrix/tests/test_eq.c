#include "test.h"

START_TEST(tt_eq_1) {
  const int rows = getRandom(1, 10, 0), cols = getRandom(20, 30, 0);
  matrix_t m1 = {0}, m2 = {0};
  int res1 = s21_create_matrix(rows, cols, &m1);
  int res2 = s21_create_matrix(rows, cols, &m2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = getRandom(0, 1000, 1);
      m1.matrix[i][j] = value;
      m2.matrix[i][j] = value;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  ck_assert_int_eq(res1, res2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(tt_eq_2) {
  const int rows = getRandom(1, 10, 0), cols = getRandom(20, 30, 0);
  matrix_t m1 = {0}, m2 = {0};
  int res1 = s21_create_matrix(rows, cols, &m1);
  int res2 = s21_create_matrix(rows, cols, &m2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = getRandom(0, 1000, 1);
      m1.matrix[i][j] = value + 1;
      m2.matrix[i][j] = value;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  ck_assert_int_eq(res1, res2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(tt_eq_3) {
  const int rows = getRandom(1, 10, 0), cols = getRandom(20, 30, 0);
  matrix_t m1 = {0}, m2 = {0};
  int res1 = s21_create_matrix(rows + 1, cols, &m1);
  int res2 = s21_create_matrix(rows, cols + 1, &m2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = getRandom(0, 1000, 1);
      m1.matrix[i][j] = value;
      m2.matrix[i][j] = value;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  ck_assert_int_eq(res1, res2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(tt_eq_4) {
  const int rows = 0, cols = getRandom(20, 30, 0);
  matrix_t m1 = {0}, m2 = {0};
  int res1 = s21_create_matrix(rows, cols, &m1);
  int res2 = s21_create_matrix(rows, cols, &m2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = getRandom(0, 1000, 1);
      m1.matrix[i][j] = value;
      m2.matrix[i][j] = value;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  ck_assert_int_eq(res1, res2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(tt_eq_5) {
  const int rows = 0, cols = 0;
  matrix_t m1 = {0}, m2 = {0};
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(tt_eq_6) {
  const int rows = 0, cols = 0;
  matrix_t m1 = {0}, m2 = {0};
  int res1 = s21_create_matrix(rows, cols, &m1);
  int res2 = s21_create_matrix(rows, cols, &m2);
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  ck_assert_int_eq(res1, res2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(tt_eq_7) {
  const int rows = getRandom(1, 1, 0), cols = getRandom(1, 1, 0);
  matrix_t m1 = {0}, m2 = {0};
  int res1 = s21_create_matrix(rows, cols, &m1);
  int res2 = s21_create_matrix(rows, cols, &m2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = getRandom(0, 1000, 1);
      m1.matrix[i][j] = value;
      m2.matrix[i][j] = value;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  ck_assert_int_eq(res1, res2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(tt_eq_8) {
  const int rows = getRandom(1, 1, 0), cols = getRandom(1, 1, 0);
  matrix_t m1 = {0}, m2 = {0};
  int res1 = s21_create_matrix(rows, cols, &m1);
  int res2 = s21_create_matrix(rows, cols, &m2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = getRandom(0, 1000, 1);
      m1.matrix[i][j] = value;
      m2.matrix[i][j] = value + 1;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  ck_assert_int_eq(res1, res2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(tt_eq_9) {
  matrix_t matrix_1 = {0}, matrix_2 = {0};
  matrix_1.rows = 2, matrix_1.columns = 3;
  matrix_2.rows = 3, matrix_2.columns = 3;
  s21_create_matrix(matrix_1.rows, matrix_1.columns, &matrix_1);
  s21_create_matrix(matrix_2.rows, matrix_2.columns, &matrix_2);
  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(tt_eq_10) {
  matrix_t matrix_1 = {0}, matrix_2 = {0};
  matrix_1.rows = 3, matrix_1.columns = 7;
  matrix_2.rows = 3, matrix_2.columns = 7;
  s21_create_matrix(matrix_1.rows, matrix_1.columns, &matrix_1);
  s21_create_matrix(matrix_2.rows, matrix_2.columns, &matrix_2);
  matrix_1.matrix[1][2] = 4.0000007;
  matrix_2.matrix[1][2] = 4.0000009;
  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(tt_eq_11) {
  matrix_t matrixA = {0};
  matrix_t matrixB = {0};
  s21_create_matrix(2, 8, &matrixA);
  s21_create_matrix(2, 8, &matrixB);
  s21_fill(&matrixA, 1);
  s21_fill(&matrixB, 1);
  ck_assert_int_eq(s21_eq_matrix(&matrixA, &matrixB), SUCCESS);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
}
END_TEST

START_TEST(tt_eq_12) {
  matrix_t matrixA = {0};
  matrix_t matrixB = {0};
  s21_create_matrix(2, 8, &matrixA);
  s21_create_matrix(2, 8, &matrixB);
  s21_fill(&matrixA, -1);
  s21_fill(&matrixB, 5);
  ck_assert_int_eq(s21_eq_matrix(&matrixA, &matrixB), FAILURE);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
}
END_TEST

START_TEST(tt_eq_13) {
  matrix_t matrixA = {0};
  matrix_t matrixB = {0};
  s21_create_matrix(2, 3, &matrixA);
  s21_create_matrix(3, 2, &matrixB);
  s21_fill(&matrixA, 1);
  s21_fill(&matrixB, 1);
  ck_assert_int_eq(s21_eq_matrix(&matrixA, &matrixB), FAILURE);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
}
END_TEST

Suite *suite_eq_matrix(void) {
  Suite *s = suite_create("suite_eq_matrix");
  TCase *tc = tcase_create("case_eq_matrix");
  tcase_add_loop_test(tc, tt_eq_1, 0, 100);
  tcase_add_test(tc, tt_eq_2);
  tcase_add_test(tc, tt_eq_3);
  tcase_add_test(tc, tt_eq_4);
  tcase_add_test(tc, tt_eq_5);
  tcase_add_test(tc, tt_eq_6);
  tcase_add_test(tc, tt_eq_7);
  tcase_add_test(tc, tt_eq_8);
  tcase_add_test(tc, tt_eq_9);
  tcase_add_test(tc, tt_eq_10);
  tcase_add_test(tc, tt_eq_11);
  tcase_add_test(tc, tt_eq_12);
  tcase_add_test(tc, tt_eq_13);
  suite_add_tcase(s, tc);
  return s;
}
