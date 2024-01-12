#include "s21_decimal.h"

int s21_checkOverflowInAdd(s21_decimal *dec_1, s21_decimal *dec_2,
                           s21_decimal *result, int exp);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int lres = OK, overflow = 0, signs = s21_getSignsSum(value_1, value_2);
  s21_decimal temp_1 = {0}, temp_2 = {0};
  init_decimal(result);
  s21_normalization(value_1, value_2, &temp_1, &temp_2);
  if (signs != 1) {
    overflow = s21_addColumns(temp_1, temp_2, result);
    for (int i = 0; overflow == 1; i++)
      overflow = s21_checkOverflowInAdd(&temp_1, &temp_2, result, i);
    if (overflow == 2) lres = TOO_BIG;
    if (signs) s21_changeBitValue(result, 127);
  } else {
    s21_decimal temp = {{0, 0, 0, 0}};
    temp = temp_2;
    s21_changeBitValue(&temp, 127);
    overflow = s21_sub(temp_1, temp, result);
    if (overflow) lres = TOO_BIG;
  }
  s21_setExponent(result, s21_getExponent(temp_1));
  if (signs && lres) lres = TOO_LOW;
  if (lres) s21_setWrongValue(result, lres);
  return lres;
}

int s21_addColumns(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int overflow = 0;
  s21_nullDec(result);
  for (int i = 0, extra = 0; i < 96; i++) {
    int sum = s21_getBitValue(value_1, i) + s21_getBitValue(value_2, i) + extra;
    if (sum == 1) {
      s21_setBitValue(result, i, 1);
      extra = 0;
    } else if (sum == 2) {
      extra = 1;
      if (i == 95) overflow = 1;
    } else if (sum == 3) {
      s21_setBitValue(result, i, 1);
      extra = 1;
      if (i == 95) overflow = 1;
    }
  }
  return overflow;
}

int s21_checkOverflowInAdd(s21_decimal *dec_1, s21_decimal *dec_2,
                           s21_decimal *result, int exp) {
  int overflow = 0, end = 0;
  init_decimal(result);
  s21_decimal temp_1 = *dec_1, temp_2 = *dec_2;
  int extra = s21_getLastDigit(temp_1) + s21_getLastDigit(temp_2);
  while (exp) {
    end += s21_divTen(&temp_1) + s21_divTen(&temp_2);
    exp--;
  }
  overflow = s21_addColumns(temp_1, temp_2, result);
  if (extra > 5 || (extra == 5 && (s21_getLastDigit(*result) == 0 ||
                                   s21_getLastDigit(*result) % 2 == 0))) {
    s21_decimal one = {{1, 0, 0, 0}}, temp = {{0, 0, 0, 0}};
    overflow += s21_addColumns(*result, one, &temp);
    *result = temp;
    extra -= 10;
    if (extra > 5 || (extra == 5 && s21_getLastDigit(*result) % 2 == 1)) {
      s21_nullDec(&temp);
      overflow += s21_addColumns(*result, one, &temp);
      *result = temp;
    }
  }
  if (overflow) {
    overflow = 1;
    s21_nullDec(result);
  } else {
    *dec_1 = temp_1;
    *dec_2 = temp_2;
  }
  if (end) overflow = 2;
  return overflow;
}
