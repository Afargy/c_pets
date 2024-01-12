#include "test.h"

START_TEST(tt_calc_comp_1) {
  matrix_t m = {0}, result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (codec) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, CALCULATION_ERROR);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_calc_comp_2) {
  matrix_t m = {0}, result = {0};
  int code = s21_calc_complements(&m, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_calc_comp_3) {
  matrix_t m = {0}, result = {0};
  int codec = s21_create_matrix(3, 4, &m);
  if (codec == OK) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, CALCULATION_ERROR);
    s21_remove_matrix(&m);
  }
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_calc_comp_4) {
  matrix_t test = {0}, result = {0};
  s21_create_matrix(3, 2, &test);
  int result_status;
  s21_gen_matrix(&test);
  result_status = s21_calc_complements(&test, &result);
  ck_assert_int_eq(result_status, 2);
  s21_remove_matrix(&test);
}
END_TEST

START_TEST(tt_calc_comp_5) {
  matrix_t test = {0}, result = {0};
  s21_create_matrix(3, 3, &test);
  s21_gen_matrix(&test);
  int result_status = s21_calc_complements(&test, &result);
  ck_assert_int_eq(result_status, 0);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_calc_comp_6) {
  matrix_t test = {0}, test_2 = {0}, result = {0};
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  s21_calc_complements(&test, &result);
  s21_create_matrix(3, 3, &test_2);
  test_2.matrix[0][0] = 0;
  test_2.matrix[0][1] = 10;
  test_2.matrix[0][2] = -20;
  test_2.matrix[1][0] = 4;
  test_2.matrix[1][1] = -14;
  test_2.matrix[1][2] = 8;
  test_2.matrix[2][0] = -8;
  test_2.matrix[2][1] = -2;
  test_2.matrix[2][2] = 4;
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      double res = result.matrix[i][j];
      double must = result.matrix[i][j];
      ck_assert_uint_eq(res, must);
    }
  }
  s21_remove_matrix(&test);
  s21_remove_matrix(&test_2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_calc_comp_7) {
  matrix_t matrix = {0}, result = {0};
  s21_create_matrix(5, 5, &matrix);
  s21_fill(&matrix, 13);
  ck_assert_int_eq(s21_calc_complements(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_calc_comp_8) {
  matrix_t matrix = {0}, result = {0};
  s21_create_matrix(5, 7, &matrix);
  s21_fill(&matrix, 2);
  ck_assert_int_eq(s21_calc_complements(&matrix, &result), CALCULATION_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tt_calc_comp_9) {
  matrix_t matrix = {0}, result = {0};
  s21_create_matrix(0, 0, &matrix);
  s21_fill(&matrix, 1);
  ck_assert_int_eq(s21_calc_complements(&matrix, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("case_calc_complements");

  tcase_add_test(tc, tt_calc_comp_1);
  tcase_add_test(tc, tt_calc_comp_2);
  tcase_add_test(tc, tt_calc_comp_3);
  tcase_add_test(tc, tt_calc_comp_4);
  tcase_add_test(tc, tt_calc_comp_5);
  tcase_add_test(tc, tt_calc_comp_6);
  tcase_add_test(tc, tt_calc_comp_7);
  tcase_add_test(tc, tt_calc_comp_8);
  tcase_add_test(tc, tt_calc_comp_9);
  suite_add_tcase(s, tc);
  return s;
}
