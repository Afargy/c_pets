#include "s21_decimal.h"
int s21_is_equal(s21_decimal x, s21_decimal y) {
  int flag = 1;
  if (getScaleSign(x) != getScaleSign(y)) {
    flag = 0;
  } else {
    s21_normal_decimal x1 = {0};
    s21_normal_decimal y1 = {0};
    init_normal(&x1);
    init_normal(&y1);
    dec_to_normal(&x1, x);
    dec_to_normal(&y1, y);
    if ((getScaleN(x) || getScaleN(y)) && (getScaleN(x) != getScaleN(y))) {
      normal_scale(&x1, &y1);
    }
    for (int i = 5; i > -1; i--) {
      if (x1.bits[i] != y1.bits[i]) {
        flag = 0;
        break;
      }
    }
  }
  return flag;
}

int s21_is_not_equal(s21_decimal x, s21_decimal y) {
  int flag = 0;
  if (!s21_is_equal(x, y)) {
    flag = 1;
  }
  return flag;
}

int s21_is_greater(s21_decimal x, s21_decimal y) {
  int flag = 0, flag_great = 0, flag_sign = 0, flag_break = 0;
  if (getScaleSign(x) && !getScaleSign(y)) {
    flag = 0;
  } else if (!getScaleSign(x) && getScaleSign(y)) {
    flag = 1;
  } else {
    if (getScaleSign(x) && getScaleSign(y)) {
      flag_sign = 1;
    }
    s21_normal_decimal x1 = {0};
    s21_normal_decimal y1 = {0};
    init_normal(&x1);
    init_normal(&y1);
    dec_to_normal(&x1, x);
    dec_to_normal(&y1, y);
    if ((getScaleN(x) || getScaleN(y)) && (getScaleN(x) != getScaleN(y))) {
      normal_scale(&x1, &y1);
    }
    for (int i = 5; i > -1; i--) {
      if (x1.bits[i] == y1.bits[i]) {
        continue;
      } else if (x1.bits[i] > y1.bits[i]) {
        flag_great = 1;
        flag_break = 1;
      } else {
        flag_great = 0;
        flag_break = 1;
      }
      if (flag_break) break;
    }
    if (flag_sign) flag_great = !flag_great;
    if (flag_break) flag = flag_great;
  }
  return flag;
}

int s21_is_greater_or_equal(s21_decimal x, s21_decimal y) {
  int flag = 0;
  if (s21_is_greater(x, y) || s21_is_equal(x, y)) {
    flag = 1;
  }
  return flag;
}

int s21_is_less(s21_decimal x, s21_decimal y) {
  int flag = 0;
  if (!s21_is_greater(x, y) && s21_is_not_equal(x, y)) {
    flag = 1;
  }
  return flag;
}

int s21_is_less_or_equal(s21_decimal x, s21_decimal y) {
  int flag = 0;
  if (s21_is_less(x, y) || s21_is_equal(x, y)) {
    flag = 1;
  }
  return flag;
}
