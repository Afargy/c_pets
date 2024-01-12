#include "../s21_decimal.h"
#include "test.h"

int main() {
  int number_failed = 0;
  SRunner* sr = srunner_create(suite_generalFunctions());
  srunner_add_suite(sr, suite_add());
  srunner_add_suite(sr, suite_sub_1());
  srunner_add_suite(sr, suite_sub_2());
  srunner_add_suite(sr, suite_mul());
  srunner_add_suite(sr, suite_divmod());
  srunner_add_suite(sr, suite_diffrent());
  srunner_add_suite(sr, suite_from_float_to_decimal());
  srunner_add_suite(sr, suite_from_decimal_to_float());
  srunner_add_suite(sr, suite_from_decimal_to_int());
  srunner_add_suite(sr, suite_from_int_to_decimal());
  srunner_add_suite(sr, suite_is_equal());
  srunner_add_suite(sr, suite_is_not_equal());
  srunner_add_suite(sr, suite_is_greater());
  srunner_add_suite(sr, suite_is_greater_or_equal());
  srunner_add_suite(sr, suite_is_less());
  srunner_add_suite(sr, suite_is_less_or_equal());
  srunner_add_suite(sr, suite_truncate());
  srunner_add_suite(sr, suite_negate());
  srunner_add_suite(sr, suite_round());
  srunner_add_suite(sr, suite_floor());
  srunner_run_all(sr, CK_FAILURE);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void s21_assertDec(s21_decimal dec_1, s21_decimal dec_2) {
  for (int i = 0; i < 3; i++) ck_assert_uint_eq(dec_1.bits[i], dec_2.bits[i]);
}

void s21_assertAllDec(s21_decimal dec_1, s21_decimal dec_2) {
  for (int i = 0; i < 4; i++) ck_assert_uint_eq(dec_1.bits[i], dec_2.bits[i]);
}
