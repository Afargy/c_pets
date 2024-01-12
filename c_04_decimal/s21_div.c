#include "s21_decimal.h"

void s21_getFrac(s21_decimal dec_1, s21_decimal dec_2, s21_decimal *frac);
void s21_modColumns(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int lres = OK, numLen = s21_getBinaryLen(value_1) - 1,
      exp = s21_getExponent(value_1) - s21_getExponent(value_2),
      sign = s21_getBitValue(value_1, 127) + s21_getBitValue(value_2, 127);
  s21_decimal temp = {0}, temp_res = {0}, temp_div = value_2, frac = {0};
  init_decimal(result);
  s21_setBitValue(&temp_div, 127, 0);
  while (numLen >= 0) {
    s21_addBitToTemp(value_1, &temp, numLen--);
    s21_moveRight(result);
    if (s21_compareDec(temp, temp_div) >= 0) {
      s21_setBitValue(result, 0, 1);
      s21_nullDec(&temp_res);
      s21_subColumns(temp, temp_div, &temp_res);
      temp = temp_res;
    }
  }
  lres = s21_returnExpForDiv(result, exp);  // lres is TOO BIG
  s21_getFrac(value_1, value_2, &frac);
  s21_nullDec(&temp);
  s21_add(*result, frac, &temp);
  *result = temp;
  if (sign == 1) s21_setBitValue(result, 127, 1);
  if (lres && sign) lres = TOO_LOW;
  if ((!value_2.bits[0]) && (!value_2.bits[1]) && (!value_2.bits[2]))
    lres = DIV_ZERO;
  if (lres) s21_setWrongValue(result, lres);
  return lres;
}

void s21_getFrac(s21_decimal dec_1, s21_decimal dec_2, s21_decimal *frac) {
  s21_decimal dec01 = {0}, dec02 = dec_2, temp_1 = {0}, temp_2 = {0},
              temp_3 = {0}, temp_4 = {0};
  int len = 28;
  init_decimal(frac);
  s21_modColumns(dec_1, dec_2, &dec01);
  while (len--) {
    s21_mulTen(&dec01);
    s21_mulTen(frac);
    if (s21_compareDec(dec01, dec02) >= 0) {
      s21_nullDec(&temp_1);
      s21_nullDec(&temp_2);
      s21_nullDec(&temp_3);
      s21_nullDec(&temp_4);
      s21_divColumns(dec01, dec02, &temp_1);
      s21_mul(temp_1, dec02, &temp_3);
      s21_addColumns(*frac, temp_1, &temp_2);
      s21_subColumns(dec01, temp_3, &temp_4);
      *frac = temp_2;
      dec01 = temp_4;
    }
  }
  s21_setExponent(frac, 28);
  for (int i = 0; i < 30; i++) {
    if (s21_getLastDigit(*frac) == 0) s21_divTen(frac);
  }
}

int s21_returnExpForDiv(s21_decimal *result, int exp) {
  int overflow = 0, sign = s21_getBitValue(*result, 127);
  result->bits[3] = 0;
  if (exp < 0)
    while (exp) {
      s21_setExponent(result, 0);
      overflow += s21_mulTen(result);
      exp++;
    }
  if (sign) s21_setBitValue(result, 127, 1);
  s21_setExponent(result, exp);
  return overflow ? 1 : 0;
}

void s21_divColumns(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  s21_nullDec(result);
  int numLen = s21_getBinaryLen(value_1) - 1;
  s21_decimal temp = {0}, temp_res = {0}, temp_div = value_2;
  s21_setBitValue(&temp_div, 127, 0);
  while (numLen >= 0) {
    s21_addBitToTemp(value_1, &temp, numLen--);
    s21_moveRight(result);
    if (s21_compareDec(temp, temp_div) >= 0) {
      s21_setBitValue(result, 0, 1);
      s21_nullDec(&temp_res);
      s21_subColumns(temp, temp_div, &temp_res);
      temp = temp_res;
    }
  }
}

void s21_modColumns(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  s21_nullDec(result);
  int numLen = s21_getBinaryLen(value_1) - 1;
  s21_decimal temp = {0}, temp_res = {0}, temp_div = value_2;
  s21_setBitValue(&temp_div, 127, 0);
  while (numLen >= 0) {
    s21_addBitToTemp(value_1, &temp, numLen--);
    s21_moveRight(result);
    if (s21_compareDec(temp, temp_div) >= 0) {
      s21_setBitValue(result, 0, 1);
      s21_nullDec(&temp_res);
      s21_subColumns(temp, temp_div, &temp_res);
      temp = temp_res;
    }
  }
  *result = temp;
}
