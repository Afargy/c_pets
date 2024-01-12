#ifndef SRC_TEST_H
#define SRC_TEST_H

#include <check.h>
#include <limits.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define RESET "\033[0m"
#define RED "\e[0;91m"
#define GREEN "\033[32m"
#define BLUE "\e[0;94m"

#define S21_TRUE 1
#define S21_FALSE 0
#define CONVERTERS_S21_TRUE 0
#define CONVERTERS_S21_FALSE 1
#define U_MAX_INT 4294967295          // 0b11111111111111111111111111111111
#define MAX_INT 2147483648            // 0b01111111111111111111111111111111
#define EXPONENT_MINUS_1 2147549184   // 0b10000000000000010000000000000000
#define EXPONENT_PLUS_1 65536         // 0b00000000000000010000000000000000
#define EXPONENT_PLUS_2 196608        // 0b00000000000000110000000000000000
#define EXPONENT_MINUS_28 2149318656  // 0b10000000000111000000000000000000
#define EXPONENT_PLUS_28 1835008      // 0b00000000000111000000000000000000
#define MINUS 2147483648              // 0b10000000000000000000000000000000
#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -79228162514264337593543950335.0F
#define BIT 8
#define SIZE_BITS 4
#define NUM_255 255
#define TRUE 1
#define FALSE 0
#define S21_MAX_UINT 4294967295
#define EXPONENT_PLUS_1 65536
#define EXPONENT_PLUS_2 196608

Suite *suite_generalFunctions(void);
Suite *suite_add(void);
Suite *suite_sub_1(void);
Suite *suite_sub_2(void);
Suite *suite_mul(void);
Suite *suite_divmod(void);
Suite *suite_diffrent(void);
Suite *suite_from_decimal_to_float(void);
Suite *suite_from_decimal_to_int(void);
Suite *suite_from_float_to_decimal(void);
Suite *suite_from_int_to_decimal(void);
Suite *suite_is_equal(void);
Suite *suite_is_not_equal(void);
Suite *suite_is_greater(void);
Suite *suite_is_greater_or_equal(void);
Suite *suite_is_less(void);
Suite *suite_is_less_or_equal(void);
Suite *suite_truncate(void);
Suite *suite_negate(void);
Suite *suite_floor(void);
Suite *suite_round(void);

void run_tests(void);
void run_testcase(Suite *testcase);
void s21_assertDec(s21_decimal dec_1, s21_decimal dec_2);
void s21_assertAllDec(s21_decimal dec_1, s21_decimal dec_2);

Suite *st_generalFunctions(void);

#endif  // SRC_TEST_H