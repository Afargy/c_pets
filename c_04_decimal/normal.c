#include "s21_decimal.h"

int getBitNormal(s21_normal_decimal x, int i) {
  int v = 0;
  unsigned int mask = 1u << (i % 32);
  if (x.bits[i / 32] & mask) {
    v = 1;
  }
  return v;
}

void setBitNormal(s21_normal_decimal *x, int i) {
  unsigned int mask = 1u << (i % 32);
  x->bits[i / 32] |= mask;
}

int getScaleNormalN(s21_normal_decimal x) {
  unsigned int mask = 0;
  unsigned int res = 0;
  for (int i = 16; i < 24; i++) {
    mask = 1u << i;
    res += x.bits[6] & mask;
  }
  res >>= 16;
  return res;
}

int init_normal(s21_normal_decimal *x) {
  for (int i = 0; i < 7; i++) {
    x->bits[i] = 0;
  }
  return 0;
}

void sdvigs(s21_normal_decimal *new) {
  int bit;
  int old_bit = 0;
  for (int j = 0; j < 6; j++) {
    bit = getBitNormal(*new, 31 + 32 * j);
    new->bits[j] <<= 1;
    if (old_bit) {
      setBitNormal(new, j * 32);
    }
    old_bit = bit;
  }
}
void normalization(s21_normal_decimal *y1, int big) {
  s21_normal_decimal new_1 = {0};
  s21_normal_decimal new_2 = {0};
  init_normal(&new_1);
  init_normal(&new_2);
  for (int i = 0; i < big; i++) {
    new_1 = *y1;
    new_2 = *y1;
    sdvigs(&new_1);
    for (int j = 0; j < 3; j++) {
      sdvigs(&new_2);
    }
    s21_add_normal(new_1, new_2, y1);
  }
}
int normal_scale(s21_normal_decimal *x, s21_normal_decimal *y) {
  int scale_x = getScaleNormalN(*x);
  int scale_y = getScaleNormalN(*y);
  if (scale_x > scale_y) {
    int big = scale_x - scale_y;
    normalization(y, big);
  }
  if (scale_x < scale_y) {
    int big = scale_y - scale_x;
    normalization(x, big);
  }
  return 0;
}

int s21_add_normal(s21_normal_decimal value_1, s21_normal_decimal value_2,
                   s21_normal_decimal *result) {
  s21_numToZeroNormal(result);
  int extra = 0;

  for (int i = 0; i < 96; i++) {
    int sum = s21_getBitValueNormal(value_1, i) +
              s21_getBitValueNormal(value_2, i) + extra;
    if (sum == 1) {
      setBitNormal(result, i);
      extra = 0;
    }
    if (sum == 2) extra = 1;
    if (sum == 3) {
      setBitNormal(result, i);
      extra = 1;
    }
  }

  return 0;
}

void s21_numToZeroNormal(s21_normal_decimal *num) {
  for (int i = 0; i < 3; i++) {
    num->bits[i] = 0;
  }
}

int s21_getBitValueNormal(s21_normal_decimal num, int bit) {
  unsigned int mask = 1u << (bit % 32);
  return (num.bits[bit / 32] & mask) ? 1 : 0;
}
