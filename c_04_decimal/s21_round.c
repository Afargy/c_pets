#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0, N = 0, sign = 0, last = 0;
  N = getScaleN(value);
  sign = getScaleSign(value);
  if (N < 29 && N > 0) {
    s21_decimal buf = {{0, 0, 0, 0}};
    buf = value;
    addition_truncate(&buf, N - 1);
    last = addition_round(&buf);
    if (last > 5 || (last == 5 && getBit(buf, 0) != 0)) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_add(one, buf, result);
    } else
      *result = buf;
  } else if (N == 0) {
    *result = value;
  } else {
    error = 1;
  }
  result->bits[3] = 0;
  if (error == 0 && sign != 0) setScaleSign(result);
  return error;
}

int addition_round(s21_decimal *res) {
  unsigned long long number = 0;
  int remainder = 0;
  number = res->bits[2];
  for (int j = 2; j >= 0; j--) {
    if (j == 0) {
      remainder = number % 10;
      res->bits[j] = number / 10;
    } else {
      remainder = number % 10;
      res->bits[j] = number / 10;
      number = remainder * (4294967296) + res->bits[j - 1];
    }
  }
  return remainder;
}
