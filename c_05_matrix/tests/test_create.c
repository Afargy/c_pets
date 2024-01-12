#include "test.h"

START_TEST(tt_create_1) {
  matrix_t *m = NULL;
  int rows = 10, columns = 3;
  ck_assert_int_eq(s21_create_matrix(rows, columns, m), INCORRECT_MATRIX);
  s21_remove_matrix(m);
}
END_TEST

START_TEST(tt_create_2) {
  matrix_t m = {0};
  int rows = 5, columns = 5;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &m), OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(tt_create_3) {
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(-1, -20, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(tt_create_4) {
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(4, 4, &m), OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(tt_create_5) {
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(0, 5, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(tt_create_6) {
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(-1, 5, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(tt_create_7) {
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(-5, -5, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(tt_create_8) {
  const int rows = getRandom(1, 10, 0), cols = getRandom(15, 20, 0);
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      m.matrix[i][j] = 0;
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, cols);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(tt_create_9) {
  const int rows = 0, cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(tt_create_10) {
  const int rows = 10, cols = 0;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}

START_TEST(tt_create_11) {
  const int rows = -1, cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(tt_create_12) {
  const int rows = 10, cols = -1;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}

Suite *suite_create_matrix(void) {
  Suite *s = suite_create("ss_create");
  TCase *tc = tcase_create("cc_create");
  tcase_add_test(tc, tt_create_1);
  tcase_add_test(tc, tt_create_2);
  tcase_add_test(tc, tt_create_3);
  tcase_add_test(tc, tt_create_4);
  tcase_add_test(tc, tt_create_5);
  tcase_add_test(tc, tt_create_6);
  tcase_add_test(tc, tt_create_7);
  tcase_add_test(tc, tt_create_8);
  tcase_add_test(tc, tt_create_9);
  tcase_add_test(tc, tt_create_10);
  tcase_add_test(tc, tt_create_11);
  tcase_add_test(tc, tt_create_12);
  suite_add_tcase(s, tc);
  return s;
}
