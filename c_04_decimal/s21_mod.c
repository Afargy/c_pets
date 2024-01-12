#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int lres = OK, exp = s21_getExponent(value_1) - s21_getExponent(value_2),
      numLen = s21_getBinaryLen(value_1) - 1,
      zero = (!value_2.bits[0]) && (!value_2.bits[1]) && (!value_2.bits[2]);
  s21_decimal temp = {0}, temp_res = {0}, temp_div = value_2, temp01 = value_1;
  temp01.bits[3] = 0;
  init_decimal(result);
  s21_setBitValue(&temp_div, 127, 0);
  lres = s21_returnExpForDiv(&temp01, exp);
  if (lres) {
    exp = s21_getExponent(value_1);
    for (int i = 0; i < s21_getExponent(value_2); i++) {
      s21_setExponent(&temp_div, 1);
      s21_divTen(&temp_div);
    }
    if ((!temp_div.bits[0]) && (!temp_div.bits[1]) && (!temp_div.bits[2]))
      temp_div.bits[0] = 1;
    lres = OK;
  }
  while (numLen >= 0) {
    s21_addBitToTemp(value_1, &temp, numLen--);
    s21_moveRight(result);
    if (s21_compareDec(temp, temp_div) >= 0) {
      s21_setBitValue(result, 0, 1);
      init_decimal(&temp_res);
      s21_subColumns(temp, temp_div, &temp_res);
      temp = temp_res;
    }
  }
  *result = temp;
  s21_setExponent(result, exp);
  if (s21_getBitValue(value_1, 127)) s21_setBitValue(result, 127, 1);
  if (zero) lres = DIV_ZERO;
  if (lres) s21_setWrongValue(result, lres);
  return lres;
}
