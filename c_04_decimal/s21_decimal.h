#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MASK 0b00000000000000000000000000000001
#define MASKE 0b10000000000000000000000000000000
#define MASKA 0b11111111111111111111111111111111
#define DINF 0b00000000000000001111111100000000
#define DMINF 0b10000000000000001111111100000000
#define DNAN 0b01111111000000001111111100000000
#define BIGGEST "79228162514264337593543950335"
#define MINUS_SIGN 2147483648
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0

#define MAX 79228162514264337593543950335
#define MAX_UINT 4294967296
#define NORMAL_VALUE 0
#define INF_VALUE 1
#define N_INF_VALUE 2
#define NAN_VALUE 3
#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0

enum Resulter { OK, TOO_BIG, TOO_LOW, DIV_ZERO };

typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_normal_decimal;

// arithmetic allenhop
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// allenhop new
int s21_getBitValue(s21_decimal dec, int bit);
void s21_setBitValue(s21_decimal *dec, int bit, bool value);
void s21_nullDec(s21_decimal *dec);
int s21_moveRight(s21_decimal *dec);
void s21_moveLeft(s21_decimal *dec);
void s21_changeBitValue(s21_decimal *dec, int bit);
int s21_addColumns(s21_decimal dec_1, s21_decimal dec_2, s21_decimal *result);
int s21_getSignsSum(s21_decimal dec_1, s21_decimal dec_2);
void s21_subColumns(s21_decimal dec_1, s21_decimal dec_2, s21_decimal *result);
int s21_setBiggerLesser(s21_decimal dec_1, s21_decimal dec_2,
                        s21_decimal *bigger, s21_decimal *lesser);
int s21_getBinaryLen(s21_decimal dec);
void s21_addBitToTemp(s21_decimal dec_1, s21_decimal *temp, int numLen);
int s21_mulTen(s21_decimal *dec);
int s21_getExponent(s21_decimal dec);
void s21_setExponent(s21_decimal *dec, int exp);
void s21_increaseExponent(s21_decimal *dec);
void s21_decreaseExponent(s21_decimal *dec);
int s21_divTen(s21_decimal *dec);
int s21_getLastDigit(s21_decimal dec);
void s21_roundBank(s21_decimal *dec);
void s21_normalization(s21_decimal dec_1, s21_decimal dec_2,
                       s21_decimal *temp_1, s21_decimal *temp_2);
int s21_divTen(s21_decimal *dec);
void s21_divTenOneTime(s21_decimal dec, s21_decimal *new);
int s21_getLastDigit(s21_decimal dec);
void s21_bankRounder(s21_decimal *dec);
void s21_setWrongValue(s21_decimal *dec, int value);
int s21_strToDec(char *num, unsigned exp, bool sign, s21_decimal *dec);
int s21_checkMaxValue(char *num);
int s21_decToShort(s21_decimal dec, int *num);
void s21_show(s21_decimal dec);
void s21_showDec(s21_decimal dec);
int s21_compareDec(s21_decimal dec_1, s21_decimal dec_2);
int s21_compare(s21_decimal dec_1, s21_decimal dec_2);
void s21_decToNormal(s21_decimal dec, s21_normal_decimal *norm);
void s21_normalToDec(s21_normal_decimal norm, s21_decimal *dec);
int s21_long_getBitValue(s21_normal_decimal dec, int bit);
void s21_long_setBitValue(s21_normal_decimal *dec, int bit, bool value);
void s21_long_nullDec(s21_normal_decimal *dec);
int s21_long_moveRight(s21_normal_decimal *dec);
void s21_long_moveLeft(s21_normal_decimal *dec);
void s21_long_setExponent(s21_normal_decimal *dec, int exp);
int s21_long_getExponent(s21_normal_decimal dec);
int s21_long_mulTen(s21_normal_decimal *dec);
int s21_long_addColumns(s21_normal_decimal value_1, s21_normal_decimal value_2,
                        s21_normal_decimal *result);
void s21_long_increaseExponent(s21_normal_decimal *dec);
void s21_long_decreaseExponent(s21_normal_decimal *dec);
void s21_long_subColumns(s21_normal_decimal value_1, s21_normal_decimal value_2,
                         s21_normal_decimal *result);
int s21_long_divTen(s21_normal_decimal *dec);
int s21_long_getLastDigit(s21_normal_decimal dec);
void s21_long_showDec(s21_normal_decimal dec);
void s21_long_show(s21_normal_decimal dec);
int s21_long_getDecLen(s21_normal_decimal dec);
int s21_long_checkOverflowForDec(s21_normal_decimal dec);
int s21_long_getBinaryLen(s21_normal_decimal dec);
void s21_long_addBitToTemp(s21_normal_decimal dec_1, s21_normal_decimal *temp,
                           int numLen);
int s21_long_compareDec(s21_normal_decimal dec_1, s21_normal_decimal dec_2);
void s21_divColumns(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);
int s21_returnExpForDiv(s21_decimal *result, int exp);

// сравнение
int s21_is_equal(s21_decimal x, s21_decimal y);
int s21_is_not_equal(s21_decimal x, s21_decimal y);
int s21_is_greater(s21_decimal x, s21_decimal y);
int s21_is_greater_or_equal(s21_decimal x, s21_decimal y);
int s21_is_less(s21_decimal x, s21_decimal y);
int s21_is_less_or_equal(s21_decimal x, s21_decimal y);

// Дргуие функции
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// вспомогательные функции для числа
int getBit(s21_decimal x, int i);
void setBit(s21_decimal *x, int i);
int getScaleSign(s21_decimal x);
int getScaleN(s21_decimal x);
void setScaleSign(s21_decimal *x);
int setScaleN(s21_decimal *x, int i);

// дополнительные функции для конвертора
void float_up_down(float x, s21_decimal *dst, float *r2);
int getBitExp(float src);

// дополнительные функции для округления
void addition_truncate(s21_decimal *res, int N);
int addition_round(s21_decimal *res);

// нормализация числа
void sdvigs(s21_normal_decimal *new);
void normalization(s21_normal_decimal *y1, int big);
int normal_scale(s21_normal_decimal *x, s21_normal_decimal *y);

// конвертор
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// функции для нормализованного числа
int getBitNormal(s21_normal_decimal x, int i);
void setBitNormal(s21_normal_decimal *x, int i);
int getScaleNormalN(s21_normal_decimal x);
int init_normal(s21_normal_decimal *x);
void dec_to_normal(s21_normal_decimal *x, s21_decimal y);
void res_float_to_dec(int scale, int scale_res, int res2, int sign,
                      s21_decimal *dst);

int s21_getDecimalLen(s21_decimal value);
int s21_getReversalBit(s21_decimal num, int bit);
int s21_getBitValue(s21_decimal num, int bit);
void s21_numToZero(s21_decimal *num);
void s21_show(s21_decimal num);
int s21_compare(s21_decimal value_1, s21_decimal value_2);
int init_decimal(s21_decimal *x);
int s21_add_normal(s21_normal_decimal value_1, s21_normal_decimal value_2,
                   s21_normal_decimal *result);
void s21_numToZeroNormal(s21_normal_decimal *num);
int s21_getBitValueNormal(s21_normal_decimal num, int bit);

#endif  // SRC_S21_DECIMAL_H_
