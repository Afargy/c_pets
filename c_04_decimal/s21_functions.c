#include "s21_decimal.h"

int s21_getBitValue(s21_decimal dec, int bit) {
  return (dec.bits[bit / 32] & (MASK << (bit % 32))) ? 1 : 0;
}

void s21_setBitValue(s21_decimal *dec, int bit, bool value) {
  value ? (dec->bits[bit / 32] |= MASK << (bit % 32))
        : (dec->bits[bit / 32] &= ~(MASK << (bit % 32)));
}

void s21_nullDec(s21_decimal *dec) {
  for (int i = 0; i < 3; i++) dec->bits[i] = 0;
}

int s21_moveRight(s21_decimal *dec) {
  int overflow = s21_getBitValue(*dec, 95);
  for (int i = 2; i >= 0; i--) {
    dec->bits[i] <<= 1;
    if (i != 0 && (MASKE & dec->bits[i - 1])) s21_setBitValue(dec, i * 32, 1);
  }
  return overflow ? 1 : 0;
}

void s21_moveLeft(s21_decimal *dec) {
  int firstBit = 0;
  for (int i = 2, temp = 0; i >= 0; i--) {
    (s21_getBitValue(*dec, i * 32)) ? (temp = 1) : (temp = 0);
    dec->bits[i] >>= 1;
    if (firstBit) s21_setBitValue(dec, (i + 1) * 32 - 1, 1);
    firstBit = temp;
  }
}

void s21_changeBitValue(s21_decimal *dec, int bit) {
  int value = s21_getBitValue(*dec, bit);
  value ? s21_setBitValue(dec, bit, 0) : s21_setBitValue(dec, bit, 1);
}

int s21_getSignsSum(s21_decimal dec_1, s21_decimal dec_2) {
  int sum = 0;
  sum = s21_getBitValue(dec_1, 127) + s21_getBitValue(dec_2, 127);
  return sum;
}

int s21_compareDec(s21_decimal dec_1, s21_decimal dec_2) {
  int res = 0;
  for (int i = 2; i >= 0 && !res; i--) {
    if (dec_1.bits[i] > dec_2.bits[i]) res = 1;
    if (dec_1.bits[i] < dec_2.bits[i]) res = -1;
  }
  return res;
}

int s21_setBiggerLesser(s21_decimal dec_1, s21_decimal dec_2,
                        s21_decimal *bigger, s21_decimal *lesser) {
  int i = s21_compareDec(dec_1, dec_2);
  if (i == 1 || i == 0) {
    *bigger = dec_1;
    *lesser = dec_2;
    i = 0;
  } else if (i == -1) {
    *bigger = dec_2;
    *lesser = dec_1;
    i = 1;
  }
  return i;
}

int s21_getBinaryLen(s21_decimal dec) {
  int len = 0;
  for (int i = 2; i >= 0; i--) {
    if (dec.bits[i] != 0) {
      for (int j = 31; j >= 0; j--) {
        if ((dec.bits[i] & (MASK << j)) != 0) {
          len = 32 * i + j + 1;
          j = -1;
          i = -1;
        }
      }
    }
  }
  return len;
}

void s21_addBitToTemp(s21_decimal dec_1, s21_decimal *temp, int numLen) {
  s21_moveRight(temp);
  if (s21_getBitValue(dec_1, numLen)) s21_setBitValue(temp, 0, 1);
}

int s21_mulTen(s21_decimal *dec) {
  int overflow = 0;
  s21_decimal original = *dec, temp1 = *dec, temp2 = *dec;
  s21_nullDec(dec);
  for (int j = 0; j < 2; j++) overflow += s21_moveRight(&temp1);
  s21_addColumns(temp1, temp2, dec);
  overflow += s21_moveRight(dec);
  dec->bits[3] = original.bits[3];
  s21_increaseExponent(dec);
  if (overflow || s21_getExponent(*dec) > 28) {
    overflow = 1;
    *dec = original;
  }
  return overflow;
}

int s21_getExponent(s21_decimal dec) {
  int exp = 0;
  for (int i = 119; i > 111; i--) {
    exp <<= 1;
    if (s21_getBitValue(dec, i)) exp++;
  }
  return exp;
}

