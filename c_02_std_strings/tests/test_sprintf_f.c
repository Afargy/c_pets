#include "../s21_string.h"
#include "test.h"

START_TEST(stars) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original = sprintf(original, "%+*f, %-*f, % *f, %0*f, %#*f,", 10, num1,
                         10, num2, 10, num3, 0, num4, 0, num5);
  len_compare = s21_sprintf(compare, "%+*f, %-*f, % *f, %0*f, %#*f,", 10, num1,
                            10, num2, 10, num3, 0, num4, 0, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);

  len_original = sprintf(original, "%+.*f, %- .*f, % .*f, %0.*f, %#.*f,", 10,
                         num1, 10, num2, 10, num3, 10, num4, 10, num5);
  len_compare = s21_sprintf(compare, "%+.*f, %- .*f, % .*f, %0.*f, %#.*f,", 10,
                            num1, 10, num2, 10, num3, 10, num4, 10, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(no_flags) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original =
      sprintf(original, "%f, %f, %f, %f, %f,", num1, num2, num3, num4, num5);
  len_compare =
      s21_sprintf(compare, "%f, %f, %f, %f, %f,", num1, num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);

  len_original = sprintf(original, "a%.0f, %.0f, %.0f, %.0f, %.0f,", num1, num2,
                         num3, num4, num5);
  len_compare = s21_sprintf(compare, "a%.0f, %.0f, %.0f, %.0f, %.0f,", num1,
                            num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(wid) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original = sprintf(original, "%10f, %10f, %10f, %10f, %10f,", num1, num2,
                         num3, num4, num5);
  len_compare = s21_sprintf(compare, "%10f, %10f, %10f, %10f, %10f,", num1,
                            num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(acc) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = 1234.9999;
  double num5 = -1234.9999;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original = sprintf(original, "%.10f, %.10f, %.10f, %.0f, %.0f,", num1,
                         num2, num3, num4, num5);
  len_compare = s21_sprintf(compare, "%.10f, %.10f, %.10f, %.0f, %.0f,", num1,
                            num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(wa) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original =
      sprintf(original, "%10.10f, %10.10f, %10.10f, %10.10f, %10.10f,", num1,
              num2, num3, num4, num5);
  len_compare =
      s21_sprintf(compare, "%10.10f, %10.10f, %10.10f, %10.10f, %10.10f,", num1,
                  num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(Wa) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original =
      sprintf(original, "%20.10f, %20.10f, %20.10f, %20.10f, %20.10f,", num1,
              num2, num3, num4, num5);
  len_compare =
      s21_sprintf(compare, "%20.10f, %20.10f, %20.10f, %20.10f, %20.10f,", num1,
                  num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(wA) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original =
      sprintf(original, "%10.20f, %10.20f, %10.20f, %10.20f, %10.20f,", num1,
              num2, num3, num4, num5);
  len_compare =
      s21_sprintf(compare, "%10.20f, %10.20f, %10.20f, %10.20f, %10.20f,", num1,
                  num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(flags) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original = sprintf(original, "%+f, %-f, % f, %#f, %0f,", num1, num2, num3,
                         num4, num5);
  len_compare = s21_sprintf(compare, "%+f, %-f, % f, %#f, %0f,", num1, num2,
                            num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(flags_wid) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original = sprintf(original, "%+10f, %-10f, % 10f, %#10f, %020f,", num1,
                         num2, num3, num4, num5);
  len_compare = s21_sprintf(compare, "%+10f, %-10f, % 10f, %#10f, %020f,", num1,
                            num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(flags_acc) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original = sprintf(original, "%+.10f, %-.10f, % .10f, %#.10f, %0.10f,",
                         num1, num2, num3, num4, num5);
  len_compare = s21_sprintf(compare, "%+.10f, %-.10f, % .10f, %#.10f, %0.10f,",
                            num1, num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(flags_wa) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original =
      sprintf(original, "%+10.10f, %-10.10f, % 10.10f, %#10.10f, %010.10f,",
              num1, num2, num3, num4, num5);
  len_compare =
      s21_sprintf(compare, "%+10.10f, %-10.10f, % 10.10f, %#10.10f, %010.10f,",
                  num1, num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(flags_Wa) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original =
      sprintf(original, "%+20.10f, %-20.10f, % 20.10f, %#20.10f, a%020.10f,",
              num1, num2, num3, num4, num5);
  len_compare =
      s21_sprintf(compare, "%+20.10f, %-20.10f, % 20.10f, %#20.10f, a%020.10f,",
                  num1, num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

START_TEST(flags_wA) {
  double num1 = N1;
  double num2 = N2;
  double num3 = N3;
  double num4 = N10;
  double num5 = N11;
  char original[BS] = {0};
  char compare[BS] = {0};
  int len_original = 1933;
  int len_compare = 1933;
  len_original =
      sprintf(original, "%+10.20f, %-10.20f, % 10.20f, %#10.20f, %010.20f,",
              num1, num2, num3, num4, num5);
  len_compare =
      s21_sprintf(compare, "%+10.20f, %-10.20f, % 10.20f, %#10.20f, %010.20f,",
                  num1, num2, num3, num4, num5);
  ck_assert_str_eq(original, compare);
  ck_assert_int_eq(len_original, len_compare);
}
END_TEST

Suite *suit_sprintf_f(void) {
  Suite *s;
  TCase *dec;

  s = suite_create("double");

  dec = tcase_create("\tdouble\t");
  tcase_add_test(dec, stars);
  tcase_add_test(dec, no_flags);
  tcase_add_test(dec, wid);
  tcase_add_test(dec, acc);
  tcase_add_test(dec, wa);
  tcase_add_test(dec, Wa);
  tcase_add_test(dec, wA);
  tcase_add_test(dec, flags);
  tcase_add_test(dec, flags_wid);
  tcase_add_test(dec, flags_acc);
  tcase_add_test(dec, flags_wa);
  tcase_add_test(dec, flags_Wa);
  tcase_add_test(dec, flags_wA);
  suite_add_tcase(s, dec);

  return s;
}