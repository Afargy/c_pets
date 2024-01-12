#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int lres = OK, zero = 0, signs = s21_getSignsSum(value_1, value_2);
  init_decimal(result);
  s21_decimal temp_1 = {{0, 0, 0, 0}}, temp_2 = {{0, 0, 0, 0}};
  s21_normalization(value_1, value_2, &temp_1, &temp_2);
  if (signs != 1) {
    if (signs == 2) {
      s21_decimal changer = {{0, 0, 0, 0}};
      changer = temp_1;
      temp_1 = temp_2;
      temp_2 = changer;
      s21_changeBitValue(&temp_1, 127);
    }
    s21_decimal bigger = {{0, 0, 0, 0}}, lesser = {{0, 0, 0, 0}};
    if (s21_setBiggerLesser(temp_1, temp_2, &bigger, &lesser))
      s21_setBitValue(result, 127, 1);
    s21_subColumns(bigger, lesser, result);
    s21_setExponent(result, s21_getExponent(temp_1));
  } else {
    s21_decimal temp = temp_2;
    s21_changeBitValue(&temp, 127);
    zero = s21_add(temp_1, temp, result);
    lres = zero;
  }
  if (lres) s21_setWrongValue(result, lres);
  return lres;
}

void s21_subColumns(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  s21_nullDec(result);
  for (int i = 0, extra = 0; i < 96; i++) {
    int dif = s21_getBitValue(value_1, i) - s21_getBitValue(value_2, i);
    if (dif == -1 && !extra) {
      extra = 1;
      s21_setBitValue(result, i, 1);
    } else if (dif == 0 && extra) {
      s21_setBitValue(result, i, 1);
    } else if (!extra && dif == 1) {
      s21_setBitValue(result, i, 1);
    } else if (extra && dif == 1) {
      extra = 0;
    }
  }
}
