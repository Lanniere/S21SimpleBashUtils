#ifndef SRC_S21_DEC_H_
#define SRC_S21_DEC_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGN 0x80000000
#define UINT_MAX 4294967295
#define SIZE_DECIMAL 4
#define BIG_SIZE_DECIMAL 7

enum returns { OK, INF, NEGATIVE_INF, DIVISION_BY_ZERO };
enum converts { SUCCESS, CONVERTING_ERROR };

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_big_decimal;

// print
void print_binary(int num);
void debug_printBinary(s21_decimal decimal);
void debug_printBinary_big(s21_big_decimal big_decimal);

// arifmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
        int sign_result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// arif_helpers
int bit_addition(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *res);
int bit_substraction(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *res);
int sub_check(s21_decimal num1, s21_decimal num2, s21_decimal *result);
int add_check(s21_decimal num1, s21_decimal num2, s21_decimal *result);

// compare
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);

int is_greater(s21_big_decimal value_1, s21_big_decimal value_2);
int is_equal(s21_big_decimal value_1, s21_big_decimal value_2);
int is_greater_or_equal(s21_big_decimal value_1, s21_big_decimal value_2);

// helpers
int get_bit_big(s21_big_decimal *value, int bit);
int get_bit(s21_decimal *value, int bit);
void set_bit_big(s21_big_decimal *varPtr, int bit, int value);
void set_bit(s21_decimal *varPtr, int bit, int value);
void set_scale(s21_decimal *num, int scale);
void set_scale_big(s21_big_decimal *num, int scale);
void set_sign(s21_decimal *num, int sign);
int get_scale(s21_decimal *num);
int get_sign(s21_decimal *num);
int get_scale_big(s21_big_decimal *num);
void clear_bits(s21_decimal *val);
void clear_bits_big(s21_big_decimal *val);
// void align_scales(s21_decimal* num1, s21_decimal* num2);
void align_scales(s21_decimal *value1, s21_decimal *value2,
                  s21_big_decimal *val1, s21_big_decimal *val2);
int big_to_normal(s21_big_decimal *source, s21_decimal *result);
void copy_s21_decimal_to_s21_big_decimal(s21_decimal *decimal,
                                         s21_big_decimal *big_decimal);
int is_zero(s21_decimal num1);
int is_zero_big(s21_big_decimal num1);
int last_bit(s21_decimal number);
int last_bit_big(s21_big_decimal number);
int shift_left(s21_decimal *value, int offset);
int shift_left_big(s21_big_decimal *value, int offset);
// int shift_right(s21_decimal *value, int offset);

int get_mantissa(s21_decimal value);

// convert
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// other functions
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

//
int less_than_zero_check(s21_decimal *number_2);
int null_check(const s21_decimal *num1, const s21_decimal *num2,
               const s21_decimal *result);
unsigned long long truncate(s21_big_decimal value, s21_big_decimal *result,
                            int scale);
int bit_multiplication(s21_big_decimal val1, s21_big_decimal ten,
                       s21_big_decimal *res);
void bit_division(s21_big_decimal number1, s21_big_decimal number2,
                  s21_big_decimal *remainder, s21_big_decimal *res);
void bits_copy(s21_big_decimal src, s21_big_decimal *dest);

#endif  // SRC_S21_DECIMAL_H_