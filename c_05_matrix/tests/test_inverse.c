#include "test.h"

START_TEST(tt_inverse_1) {
  matrix_t A = {0}, B = {0}, C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(tt_inverse_2) {
  matrix_t m = {0}, result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (codec) {
    m.matrix[0][0] = 1431.12312331;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, OK);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_inverse_3) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALCULATION_ERROR);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_inverse_4) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(tt_inverse_5) {
  const int size = 2;
  matrix_t m = {0}, result = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 5;
  m.matrix[0][1] = 5;
  m.matrix[1][0] = 5;
  m.matrix[1][1] = 5;
  int code = s21_inverse_matrix(&m, &result);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(tt_inverse_6) {
  matrix_t m = {0}, result = {0};
  int codec = s21_create_matrix(1, 4, &m);
  if (codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALCULATION_ERROR);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_inverse_7) {
  const int size = 3;
  matrix_t m = {0}, res = {0}, expected = {0};
  s21_create_matrix(size, size, &m);
  s21_create_matrix(size, size, &expected);
  s21_inverse_matrix(&m, &res);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;
  // ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&res);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(tt_inverse_8) {
  matrix_t temp = {0}, result_defolt = {0}, result_defolt_2 = {0};
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &result_defolt);
  temp.matrix[0][0] = 2;
  temp.matrix[0][1] = 5;
  temp.matrix[0][2] = 7;
  temp.matrix[1][0] = 6;
  temp.matrix[1][1] = 3;
  temp.matrix[1][2] = 4;
  temp.matrix[2][0] = 5;
  temp.matrix[2][1] = -2;
  temp.matrix[2][2] = -3;
  result_defolt.matrix[0][0] = 1;
  result_defolt.matrix[0][1] = -1;
  result_defolt.matrix[0][2] = 1;
  result_defolt.matrix[1][0] = -38;
  result_defolt.matrix[1][1] = 41;
  result_defolt.matrix[1][2] = -34;
  result_defolt.matrix[2][0] = 27;
  result_defolt.matrix[2][1] = -29;
  result_defolt.matrix[2][2] = 24;

  s21_inverse_matrix(&temp, &result_defolt_2);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_uint_eq(result_defolt.matrix[i][j],
                        result_defolt_2.matrix[i][j]);
    }
  }
  s21_remove_matrix(&temp);
  s21_remove_matrix(&result_defolt);
  s21_remove_matrix(&result_defolt_2);
}
END_TEST

START_TEST(tt_inverse_9) {
  matrix_t result1 = {0};
  matrix_t result2 = {0};
  matrix_t result3 = {0};
  s21_create_matrix(3, 3, &result1);
  result1.matrix[0][0] = 2;
  result1.matrix[0][1] = 5;
  result1.matrix[0][2] = 7;

  result1.matrix[1][0] = 6;
  result1.matrix[1][1] = 3;
  result1.matrix[1][2] = 4;

  result1.matrix[2][0] = 5;
  result1.matrix[2][1] = -2;
  result1.matrix[2][2] = -3;

  int expected_result = s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = -1;
  result2.matrix[0][2] = 1;
  result2.matrix[1][0] = -38;
  result2.matrix[1][1] = 41;
  result2.matrix[1][2] = -34;
  result2.matrix[2][0] = 27;
  result2.matrix[2][1] = -29;
  result2.matrix[2][2] = 24;
  int actual_result = s21_inverse_matrix(&result1, &result3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result2.matrix[i][j], result3.matrix[i][j], 1e-7);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(tt_inverse_10) {
  matrix_t result1 = {0};
  matrix_t result3 = {0};
  s21_create_matrix(3, 3, &result1);
  result1.matrix[0][0] = 1;
  result1.matrix[0][1] = 2;
  result1.matrix[0][2] = 3;

  result1.matrix[1][0] = 4;
  result1.matrix[1][1] = 5;
  result1.matrix[1][2] = 6;

  result1.matrix[2][0] = 7;
  result1.matrix[2][1] = 8;
  result1.matrix[2][2] = 9;
  int expected_result = CALCULATION_ERROR;
  int actual_result = s21_inverse_matrix(&result1, &result3);
  ck_assert_uint_eq(expected_result, actual_result);

  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(tt_inverse_11) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 8;
  matrix.matrix[0][2] = 2;
  matrix.matrix[1][0] = 8;
  matrix.matrix[1][1] = 2;
  matrix.matrix[1][2] = 8;
  matrix.matrix[2][0] = 2;
  matrix.matrix[2][1] = -8;
  matrix.matrix[2][2] = -2;
  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_inverse_12) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(6, 8, &matrix);
  s21_fill(&matrix, 5);
  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALCULATION_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_inverse_13) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(0, 0, &matrix);
  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_inverse_14) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &matrix);
  s21_fill(&matrix, 8);
  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALCULATION_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("suite_inverse_matrix");
  TCase *tc = tcase_create("case_inverse_matrix");

  tcase_add_test(tc, tt_inverse_1);
  tcase_add_test(tc, tt_inverse_2);
  tcase_add_test(tc, tt_inverse_3);
  tcase_add_test(tc, tt_inverse_4);
  tcase_add_test(tc, tt_inverse_5);
  tcase_add_test(tc, tt_inverse_6);
  tcase_add_test(tc, tt_inverse_7);
  tcase_add_test(tc, tt_inverse_8);
  tcase_add_test(tc, tt_inverse_9);
  tcase_add_test(tc, tt_inverse_10);
  tcase_add_test(tc, tt_inverse_11);
  tcase_add_test(tc, tt_inverse_12);
  tcase_add_test(tc, tt_inverse_13);
  tcase_add_test(tc, tt_inverse_14);
  suite_add_tcase(s, tc);
  return s;
}
