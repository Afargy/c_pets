#include "test.h"

START_TEST(tt_getBitValue) {
  s21_decimal dec = {{MASK, MASK << 1, MASKE >> 1, MASKE >> 2}};
  ck_assert_uint_eq(1, s21_getBitValue(dec, 0));
  ck_assert_uint_eq(0, s21_getBitValue(dec, 1));
  ck_assert_uint_eq(1, s21_getBitValue(dec, 33));
  ck_assert_uint_eq(0, s21_getBitValue(dec, 32));
  ck_assert_uint_eq(1, s21_getBitValue(dec, 94));
  ck_assert_uint_eq(0, s21_getBitValue(dec, 95));
  ck_assert_uint_eq(1, s21_getBitValue(dec, 125));
  ck_assert_uint_eq(0, s21_getBitValue(dec, 127));
}
END_TEST

START_TEST(tt_setBitValue) {
  s21_decimal dec = {{0, 0, 0, 0}};
  for (int i = 0; i < 127; i++) ck_assert_uint_eq(0, s21_getBitValue(dec, i));
  for (int i = 0; i < 127; i++) {
    s21_setBitValue(&dec, i, 1);
    for (int j = 0; j < 127; j++) {
      ck_assert_uint_eq(j <= i ? 1 : 0, s21_getBitValue(dec, j));
    }
  }
  for (int i = 0; i < 127; i++) {
    s21_setBitValue(&dec, i, 0);
    for (int j = 0; j < 127; j++) {
      ck_assert_uint_eq(j <= i ? 0 : 1, s21_getBitValue(dec, j));
    }
  }
}
END_TEST

START_TEST(tt_nullDec) {
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_nullDec(&dec);
  for (int i = 0; i < 3; i++) {
    dec.bits[i] = 1;
    ck_assert_int_ne(0, s21_compareDec(dec, equ));
    s21_nullDec(&dec);
    ck_assert_int_eq(0, s21_compareDec(dec, equ));
  }
}
END_TEST

START_TEST(tt_moveRight) {
  s21_decimal dec = {{0, 0, 0, 0}};
  for (int i = 0; i > 3; i++) {
    s21_nullDec(&dec);
    dec.bits[i] = MASK;
    int res = 0;
    res = s21_moveRight(&dec);
    ck_assert_uint_eq(2, dec.bits[i]);
    ck_assert_int_eq(0, res);
  }
  for (int i = 0; i < 3; i++) {
    s21_nullDec(&dec);
    dec.bits[i] = MASK + MASKE;
    int res = 0;
    res = s21_moveRight(&dec);
    ck_assert_uint_eq(2, dec.bits[i]);
    if (i != 2) {
      ck_assert_uint_eq(1, dec.bits[i + 1]);
      ck_assert_int_eq(0, res);
    } else {
      ck_assert_uint_eq(0, dec.bits[i + 1]);
      ck_assert_int_eq(1, res);
    }
  }
}
END_TEST

START_TEST(tt_moveLeft) {
  s21_decimal dec = {{0, 0, 0, 0}};
  for (int i = 0; i > 3; i++) {
    s21_nullDec(&dec);
    dec.bits[i] = MASK;
    s21_moveLeft(&dec);
    if (i == 0)
      ck_assert_uint_eq(0, dec.bits[i]);
    else
      ck_assert_uint_eq(MASKE, dec.bits[i - 1]);
  }
  for (int i = 0; i < 3; i++) {
    s21_nullDec(&dec);
    dec.bits[i] = MASK + MASKE;
    s21_moveLeft(&dec);
    if (i == 0) {
      ck_assert_uint_eq(MASKE >> 1, dec.bits[i]);
    } else {
      ck_assert_uint_eq(MASKE >> 1, dec.bits[i]);
      ck_assert_uint_eq(MASKE, dec.bits[i - 1]);
    }
  }
}
END_TEST

