#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result) {
    *result = value;
    setScaleSign(result);
  } else
    error = 1;
  s21_decimal zero = {{0, 0, 0, 0}};
  if (s21_is_equal(value, zero)) {
    *result = zero;
  }
  return error;
}
