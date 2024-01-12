#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0, N = 0;
  N = getScaleN(value);
  if (N <= 28) {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    if (N != 0) {
      addition_truncate(result, N);
    }
  } else
    error = 1;
  if (error == 0 && getScaleSign(value) != 0) setScaleSign(result);
  return error;
}

void addition_truncate(s21_decimal *res, int N) {
  unsigned long long number = 0;
  int remainder = 0;
  for (int i = 0; i < N; i++) {
    number = res->bits[2];
    for (int j = 2; j >= 0; j--) {
      if (j == 0) {
        res->bits[j] = number / 10;
      } else {
        remainder = number % 10;
        res->bits[j] = number / 10;
        number = remainder * (4294967296) + res->bits[j - 1];
      }
    }
  }
  res->bits[3] = 0;
}
