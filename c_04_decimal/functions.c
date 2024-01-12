#include "s21_decimal.h"

void dec_to_normal(s21_normal_decimal *x, s21_decimal y) {
  for (int i = 0; i < 3; i++) {
    x->bits[i] = y.bits[i];
  }
  x->bits[6] = y.bits[3];
}

int init_decimal(s21_decimal *x) {
  for (int i = 0; i < 4; i++) {
    x->bits[i] = 0;
  }
  return 0;
}

int getBit(s21_decimal x, int i) {
  int res = 0;
  unsigned int mask = 1u << (i % 32);
  return res = x.bits[i / 32] & mask ? 1 : 0;
}
void setBit(s21_decimal *x, int i) {
  unsigned int mask = 1u << (i % 32);
  x->bits[i / 32] |= mask;
}
int getScaleSign(s21_decimal x) {
  unsigned int mask = 1u << 31;
  return x.bits[3] & mask;
}
int getScaleN(s21_decimal x) {
  unsigned int mask = 0;
  unsigned int res = 0;
  for (int i = 16; i < 24; i++) {
    mask = 1u << i;
    res += x.bits[3] & mask;
  }
  res >>= 16;
  return res;
}
void setScaleSign(s21_decimal *x) {
  unsigned int mask = 1u << 31;
  if (getScaleSign(*x) != 0)
    x->bits[3] &= (~mask);
  else
    x->bits[3] |= mask;
}
int setScaleN(s21_decimal *x, int i) {
  int error = 0;
  if (i <= 16 && i >= 0) {
    unsigned int flag = getScaleSign(*x);
    x->bits[3] = i;
    x->bits[3] <<= 16;
    if (flag != 0) {
      setScaleSign(x);
    }
    error = 1;
  }
  return error;
}

int getBitExp(float src) {
  int i = 31;
  int i_exp = 8;
  int res = 0;
  unsigned int xbit = *((unsigned int *)&src);
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    i--;
    if (i <= 30 && i >= 22) {
      res += pow(2, i_exp) * !!(xbit & mask);
      i_exp--;
    }
  }
  return res - 127;
}

void float_up_down(float x, s21_decimal *dst, float *r2) {
  int ind = 31;
  unsigned int xbit = *((unsigned int *)&x);
  int exp = getBitExp(x);
  setBit(dst, exp);
  double res2 = 0;
  exp--;
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    if (ind <= 22) {
      if (exp >= 0 && !!(xbit & mask)) {
        setBit(dst, exp);
      }
      if (exp < 0) {
        res2 += pow(2, exp) * !!(xbit & mask);
      }
      exp--;
    }
    ind--;
  }
  *r2 = (float)res2;
}

void res_float_to_dec(int scale, int scale_res, int res2, int sign,
                      s21_decimal *dst) {
  s21_decimal dst_ost = {0};
  s21_decimal result_fl = {0};
  init_decimal(&dst_ost);
  init_decimal(&result_fl);
  int res_ost = res2;
  s21_from_int_to_decimal(res_ost, &dst_ost);
  s21_add(*dst, dst_ost, &result_fl);
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = result_fl.bits[i];
  }
  setScaleN(dst, scale + scale_res);
  if (sign) {
    setScaleSign(dst);
  }
}
