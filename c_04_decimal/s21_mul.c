#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int lres = OK, exp = s21_getExponent(value_1) + s21_getExponent(value_2);
  s21_normal_decimal temp_1 = {0}, temp_2 = {0}, temp_res = {0}, res = {0};
  unsigned last = 0, zero = 0;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_decToNormal(value_1, &temp_1);
  s21_decToNormal(value_2, &temp_2);
  temp_1.bits[6] = 0;
  temp_2.bits[6] = 0;
  for (int i = 0; i < 96; i++) {
    if (s21_long_getBitValue(temp_2, i) != 0) {
      s21_long_nullDec(&temp_res);
      s21_long_addColumns(res, temp_1, &temp_res);
      res = temp_res;
    }
    s21_long_moveRight(&temp_1);
  }
  s21_long_setExponent(&res, exp);
  while (
      (s21_long_checkOverflowForDec(res) || s21_long_getExponent(res) > 28) &&
      !zero) {
    last = s21_long_getLastDigit(res);
    zero += s21_long_divTen(&res);
  }
  if (last > 5 || (last == 5 && (s21_long_getLastDigit(res) % 2 ||
                                 s21_long_getLastDigit(res) == 0))) {
    s21_normal_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
    s21_long_nullDec(&temp_res);
    temp_res.bits[6] = res.bits[6];
    s21_long_addColumns(res, one, &temp_res);
    res = temp_res;
  }
  if (s21_getBitValue(value_1, 127) + s21_getBitValue(value_2, 127) == 1)
    s21_long_setBitValue(&res, 223, 1);
  s21_normalToDec(res, result);
  if (zero) lres = zero + s21_getBitValue(*result, 127);
  if (lres) s21_setWrongValue(result, lres);
  return lres;
}
