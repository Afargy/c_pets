#include "test.h"

#include <stdlib.h>

START_TEST(test_1) {
  int err = NO;
  char expr[5000] = "2+2\0";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(4, res, 1e-6);
}
END_TEST

START_TEST(test_2) {
  int err = NO;
  char expr[5000] = "sin(1)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(sin(1), res, 1e-6);
}
END_TEST

START_TEST(test_3) {
  int err = NO;
  char expr[5000] = "cos(1)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(cos(1), res, 1e-6);
}
END_TEST

START_TEST(test_4) {
  int err = NO;
  char expr[5000] = "tan(1)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(tan(1), res, 1e-6);
}
END_TEST

START_TEST(test_5) {
  int err = NO;
  char expr[5000] = "asin(1)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(asin(1), res, 1e-6);
}
END_TEST

START_TEST(test_6) {
  int err = NO;
  char expr[5000] = "acos(1)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(acos(1), res, 1e-6);
}
END_TEST

START_TEST(test_7) {
  int err = NO;
  char expr[5000] = "atan(1)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(atan(1), res, 1e-6);
}
END_TEST

START_TEST(test_8) {
  int err = NO;
  char expr[5000] = "ln(1)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(log(1), res, 1e-6);
}
END_TEST

START_TEST(test_9) {
  int err = NO;
  char expr[5000] = "log(1)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(log10(1), res, 1e-6);
}
END_TEST

START_TEST(test_10) {
  int err = NO;
  char expr[5000] = "2^2";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(pow(2, 2), res, 1e-6);
}
END_TEST

START_TEST(test_11) {
  int err = NO;
  char expr[5000] = "sqrt(4)";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(sqrt(4), res, 1e-6);
}
END_TEST

START_TEST(test_12) {
  int err = NO;
  char expr[5000] = "2+2";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(2 + 2, res, 1e-6);
}
END_TEST

START_TEST(test_13) {
  int err = NO;
  char expr[5000] = "2-2";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(2 - 2, res, 1e-6);
}
END_TEST

START_TEST(test_14) {
  int err = NO;
  char expr[5000] = "2*2";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(2 * 2, res, 1e-6);
}
END_TEST

START_TEST(test_15) {
  int err = NO;
  char expr[5000] = "2/2";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(2 / 2, res, 1e-6);
}
END_TEST

START_TEST(test_16) {
  int err = NO;
  char expr[5000] = "2mod2";
  double res = 0;
  ck_assert_int_eq(NO, calculate(expr, 1, &res));
  ck_assert_ldouble_eq_tol(fmod(2, 2), res, 1e-6);
}
END_TEST

START_TEST(test_17) {
  int err = NO;
  char expr[5000] = "2/0";
  double res = 0;
  ck_assert_int_eq(YES, calculate(expr, 1, &res));
}
END_TEST

Suite *suite_1(void) {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("case_calc_complements");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  suite_add_tcase(s, tc);
  return s;
}
