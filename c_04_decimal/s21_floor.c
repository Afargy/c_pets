#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  if (getScaleSign(value)) {
    if (getScaleN(value) == 0) {
      result->bits[0] = value.bits[0];
      result->bits[1] = value.bits[1];
      result->bits[2] = value.bits[2];
    } else {
      s21_decimal buf = {{0, 0, 0, 0}};
      buf = value;
      addition_truncate(&buf, getScaleN(value));
      s21_decimal addition = {{1, 0, 0, 0}};
      s21_add(addition, buf, result);
    }
    setScaleSign(result);
  } else {
    s21_truncate(value, result);
  }
  return error;
}
