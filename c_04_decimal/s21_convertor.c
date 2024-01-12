#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = 1;
  if (dst) {
    flag = 0;
    init_decimal(dst);
    if (src < 0) {
      src = -src;
      setScaleSign(dst);
    }
    dst->bits[0] = src;
  }
  return flag;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 1;
  if (dst) {
    flag = 0;
    int sign = 1;
    if (getScaleSign(src)) {
      sign = -1;
    }
    s21_decimal x = {0};
    init_decimal(&x);
    s21_truncate(src, &x);
    if (!x.bits[1] && !x.bits[2]) {
      *dst = x.bits[0] * sign;
    } else {
      flag = 1;
    }
  }
  return flag;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  long double temp = 0;
  for (int i = 0; i < 96; i++) {
    temp += getBit(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -getScaleN(src));
  if (getScaleSign(src)) temp = -temp;
  *dst = (float)temp;
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 1;
  init_decimal(dst);
  if (dst || src != S21_INF || src != S21_NAN) {
    flag = 0;
    if (src == 0) {
      dst->bits[0] = 0;
    } else {
      int sign = 0;
      if (src < 0) {
        sign = 1;
        src = -src;
      }
      int exp = getBitExp(src);
      int scale = 0;
      if (exp >= 95 || exp <= -94) {
        flag = 1;
      } else {
        if (exp < 95) {
          for (; !((int)src); src *= 10, scale++) {
          }
        }
        float res2 = 0;
        float_up_down(src, dst, &res2);
        s21_normal_decimal dst_normal = {0};
        init_normal(&dst_normal);
        dec_to_normal(&dst_normal, *dst);
        int scale_res = 7;
        res2 = floor(res2 * 1e+7);
        while (!fmod(res2, 10) && scale_res > 0) {
          res2 /= 10;
          scale_res--;
        }
        normalization(&dst_normal, scale_res);
        if (dst_normal.bits[3] || dst_normal.bits[4] || dst_normal.bits[5]) {
          flag = 0;
        } else {
          for (int i = 0; i < 3; i++) {
            dst->bits[i] = dst_normal.bits[i];
          }
          res_float_to_dec(scale, scale_res, res2, sign, dst);
        }
      }
    }
  }
  return flag;
}