START_TEST(tt_addColumns00) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_addColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_addColumns01) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_addColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_addColumns02) {
  s21_decimal dec_1 = {{1, 1, 1, 0}};
  s21_decimal dec_2 = {{1, 1, 1, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal equ = {{2, 2, 2, 0}};
  s21_addColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_addColumns03) {
  s21_decimal dec_1 = {{2, 1, 2, 0}};
  s21_decimal dec_2 = {{2, 2, 1, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal equ = {{4, 3, 3, 0}};
  s21_addColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_addColumns04) {
  s21_decimal dec_1 = {{10, 10, 10, 0}};
  s21_decimal dec_2 = {{10, 10, 10, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal equ = {{20, 20, 20, 0}};
  s21_addColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_addColumns05) {
  s21_decimal dec_1 = {{100, 99, 11, 0}};
  s21_decimal dec_2 = {{163, 16, 16, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal equ = {{263, 115, 27, 0}};
  s21_addColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_addColumns06) {
  s21_decimal dec_1 = {{MASK + MASKE, MASK + MASKE, 2, 0}};
  s21_decimal dec_2 = {{MASK + MASKE, MASK + MASKE, 1, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal equ = {{2, 3, 4, 0}};
  s21_addColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_addColumns07) {
  s21_decimal dec_1 = {{MASKE, 0, MASKE, 0}};
  s21_decimal dec_2 = {{MASKE, 0, MASKE, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal equ = {{0, 1, 0, 0}};
  s21_addColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_getSignsSum) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  int res = s21_getSignsSum(dec_1, dec_2);
  ck_assert_int_eq(0, res);
  s21_setBitValue(&dec_1, 127, 1);
  res = s21_getSignsSum(dec_1, dec_2);
  ck_assert_int_eq(1, res);
  s21_setBitValue(&dec_2, 127, 1);
  res = s21_getSignsSum(dec_1, dec_2);
  ck_assert_int_eq(2, res);
}
END_TEST

START_TEST(tt_subColumns00) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_subColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_subColumns01) {
  s21_decimal dec_1 = {{1, 1, 1, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal equ = {{1, 1, 1, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_subColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_subColumns02) {
  s21_decimal dec_1 = {{2, 2, 2, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal equ = {{2, 2, 2, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_subColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_subColumns03) {
  s21_decimal dec_1 = {{100, 100, 100, 0}};
  s21_decimal dec_2 = {{12, 12, 12, 0}};
  s21_decimal equ = {{88, 88, 88, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_subColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_subColumns04) {
  s21_decimal dec_1 = {{101, 101, 101, 0}};
  s21_decimal dec_2 = {{27, 27, 27, 0}};
  s21_decimal equ = {{74, 74, 74, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_subColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_subColumns05) {
  s21_decimal dec_1 = {{0, 0, 2, 0}};
  s21_decimal dec_2 = {{1, 0, 1, 0}};
  s21_decimal equ = {{MASKA, MASKA, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_subColumns(dec_1, dec_2, &res);
  s21_assertDec(res, equ);
}
END_TEST

START_TEST(tt_setBiggerLesser00) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser01) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser02) {
  s21_decimal dec_1 = {{1, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser03) {
  s21_decimal dec_1 = {{0, 1, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser04) {
  s21_decimal dec_1 = {{0, 0, 1, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser05) {
  s21_decimal dec_1 = {{0, 0, 1, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser06) {
  s21_decimal dec_1 = {{0, 0, 1, 0}};
  s21_decimal dec_2 = {{0, 12, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser07) {
  s21_decimal dec_1 = {{0, 0, 1, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser08) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(1, res);
  s21_assertDec(dec_2, bigger);
  s21_assertDec(dec_1, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser09) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 1, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(1, res);
  s21_assertDec(dec_2, bigger);
  s21_assertDec(dec_1, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser10) {
  s21_decimal dec_1 = {{1, 0, 1, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser11) {
  s21_decimal dec_1 = {{0, 0, 1, 0}};
  s21_decimal dec_2 = {{0, 123, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser12) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 12, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(1, res);
  s21_assertDec(dec_2, bigger);
  s21_assertDec(dec_1, lesser);
}
END_TEST

START_TEST(tt_setBiggerLesser13) {
  s21_decimal dec_1 = {{12, 12, 0, 0}};
  s21_decimal dec_2 = {{12, 12, 0, 0}};
  s21_decimal bigger = {{0, 0, 0, 0}};
  s21_decimal lesser = {{0, 0, 0, 0}};
  int res = s21_setBiggerLesser(dec_1, dec_2, &bigger, &lesser);
  ck_assert_int_eq(0, res);
  s21_assertDec(dec_1, bigger);
  s21_assertDec(dec_2, lesser);
}
END_TEST

START_TEST(tt_div01) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div02) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{1, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div03) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{1, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div04) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div05) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{4, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div06) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{4, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div07) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{4, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div08) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{4, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div09) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{25, 0, 0, 0}};
  s21_setExponent(&equ, 2);
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div10) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{25, 0, 0, MASKE}};
  s21_setExponent(&equ, 2);
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div11) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{25, 0, 0, MASKE}};
  s21_setExponent(&equ, 2);
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div12) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{25, 0, 0, 0}};
  s21_setExponent(&equ, 2);
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div13) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{4, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_setExponent(&dec_1, 1);
  s21_setExponent(&equ, 1);
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div14) {
  s21_decimal dec_1 = {{0, 0, 0, 0}}, dec_2 = {{0, 0, 0, 0}},
              equ = {{0, 0, 0, 0}}, res = {{0, 0, 0, 0}};
  s21_strToDec("12", 0, 0, &dec_1);
  s21_strToDec("3", 1, 0, &dec_2);
  s21_strToDec("40", 0, 0, &equ);
  s21_strToDec("0", 0, 0, &res);
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div15) {
  s21_decimal dec_1 = {{0, 0, 0, 0}}, dec_2 = {{0, 0, 0, 0}},
              equ = {{0, 0, 0, 0}}, res = {{0, 0, 0, 0}};
  s21_strToDec("12", 1, 0, &dec_1);
  s21_strToDec("3", 1, 0, &dec_2);
  s21_strToDec("4", 0, 0, &equ);
  s21_strToDec("0", 0, 0, &res);
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div16) {
  s21_decimal dec_1 = {{0, 0, 0, 0}}, dec_2 = {{0, 0, 0, 0}},
              equ = {{0, 0, 0, 0}}, res = {{0, 0, 0, 0}};
  s21_strToDec("12", 0, 0, &dec_1);
  s21_strToDec("3", 28, 0, &dec_2);
  s21_strToDec("40000000000000000000000000000", 0, 0, &equ);
  s21_strToDec("0", 0, 0, &res);
  int overflow = s21_div(dec_1, dec_2, &res);
  ck_assert_int_eq(0, overflow);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_div17) {
  s21_decimal dec_1 = {{0, 0, 0, 0}}, dec_2 = {{0, 0, 0, 0}},
              res = {{0, 0, 0, 0}};
  s21_strToDec("120", 0, 0, &dec_1);
  s21_strToDec("3", 28, 0, &dec_2);
  s21_strToDec("0", 0, 0, &res);
  int overflow = s21_div(dec_1, dec_2, &res);
  ck_assert_int_eq(1, overflow);
}
END_TEST

START_TEST(tt_div18) {
  s21_decimal dec_1 = {{0, 0, 0, 0}}, dec_2 = {{0, 0, 0, 0}},
              equ = {{0, 0, 0, 0}}, res = {{0, 0, 0, 0}};
  s21_strToDec("12", 28, 0, &dec_1);
  s21_strToDec("3", 1, 0, &dec_2);
  s21_strToDec("4", 27, 0, &equ);
  s21_strToDec("0", 0, 0, &res);
  s21_div(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
  int overflow = s21_div(dec_1, dec_2, &res);
  ck_assert_int_eq(0, overflow);
}
END_TEST

START_TEST(tt_mod01) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod02) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod03) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod04) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{0, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod05) {
  s21_decimal dec_1 = {{14, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod06) {
  s21_decimal dec_1 = {{14, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{2, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod07) {
  s21_decimal dec_1 = {{14, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod08) {
  s21_decimal dec_1 = {{14, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{2, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod09) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{14, 0, 0, 0}};
  s21_decimal equ = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod10) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{14, 0, 0, 0}};
  s21_decimal equ = {{3, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod11) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{14, 0, 0, MASKE}};
  s21_decimal equ = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod12) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{14, 0, 0, MASKE}};
  s21_decimal equ = {{3, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mod13) {
  s21_decimal dec_1 = {{0, 0, 0, 0}}, dec_2 = {{0, 0, 0, 0}},
              equ = {{0, 0, 0, 0}}, res = {{0, 0, 0, 0}};
  s21_strToDec(BIGGEST, 0, 0, &dec_1);
  s21_strToDec("1", 2, 0, &dec_2);
  s21_strToDec("0", 0, 0, &equ);
  s21_mod(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_setGetExp) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int exp = 999;
  exp = s21_getExponent(dec);
  ck_assert_int_eq(0, exp);
  s21_setExponent(&dec, 1);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(1, exp);
  ck_assert_uint_eq(0b00000000000000010000000000000000, dec.bits[3]);
  s21_setExponent(&dec, 3);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(3, exp);
  ck_assert_uint_eq(0b00000000000000110000000000000000, dec.bits[3]);
  dec.bits[3] = MASKE;
  s21_setExponent(&dec, 0);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(0, exp);
  ck_assert_uint_eq(dec.bits[3], 0b10000000000000000000000000000000);
  s21_setExponent(&dec, 1);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(1, exp);
  ck_assert_uint_eq(0b10000000000000010000000000000000, dec.bits[3]);
  s21_setExponent(&dec, 3);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(3, exp);
  ck_assert_uint_eq(0b10000000000000110000000000000000, dec.bits[3]);
}
END_TEST

START_TEST(tt_mulTen01) {
  s21_decimal dec = {{92, 0, 0, 0}};
  s21_mulTen(&dec);
  ck_assert_uint_eq(920, dec.bits[0]);
  ck_assert_uint_eq(0b00000000000000010000000000000000, dec.bits[3]);
  s21_mulTen(&dec);
  ck_assert_uint_eq(9200, dec.bits[0]);
  ck_assert_uint_eq(0b00000000000000100000000000000000, dec.bits[3]);
  s21_mulTen(&dec);
  ck_assert_uint_eq(92000, dec.bits[0]);
  ck_assert_uint_eq(0b00000000000000110000000000000000, dec.bits[3]);
}
END_TEST

START_TEST(tt_mulTen02) {
  s21_decimal dec = {{92, 0, MASKE, 0}};
  int overflow = 0;
  overflow = s21_mulTen(&dec);
  ck_assert_uint_eq(92, dec.bits[0]);
  ck_assert_uint_eq(0, dec.bits[3]);
  ck_assert_int_eq(1, overflow);
}
END_TEST

START_TEST(tt_mulTen03) {
  s21_decimal dec = {{92, 0, 0, 0}};
  int overflow = 0;
  overflow = s21_mulTen(&dec);
  ck_assert_uint_eq(920, dec.bits[0]);
  ck_assert_uint_eq(0b00000000000000010000000000000000, dec.bits[3]);
  ck_assert_int_eq(0, overflow);
  s21_setExponent(&dec, 27);
  overflow = s21_mulTen(&dec);
  ck_assert_uint_eq(9200, dec.bits[0]);
  ck_assert_uint_eq(0b00000000000111000000000000000000, dec.bits[3]);
  ck_assert_int_eq(0, overflow);
  overflow = s21_mulTen(&dec);
  ck_assert_uint_eq(9200, dec.bits[0]);
  ck_assert_uint_eq(0b00000000000111000000000000000000, dec.bits[3]);
  ck_assert_int_eq(1, overflow);
}
END_TEST

START_TEST(tt_incDecExp) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int exp = 999;
  exp = s21_getExponent(dec);
  ck_assert_int_eq(0, exp);
  s21_increaseExponent(&dec);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(1, exp);
  ck_assert_uint_eq(0b00000000000000010000000000000000, dec.bits[3]);
  s21_increaseExponent(&dec);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(2, exp);
  ck_assert_uint_eq(0b00000000000000100000000000000000, dec.bits[3]);
  dec.bits[3] = MASKE;
  s21_setExponent(&dec, 3);
  s21_decreaseExponent(&dec);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(2, exp);
  ck_assert_uint_eq(0b10000000000000100000000000000000, dec.bits[3]);
  s21_decreaseExponent(&dec);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(1, exp);
  ck_assert_uint_eq(0b10000000000000010000000000000000, dec.bits[3]);
  s21_decreaseExponent(&dec);
  exp = s21_getExponent(dec);
  ck_assert_int_eq(0, exp);
  ck_assert_uint_eq(0b10000000000000000000000000000000, dec.bits[3]);
}
END_TEST

START_TEST(tt_divTen01) {
  s21_decimal dec = {{92123, 0, 0, 0b10000000000000110000000000000000}};
  int overflow = 0;
  s21_divTen(&dec);
  ck_assert_uint_eq(9212, dec.bits[0]);
  ck_assert_uint_eq(0b10000000000000100000000000000000, dec.bits[3]);
  ck_assert_int_eq(0, overflow);
  s21_divTen(&dec);
  ck_assert_uint_eq(921, dec.bits[0]);
  ck_assert_uint_eq(0b10000000000000010000000000000000, dec.bits[3]);
  ck_assert_int_eq(0, overflow);
  s21_divTen(&dec);
  ck_assert_uint_eq(92, dec.bits[0]);
  ck_assert_uint_eq(0b10000000000000000000000000000000, dec.bits[3]);
  ck_assert_int_eq(0, overflow);
}
END_TEST

START_TEST(tt_divTen02) {
  s21_decimal dec = {{92, 0, MASKE, 0}};
  int overflow = 0;
  overflow = s21_divTen(&dec);
  ck_assert_uint_eq(92, dec.bits[0]);
  ck_assert_uint_eq(0, dec.bits[3]);
  ck_assert_int_eq(1, overflow);
}
END_TEST

START_TEST(tt_getLastDigit) {
  s21_decimal dec = {{92, 0, 0, 0}};
  int last = 0;
  last = s21_getLastDigit(dec);
  ck_assert_int_eq(2, last);
  dec.bits[0] = 15245;
  last = s21_getLastDigit(dec);
  ck_assert_int_eq(5, last);
  dec.bits[0] = 1524;
  last = s21_getLastDigit(dec);
  ck_assert_int_eq(4, last);
}
END_TEST

START_TEST(tt_roundBank01) {
  s21_decimal dec = {{92, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(9, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank02) {
  s21_decimal dec = {{93, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(9, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank03) {
  s21_decimal dec = {{94, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(9, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank04) {
  s21_decimal dec = {{95, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(10, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank05) {
  s21_decimal dec = {{82, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(8, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank06) {
  s21_decimal dec = {{85, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(8, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank07) {
  s21_decimal dec = {{86, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(9, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank08) {
  s21_decimal dec = {{89, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(9, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank09) {
  s21_decimal dec = {{1, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(0, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank10) {
  s21_decimal dec = {{5, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(0, dec.bits[0]);
}
END_TEST

START_TEST(tt_roundBank11) {
  s21_decimal dec = {{6, 0, 0, 0b00000000000000010000000000000000}};
  s21_roundBank(&dec);
  ck_assert_int_eq(1, dec.bits[0]);
}
END_TEST

START_TEST(tt_normalization01) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_normalization(dec1, dec2, &dec3, &dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(1, dec4.bits[0]);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_int_eq(0, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization02) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 0);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(10, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization03) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 3);
  s21_setExponent(&dec2, 0);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(1000, dec4.bits[0]);
  ck_assert_int_eq(3, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization04) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 0);
  s21_setExponent(&dec2, 1);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(10, dec3.bits[0]);
  ck_assert_uint_eq(1, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization05) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 0);
  s21_setExponent(&dec2, 3);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1000, dec3.bits[0]);
  ck_assert_uint_eq(1, dec4.bits[0]);
  ck_assert_int_eq(3, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization06) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 2);
  s21_setExponent(&dec2, 1);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(10, dec4.bits[0]);
  ck_assert_int_eq(2, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization07) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 2);
  s21_setExponent(&dec2, 6);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(10000, dec3.bits[0]);
  ck_assert_uint_eq(1, dec4.bits[0]);
  ck_assert_int_eq(6, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization08) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 2);
  s21_setExponent(&dec2, 6);
  s21_setBitValue(&dec1, 127, 1);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  int sign1 = s21_getBitValue(dec3, 127);
  int sign2 = s21_getBitValue(dec4, 127);
  ck_assert_int_eq(1, sign1);
  ck_assert_int_eq(0, sign2);
  ck_assert_uint_eq(10000, dec3.bits[0]);
  ck_assert_uint_eq(1, dec4.bits[0]);
  ck_assert_int_eq(6, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization09) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 0);
  s21_setExponent(&dec2, 1);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(0, dec4.bits[0]);
  ck_assert_int_eq(0, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization10) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 0);
  s21_setExponent(&dec2, 0);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(1, dec4.bits[0]);
  ck_assert_int_eq(0, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization11) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 1);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(1, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization12) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{123, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 2);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(12, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization13) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{125, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 2);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(12, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization14) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{126, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 2);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(13, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization15) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{113, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 2);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(11, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization16) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{115, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 2);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(12, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization17) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{117, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 2);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(12, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(tt_normalization18) {
  s21_decimal dec1 = {{1, 0, MASKE, 0}};
  s21_decimal dec2 = {{517, 0, 0, 0}};
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_setExponent(&dec1, 1);
  s21_setExponent(&dec2, 4);
  s21_normalization(dec1, dec2, &dec3, &dec4);
  int exp3 = s21_getExponent(dec3);
  int exp4 = s21_getExponent(dec4);
  ck_assert_uint_eq(1, dec3.bits[0]);
  ck_assert_uint_eq(MASKE, dec3.bits[2]);
  ck_assert_uint_eq(0, dec4.bits[0]);
  ck_assert_int_eq(1, exp3);
  ck_assert_int_eq(exp3, exp4);
}
END_TEST

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}},
              res = {{0, 0, 0, 0}};
  s21_strToDec("123", 28, 0, &val1);
  s21_strToDec("123", 28, 0, &val2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_13) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}},
              res = {{0, 0, 0, 0}};
  s21_strToDec(BIGGEST, 28, 0, &val1);
  s21_strToDec(BIGGEST, 28, 0, &val2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_14) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}},
              res = {{0, 0, 0, 0}};
  s21_strToDec(BIGGEST, 0, 0, &val1);
  s21_strToDec(BIGGEST, 0, 0, &val2);
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_15) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}},
              res = {{0, 0, 0, 0}};
  s21_strToDec(BIGGEST, 0, 1, &val1);
  s21_strToDec(BIGGEST, 0, 1, &val2);
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_16) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}},
              res = {{0, 0, 0, 0}};
  s21_strToDec(BIGGEST, 0, 1, &val1);
  s21_strToDec(BIGGEST, 28, 0, &val2);
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_17) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}},
              res = {{0, 0, 0, 0}};
  s21_strToDec(BIGGEST, 0, 0, &val1);
  s21_strToDec(BIGGEST, 0, 1, &val2);
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(tt_mul00) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul01) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{144, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul02) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{144, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul03) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{144, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul04) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{144, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul05) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{36, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul06) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{36, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul07) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{36, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul08) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{36, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul09) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{36, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul10) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{36, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul11) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{36, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_mul12) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{36, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_2) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_3) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(tt_add_17) {
  int tmp1 = 4294967295;
  s21_decimal dec1 = {{tmp1, tmp1, tmp1, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal res1 = {{0}};
  int ret_s21 = s21_add(dec1, dec2, &res1);
  ck_assert_int_eq(1, ret_s21);
}
END_TEST

START_TEST(tt_add_18) {
  int tmp1 = 4294967295;
  float tmp2 = pow(2, 31);
  s21_decimal dec1 = {{tmp1, tmp1, tmp1, tmp2}};
  s21_decimal dec2 = {{1, 0, 0, tmp2}};
  s21_decimal res1 = {{0}};
  int ret_s21 = s21_add(dec1, dec2, &res1);
  ck_assert_int_eq(2, ret_s21);
}
END_TEST

START_TEST(tt_add_19) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
}
END_TEST

START_TEST(tt_add_20) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
}
END_TEST

START_TEST(tt_add_21) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 1);
}
END_TEST

START_TEST(tt_add_22) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111110;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(tt_add_23) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b00000000000000000000001111111111;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000001111111111;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b00000000000000000010101111110101;
  original_res.bits[1] = 0b00000000000000000000000000000000;
  original_res.bits[2] = 0b00000000000000000000000000000000;
  original_res.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal s21_res = {0};
  s21_add(src1, src2, &s21_res);
  ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(tt_add_24) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_25) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{24, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_26) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_27) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_28) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{24, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_29) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_30) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{9, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_31) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{9, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_32) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{15, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_33) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_34) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{9, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_35) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{9, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_add_36) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{15, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_add(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_14) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(tt_sub_20) {
  // 863
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_21) {
  // 889
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_22) {
  // 915
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_23) {
  // 941
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_24) {
  // 967
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_25) {
  // 993
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_26) {
  // 1019
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000010000100000010000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_27) {
  // 1045
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000101110100011001110100010111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_28) {
  // 1071
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 95;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 5;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_29) {
  // 1097
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000001011001000011001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_30) {
  // 1123
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11111101101100110001110000110000;
  origin.bits[1] = 0b00000000000000000000000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_31) {
  // 1149
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01001100110100101000000111000010;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_32) {
  // 1175
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10001001111001111111111111111110;
  origin.bits[1] = 0b10001010110001110010001100000100;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_33) {
  // 1201
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11111111111111111111111111111110;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_34) {
  // 1227
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;

  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11000000100010111000101000100010;
  origin.bits[1] = 0b11111111111111111111111111111101;
  origin.bits[2] = 0b00000000000000000000000000001001;
  origin.bits[3] = 0b00000000000000010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_35) {
  // 1253
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;

  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10010100100110011101101011101101;
  origin.bits[1] = 0b11000101100100110110100101100010;
  origin.bits[2] = 0b10110000001111101111000110111100;
  origin.bits[3] = 0b10000000000011100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_36) {
  // 1305
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01001110111001000011100101110110;
  origin.bits[1] = 0b01001011001101011010000111011001;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_37) {
  // 1435
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_38) {
  // 1461
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_39) {
  // 1487
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_40) {
  // 1513
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 792281625142643375935439503;
  // src2 = -1;

  src1.bits[0] = 0b00101000111101011100001010001111;
  src1.bits[1] = 0b11110101110000101000111101011100;
  src1.bits[2] = 0b00000010100011110101110000101000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00101000111101011100001010010000;
  origin.bits[1] = 0b11110101110000101000111101011100;
  origin.bits[2] = 0b00000010100011110101110000101000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_41) {
  // 1539
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01011011000111100101100000001101;
  origin.bits[1] = 0b01101101111100110111111101100111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_42) {
  // 1565
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11101000101010001011011101111000;
  origin.bits[1] = 0b00000000000111110100000111110001;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_43) {
  // 1591
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;

  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00001110111111111010100000101010;
  origin.bits[1] = 0b00101001110101100000001000110100;
  origin.bits[2] = 0b00000000000001011111000010100001;
  origin.bits[3] = 0b10000000000110000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_44) {
  // 1617
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11010010100100100111101010001100;
  origin.bits[1] = 0b10011110100111100111000100000100;
  origin.bits[2] = 0b00011111101010011000000100111000;
  origin.bits[3] = 0b10000000000011000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_45) {
  // 1643
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;

  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01011010101111100101111101110011;
  origin.bits[1] = 0b00101101001111010011000001101000;
  origin.bits[2] = 0b00000100101010001101010101010111;
  origin.bits[3] = 0b10000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_46) {
  // 1695
  s21_decimal src1 = {{0, 0, 0, 0}}, src2 = {{0, 0, 0, 0}},
              origin = {{0, 0, 0, 0}};
  // src1 = -7922816251426433759354395033;
  // src2 = 1;

  src1.bits[0] = 0b10011001100110011001100110011001;
  src1.bits[1] = 0b10011001100110011001100110011001;
  src1.bits[2] = 0b00011001100110011001100110011001;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10011001100110011001100110011010;
  origin.bits[1] = 0b10011001100110011001100110011001;
  origin.bits[2] = 0b00011001100110011001100110011001;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(tt_sub_47) {  // -1-(-1)=0
  s21_decimal c = {{100, 0, 0, ~(INT_MAX)}};
  s21_decimal d = {{100, 0, 0, ~(INT_MAX)}};

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
}
END_TEST

START_TEST(tt_sub_48) {
  float tmp = pow(2, 31);
  s21_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal dec2 = {{1, 0, 0, tmp}};
  s21_decimal res1 = {{0}};
  int ret_s21 = s21_sub(dec1, dec2, &res1);
  ck_assert_int_eq(1, ret_s21);
}
END_TEST

START_TEST(tt_sub_49) {
  float tmp = pow(2, 31);
  s21_decimal dec1 = {{4294967295, 4294967295, 4294967295, tmp}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal res1 = {{0}};
  int ret_s21 = s21_sub(dec1, dec2, &res1);
  ck_assert_int_eq(2, ret_s21);
}
END_TEST

START_TEST(tt_sub_50) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111110;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  s21_sub(src1, src2, &s21_res);
  ck_assert_int_eq(s21_sub(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(tt_sub_51) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_res = {0};
  ck_assert_int_eq(s21_sub(src1, src2, &s21_res), 2);
}
END_TEST

START_TEST(tt_sub_52) {
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  s21_decimal dec_2 = {{0, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_53) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_54) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{24, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_55) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{24, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_56) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_57) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{9, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_58) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, 0}};
  s21_decimal equ = {{15, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_59) {
  s21_decimal dec_1 = {{12, 0, 0, 0}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_60) {
  s21_decimal dec_1 = {{12, 0, 0, MASKE}};
  s21_decimal dec_2 = {{3, 0, 0, MASKE}};
  s21_decimal equ = {{9, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_61) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{9, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_62) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, 0}};
  s21_decimal equ = {{15, 0, 0, MASKE}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_63) {
  s21_decimal dec_1 = {{3, 0, 0, 0}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_64) {
  s21_decimal dec_1 = {{3, 0, 0, MASKE}};
  s21_decimal dec_2 = {{12, 0, 0, MASKE}};
  s21_decimal equ = {{9, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_sub(dec_1, dec_2, &res);
  s21_assertAllDec(equ, res);
}
END_TEST

START_TEST(tt_sub_65) {
  s21_decimal src1 = {0}, src2 = {0};
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  s21_decimal result_origin = {0};
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  s21_decimal result_our = {0};
  s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

Suite* suite_generalFunctions(void) {
  Suite* s = suite_create("general functions");
  TCase* tc = tcase_create("get_bit");
  tcase_add_test(tc, tt_getBitValue);
  tcase_add_test(tc, tt_setBitValue);
  tcase_add_test(tc, tt_nullDec);
  tcase_add_test(tc, tt_moveRight);
  tcase_add_test(tc, tt_moveLeft);
  tcase_add_test(tc, tt_addColumns00);
  tcase_add_test(tc, tt_addColumns01);
  tcase_add_test(tc, tt_addColumns02);
  tcase_add_test(tc, tt_addColumns03);
  tcase_add_test(tc, tt_addColumns04);
  tcase_add_test(tc, tt_addColumns05);
  tcase_add_test(tc, tt_addColumns06);
  tcase_add_test(tc, tt_addColumns07);
  tcase_add_test(tc, tt_getSignsSum);
  tcase_add_test(tc, tt_subColumns00);
  tcase_add_test(tc, tt_subColumns01);
  tcase_add_test(tc, tt_subColumns02);
  tcase_add_test(tc, tt_subColumns03);
  tcase_add_test(tc, tt_subColumns04);
  tcase_add_test(tc, tt_subColumns05);
  tcase_add_test(tc, tt_setBiggerLesser00);
  tcase_add_test(tc, tt_setBiggerLesser01);
  tcase_add_test(tc, tt_setBiggerLesser02);
  tcase_add_test(tc, tt_setBiggerLesser03);
  tcase_add_test(tc, tt_setBiggerLesser04);
  tcase_add_test(tc, tt_setBiggerLesser05);
  tcase_add_test(tc, tt_setBiggerLesser06);
  tcase_add_test(tc, tt_setBiggerLesser07);
  tcase_add_test(tc, tt_setBiggerLesser08);
  tcase_add_test(tc, tt_setBiggerLesser09);
  tcase_add_test(tc, tt_setBiggerLesser10);
  tcase_add_test(tc, tt_setBiggerLesser11);
  tcase_add_test(tc, tt_setBiggerLesser12);
  tcase_add_test(tc, tt_setBiggerLesser13);
  suite_add_tcase(s, tc);
  return s;
}

Suite* suite_divmod(void) {
  Suite* s = suite_create("divmod");
  TCase* tc = tcase_create("get_bit");
  tcase_add_test(tc, tt_div01);
  tcase_add_test(tc, tt_div02);
  tcase_add_test(tc, tt_div03);
  tcase_add_test(tc, tt_div04);
  tcase_add_test(tc, tt_div05);
  tcase_add_test(tc, tt_div06);
  tcase_add_test(tc, tt_div07);
  tcase_add_test(tc, tt_div08);
  tcase_add_test(tc, tt_div09);
  tcase_add_test(tc, tt_div10);
  tcase_add_test(tc, tt_div11);
  tcase_add_test(tc, tt_div12);
  tcase_add_test(tc, tt_div13);
  tcase_add_test(tc, tt_div14);
  tcase_add_test(tc, tt_div15);
  tcase_add_test(tc, tt_div16);
  tcase_add_test(tc, tt_div17);
  tcase_add_test(tc, tt_div18);
  tcase_add_test(tc, tt_mod01);
  tcase_add_test(tc, tt_mod02);
  tcase_add_test(tc, tt_mod03);
  tcase_add_test(tc, tt_mod04);
  tcase_add_test(tc, tt_mod05);
  tcase_add_test(tc, tt_mod06);
  tcase_add_test(tc, tt_mod07);
  tcase_add_test(tc, tt_mod08);
  tcase_add_test(tc, tt_mod09);
  tcase_add_test(tc, tt_mod10);
  tcase_add_test(tc, tt_mod11);
  tcase_add_test(tc, tt_mod12);
  tcase_add_test(tc, tt_mod13);
  suite_add_tcase(s, tc);
  return s;
}

Suite* suite_diffrent(void) {
  Suite* s = suite_create("differnt");
  TCase* tc = tcase_create("get_bit");
  tcase_add_test(tc, tt_setGetExp);
  tcase_add_test(tc, tt_mulTen01);
  tcase_add_test(tc, tt_mulTen02);
  tcase_add_test(tc, tt_mulTen03);
  tcase_add_test(tc, tt_incDecExp);
  tcase_add_test(tc, tt_divTen01);
  tcase_add_test(tc, tt_divTen02);
  tcase_add_test(tc, tt_getLastDigit);
  tcase_add_test(tc, tt_roundBank01);
  tcase_add_test(tc, tt_roundBank02);
  tcase_add_test(tc, tt_roundBank03);
  tcase_add_test(tc, tt_roundBank04);
  tcase_add_test(tc, tt_roundBank05);
  tcase_add_test(tc, tt_roundBank06);
  tcase_add_test(tc, tt_roundBank07);
  tcase_add_test(tc, tt_roundBank08);
  tcase_add_test(tc, tt_roundBank09);
  tcase_add_test(tc, tt_roundBank10);
  tcase_add_test(tc, tt_roundBank11);
  tcase_add_test(tc, tt_normalization01);
  tcase_add_test(tc, tt_normalization02);
  tcase_add_test(tc, tt_normalization03);
  tcase_add_test(tc, tt_normalization04);
  tcase_add_test(tc, tt_normalization05);
  tcase_add_test(tc, tt_normalization06);
  tcase_add_test(tc, tt_normalization07);
  tcase_add_test(tc, tt_normalization08);
  tcase_add_test(tc, tt_normalization09);
  tcase_add_test(tc, tt_normalization10);
  tcase_add_test(tc, tt_normalization11);
  tcase_add_test(tc, tt_normalization12);
  tcase_add_test(tc, tt_normalization13);
  tcase_add_test(tc, tt_normalization14);
  tcase_add_test(tc, tt_normalization15);
  tcase_add_test(tc, tt_normalization16);
  tcase_add_test(tc, tt_normalization17);
  tcase_add_test(tc, tt_normalization18);
  suite_add_tcase(s, tc);
  return s;
}

Suite* suite_mul(void) {
  Suite* s = suite_create("suite_mul");
  TCase* tc = tcase_create("mul_tc");
  tcase_add_test(tc, mul_0);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  tcase_add_test(tc, mul_15);
  tcase_add_test(tc, mul_16);
  tcase_add_test(tc, mul_17);
  tcase_add_test(tc, tt_mul00);
  tcase_add_test(tc, tt_mul01);
  tcase_add_test(tc, tt_mul02);
  tcase_add_test(tc, tt_mul03);
  tcase_add_test(tc, tt_mul04);
  tcase_add_test(tc, tt_mul05);
  tcase_add_test(tc, tt_mul06);
  tcase_add_test(tc, tt_mul07);
  tcase_add_test(tc, tt_mul08);
  tcase_add_test(tc, tt_mul09);
  tcase_add_test(tc, tt_mul10);
  tcase_add_test(tc, tt_mul11);
  tcase_add_test(tc, tt_mul12);
  suite_add_tcase(s, tc);
  return s;
}

Suite* suite_sub_1(void) {
  Suite* s = suite_create("suite_sub_1");
  TCase* tc = tcase_create("log_tc");
  tcase_add_test(tc, tt_sub_0);
  tcase_add_test(tc, tt_sub_1);
  tcase_add_test(tc, tt_sub_2);
  tcase_add_test(tc, tt_sub_3);
  tcase_add_test(tc, tt_sub_4);
  tcase_add_test(tc, tt_sub_5);
  tcase_add_test(tc, tt_sub_6);
  tcase_add_test(tc, tt_sub_7);
  tcase_add_test(tc, tt_sub_8);
  tcase_add_test(tc, tt_sub_9);
  tcase_add_test(tc, tt_sub_10);
  tcase_add_test(tc, tt_sub_11);
  tcase_add_test(tc, tt_sub_12);
  tcase_add_test(tc, tt_sub_13);
  tcase_add_test(tc, tt_sub_14);
  tcase_add_test(tc, tt_sub_15);
  tcase_add_test(tc, tt_sub_16);
  tcase_add_test(tc, tt_sub_17);
  tcase_add_test(tc, tt_sub_18);
  tcase_add_test(tc, tt_sub_19);
  tcase_add_test(tc, tt_sub_20);
  tcase_add_test(tc, tt_sub_21);
  tcase_add_test(tc, tt_sub_22);
  tcase_add_test(tc, tt_sub_23);
  tcase_add_test(tc, tt_sub_24);
  tcase_add_test(tc, tt_sub_25);
  tcase_add_test(tc, tt_sub_26);
  tcase_add_test(tc, tt_sub_27);
  tcase_add_test(tc, tt_sub_28);
  tcase_add_test(tc, tt_sub_29);
  tcase_add_test(tc, tt_sub_30);
  suite_add_tcase(s, tc);
  return s;
}

Suite* suite_sub_2(void) {
  Suite* s = suite_create("suite_sub_2");
  TCase* tc = tcase_create("log_tc");
  tcase_add_test(tc, tt_sub_31);
  tcase_add_test(tc, tt_sub_32);
  tcase_add_test(tc, tt_sub_33);
  tcase_add_test(tc, tt_sub_34);
  tcase_add_test(tc, tt_sub_35);
  tcase_add_test(tc, tt_sub_36);
  tcase_add_test(tc, tt_sub_37);
  tcase_add_test(tc, tt_sub_38);
  tcase_add_test(tc, tt_sub_39);
  tcase_add_test(tc, tt_sub_40);
  tcase_add_test(tc, tt_sub_41);
  tcase_add_test(tc, tt_sub_42);
  tcase_add_test(tc, tt_sub_43);
  tcase_add_test(tc, tt_sub_44);
  tcase_add_test(tc, tt_sub_45);
  tcase_add_test(tc, tt_sub_46);
  tcase_add_test(tc, tt_sub_47);
  tcase_add_test(tc, tt_sub_48);
  tcase_add_test(tc, tt_sub_49);
  tcase_add_test(tc, tt_sub_50);
  tcase_add_test(tc, tt_sub_51);
  tcase_add_test(tc, tt_sub_52);
  tcase_add_test(tc, tt_sub_53);
  tcase_add_test(tc, tt_sub_54);
  tcase_add_test(tc, tt_sub_55);
  tcase_add_test(tc, tt_sub_56);
  tcase_add_test(tc, tt_sub_57);
  tcase_add_test(tc, tt_sub_58);
  tcase_add_test(tc, tt_sub_59);
  tcase_add_test(tc, tt_sub_60);
  tcase_add_test(tc, tt_sub_61);
  tcase_add_test(tc, tt_sub_62);
  tcase_add_test(tc, tt_sub_63);
  tcase_add_test(tc, tt_sub_64);
  tcase_add_test(tc, tt_sub_65);
  suite_add_tcase(s, tc);
  return s;
}

Suite* suite_add(void) {
  Suite* s = suite_create("suite_add");
  TCase* tc = tcase_create("case_add");
  tcase_add_test(tc, tt_add_0);
  tcase_add_test(tc, tt_add_1);
  tcase_add_test(tc, tt_add_2);
  tcase_add_test(tc, tt_add_3);
  tcase_add_test(tc, tt_add_4);
  tcase_add_test(tc, tt_add_5);
  tcase_add_test(tc, tt_add_6);
  tcase_add_test(tc, tt_add_7);
  tcase_add_test(tc, tt_add_8);
  tcase_add_test(tc, tt_add_9);
  tcase_add_test(tc, tt_add_10);
  tcase_add_test(tc, tt_add_11);
  tcase_add_test(tc, tt_add_12);
  tcase_add_test(tc, tt_add_13);
  tcase_add_test(tc, tt_add_14);
  tcase_add_test(tc, tt_add_15);
  tcase_add_test(tc, tt_add_16);
  tcase_add_test(tc, tt_add_17);
  tcase_add_test(tc, tt_add_18);
  tcase_add_test(tc, tt_add_19);
  tcase_add_test(tc, tt_add_20);
  tcase_add_test(tc, tt_add_21);
  tcase_add_test(tc, tt_add_22);
  tcase_add_test(tc, tt_add_23);
  tcase_add_test(tc, tt_add_24);
  tcase_add_test(tc, tt_add_25);
  tcase_add_test(tc, tt_add_26);
  tcase_add_test(tc, tt_add_27);
  tcase_add_test(tc, tt_add_28);
  tcase_add_test(tc, tt_add_29);
  tcase_add_test(tc, tt_add_30);
  tcase_add_test(tc, tt_add_31);
  tcase_add_test(tc, tt_add_32);
  tcase_add_test(tc, tt_add_33);
  tcase_add_test(tc, tt_add_34);
  tcase_add_test(tc, tt_add_35);
  tcase_add_test(tc, tt_add_36);
  suite_add_tcase(s, tc);
  return s;
}