void s21_setExponent(s21_decimal *dec, int exp) {
  int offset = exp;
  for (int i = 112; i < 120; i++) {
    s21_setBitValue(dec, i, offset & MASK);
    offset >>= 1;
  }
}

void s21_increaseExponent(s21_decimal *dec) {
  int exp = s21_getExponent(*dec);
  s21_setExponent(dec, exp + 1);
}

void s21_decreaseExponent(s21_decimal *dec) {
  int exp = s21_getExponent(*dec);
  s21_setExponent(dec, exp - 1);
}

int s21_divTen(s21_decimal *dec) {
  int zero = 0;
  if (s21_getExponent(*dec) == 0) zero = 1;
  if (!zero) {
    s21_decimal original = *dec, temp1 = *dec, temp2, temp3 = {{0, 0, 0, 0}};
    s21_moveLeft(&temp1);
    temp2 = temp1;
    s21_moveLeft(&temp2);
    s21_addColumns(temp1, temp2, &temp3);
    for (int i = 4; i < 65; i *= 2) {
      temp1 = temp3;
      temp2 = temp3;
      s21_nullDec(&temp3);
      for (int j = 0; j < i; j++) s21_moveLeft(&temp2);
      s21_addColumns(temp1, temp2, &temp3);
    }
    for (int i = 0; i < 3; i++) s21_moveLeft(&temp3);  // temp3 is q
    temp1 = temp3;
    s21_mulTen(&temp1);  // temp1 is q * 10
    s21_nullDec(&temp2);
    s21_subColumns(original, temp1, &temp2);  // temp2 is r
    s21_nullDec(&temp1);
    s21_decimal temp = {{6, 0, 0, 0}};
    s21_addColumns(temp2, temp, &temp1);
    for (int i = 0; i < 4; i++) s21_moveLeft(&temp1);
    s21_nullDec(dec);
    dec->bits[3] = original.bits[3];
    s21_addColumns(temp3, temp1, dec);
    s21_decreaseExponent(dec);
  }
  return zero;
}

int s21_getLastDigit(s21_decimal dec) {
  int last;
  s21_decimal temp = dec, res = {{0, 0, 0, 0}};
  s21_setExponent(&temp, 1);
  s21_divTen(&temp);
  s21_setExponent(&temp, 1);
  s21_mulTen(&temp);
  s21_subColumns(dec, temp, &res);
  last = res.bits[0];
  return last;
}

void s21_roundBank(s21_decimal *dec) {
  s21_decimal temp = *dec;
  int last = s21_getLastDigit(*dec);
  s21_divTen(&temp);
  if (last == 5) {
    int pre_last = s21_getLastDigit(temp);
    (pre_last == 0 || pre_last % 2 == 0) ? (last = 4) : (last = 6);
  }
  if (last > 5) {
    s21_decimal extra = {{1, 0, 0, 0}};
    s21_nullDec(dec);
    s21_addColumns(temp, extra, dec);
    s21_decreaseExponent(dec);
  } else {
    *dec = temp;
  }
}

void s21_normalization(s21_decimal dec_1, s21_decimal dec_2,
                       s21_decimal *temp_1, s21_decimal *temp_2) {
  int diff = s21_getExponent(dec_1) - s21_getExponent(dec_2);
  int reverse = 0, overflow = 0, zero = 0;
  if (diff >= 0) {
    *temp_1 = dec_1;
    *temp_2 = dec_2;
  } else if (diff < 0) {
    *temp_1 = dec_2;
    *temp_2 = dec_1;
    diff = -diff;
    reverse = 1;
  }
  while (!overflow && diff) {
    overflow = s21_mulTen(temp_2);
    if (!overflow) diff--;
  }
  while (!zero && diff) {
    if (diff == 1)
      s21_roundBank(temp_1);
    else
      zero = s21_divTen(temp_1);
    diff--;
  }
  if (reverse) {
    s21_decimal temp_reverse = *temp_1;
    *temp_1 = *temp_2;
    *temp_2 = temp_reverse;
  }
}

void s21_setWrongValue(s21_decimal *dec, int value) {
  s21_nullDec(dec);
  if (value == 1) {
    dec->bits[3] = DINF;
  } else if (value == 2) {
    dec->bits[3] = DMINF;
  } else {
    dec->bits[3] = DNAN;
  }
}

int s21_strToDec(char *num, unsigned exp, bool sign, s21_decimal *dec) {
  int error = s21_checkMaxValue(num);
  if (exp > 28 && error) error = 3;
  if (exp > 28) error = 2;
  if (!error) {
    s21_decimal temp = {{0, 0, 0, 0}}, res;
    s21_nullDec(dec);
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
      s21_setExponent(dec, 1);
      s21_mulTen(dec);
      temp.bits[0] = num[i] - 48;
      s21_nullDec(&res);
      s21_addColumns(temp, *dec, &res);
      *dec = res;
    }
    dec->bits[3] = 0;
    s21_setExponent(dec, exp);
    s21_setBitValue(dec, 127, sign);
  }
  if (error) {
    printf("\n\033[91m");
    printf("ERROR:%d\tERROR:%d\tERROR:%d\t", error, error, error);
    printf("\n\033[39m");
  }
  return error;
}

int s21_checkMaxValue(char *num) {
  int error = 0, len = strlen(num);
  if (len == 29)
    error = strcmp(num, BIGGEST);
  else if (len > 29)
    error = 1;
  if (error > 0)
    error = 1;
  else
    error = 0;
  return error;
}

// for normal dec

void s21_decToNormal(s21_decimal dec, s21_normal_decimal *norm) {
  s21_long_nullDec(norm);
  for (int i = 0; i < 3; i++) norm->bits[i] = dec.bits[i];
  norm->bits[6] = dec.bits[3];
}

void s21_normalToDec(s21_normal_decimal norm, s21_decimal *dec) {
  for (int i = 0; i < 3; i++) dec->bits[i] = norm.bits[i];
  dec->bits[3] = norm.bits[6];
}

int s21_long_getBitValue(s21_normal_decimal dec, int bit) {
  return (dec.bits[bit / 32] & (MASK << (bit % 32))) ? 1 : 0;
}

void s21_long_setBitValue(s21_normal_decimal *dec, int bit, bool value) {
  value ? (dec->bits[bit / 32] |= MASK << (bit % 32))
        : (dec->bits[bit / 32] &= ~(MASK << (bit % 32)));
}

void s21_long_nullDec(s21_normal_decimal *dec) {
  for (int i = 0; i < 8; i++) dec->bits[i] = 0;
}

int s21_long_moveRight(s21_normal_decimal *dec) {
  int overflow = s21_long_getBitValue(*dec, 191);
  for (int i = 5; i >= 0; i--) {
    dec->bits[i] <<= 1;
    if (i != 0 && (MASKE & dec->bits[i - 1]))
      s21_long_setBitValue(dec, i * 32, 1);
  }
  return overflow ? 1 : 0;
}

void s21_long_moveLeft(s21_normal_decimal *dec) {
  int firstBit = 0;
  for (int i = 5, temp = 0; i >= 0; i--) {
    (s21_long_getBitValue(*dec, i * 32)) ? (temp = 1) : (temp = 0);
    dec->bits[i] >>= 1;
    if (firstBit) s21_long_setBitValue(dec, (i + 1) * 32 - 1, 1);
    firstBit = temp;
  }
}

int s21_long_getExponent(s21_normal_decimal dec) {
  int exp = 0;
  for (int i = 215; i > 207; i--) {
    exp <<= 1;
    if (s21_long_getBitValue(dec, i)) exp++;
  }
  return exp;
}

void s21_long_setExponent(s21_normal_decimal *dec, int exp) {
  int offset = exp;
  for (int i = 208; i < 216; i++) {
    s21_long_setBitValue(dec, i, offset & MASK);
    offset >>= 1;
  }
}

int s21_long_mulTen(s21_normal_decimal *dec) {
  int overflow = 0;
  s21_normal_decimal original = *dec, temp1 = *dec, temp2 = *dec;
  s21_long_nullDec(dec);
  for (int j = 0; j < 2; j++) overflow += s21_long_moveRight(&temp1);
  s21_long_addColumns(temp1, temp2, dec);
  overflow += s21_long_moveRight(dec);
  dec->bits[6] = original.bits[6];
  s21_long_increaseExponent(dec);
  if (overflow || s21_long_getExponent(*dec) > 59) {
    overflow = 1;
    *dec = original;
  }
  return overflow;
}

int s21_long_addColumns(s21_normal_decimal value_1, s21_normal_decimal value_2,
                        s21_normal_decimal *result) {
  int overflow = 0;
  for (int i = 0, extra = 0; i < 192; i++) {
    int sum = s21_long_getBitValue(value_1, i) +
              s21_long_getBitValue(value_2, i) + extra;
    if (sum == 1) {
      s21_long_setBitValue(result, i, 1);
      extra = 0;
    } else if (sum == 2) {
      extra = 1;
      if (i == 190) overflow = 1;
    } else if (sum == 3) {
      s21_long_setBitValue(result, i, 1);
      extra = 1;
      if (i == 190) overflow = 1;
    }
  }
  return overflow;
}

void s21_long_increaseExponent(s21_normal_decimal *dec) {
  int exp = s21_long_getExponent(*dec);
  s21_long_setExponent(dec, exp + 1);
}

void s21_long_decreaseExponent(s21_normal_decimal *dec) {
  int exp = s21_long_getExponent(*dec);
  s21_long_setExponent(dec, exp - 1);
}

int s21_long_divTen(s21_normal_decimal *dec) {
  int zero = 0;
  if (s21_long_getExponent(*dec) == 0) zero = 1;
  if (!zero) {
    s21_normal_decimal original = *dec, temp1 = *dec, temp2, temp3 = {0};
    s21_long_moveLeft(&temp1);
    temp2 = temp1;
    s21_long_moveLeft(&temp2);
    s21_long_addColumns(temp1, temp2, &temp3);
    for (int i = 4; i < 129; i *= 2) {
      temp1 = temp3;
      temp2 = temp3;
      s21_long_nullDec(&temp3);
      for (int j = 0; j < i; j++) s21_long_moveLeft(&temp2);
      s21_long_addColumns(temp1, temp2, &temp3);
    }
    for (int i = 0; i < 3; i++) s21_long_moveLeft(&temp3);  // temp3 is q
    temp1 = temp3;
    s21_long_mulTen(&temp1);  // temp1 is q * 10
    s21_long_nullDec(&temp2);
    s21_long_subColumns(original, temp1, &temp2);  // temp2 is r
    s21_long_nullDec(&temp1);
    s21_normal_decimal temp = {{6, 0, 0, 0, 0, 0, 0}};
    s21_long_addColumns(temp2, temp, &temp1);
    for (int i = 0; i < 4; i++) s21_long_moveLeft(&temp1);
    s21_long_nullDec(dec);
    dec->bits[6] = original.bits[6];
    s21_long_addColumns(temp3, temp1, dec);
    s21_long_decreaseExponent(dec);
  }
  return zero;
}

void s21_long_subColumns(s21_normal_decimal value_1, s21_normal_decimal value_2,
                         s21_normal_decimal *result) {
  for (int i = 0, extra = 0; i < 192; i++) {
    int dif =
        s21_long_getBitValue(value_1, i) - s21_long_getBitValue(value_2, i);
    if (dif == -1 && !extra) {
      extra = 1;
      s21_long_setBitValue(result, i, 1);
    } else if (dif == 0 && extra) {
      s21_long_setBitValue(result, i, 1);
    } else if (!extra && dif == 1) {
      s21_long_setBitValue(result, i, 1);
    } else if (extra && dif == 1) {
      extra = 0;
    }
  }
}

int s21_long_getLastDigit(s21_normal_decimal dec) {
  int last;
  s21_normal_decimal temp = dec, res = {0};
  s21_long_setExponent(&temp, 1);
  s21_long_divTen(&temp);
  s21_long_setExponent(&temp, 1);
  s21_long_mulTen(&temp);
  s21_long_subColumns(dec, temp, &res);
  last = res.bits[0];
  return last;
}

int s21_long_checkOverflowForDec(s21_normal_decimal dec) {
  int overflow = 0;
  for (int i = 3; i < 6; i++) overflow += (dec.bits[i] != 0);
  return overflow ? 1 : 0;
}
