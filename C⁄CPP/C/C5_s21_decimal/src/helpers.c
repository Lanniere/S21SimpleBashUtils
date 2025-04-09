#include "s21_decimal.h"

int get_bit_big(s21_big_decimal* value, int bit) {
  int result = 0;
  unsigned int mask = 1u << (bit % 32);
  result = value->bits[bit / 32] & mask;
  return !!result;
}

int get_bit(s21_decimal* value, int bit) {
  int result = 0;
  unsigned int mask = 1u << (bit % 32);
  result = (value->bits[bit / 32] & mask) >> bit;
  return result;
}

void set_bit_big(s21_big_decimal* varPtr, int bit, int value) {
  unsigned int mask = 1u << (bit % 32);
  if (bit / 32 < 7 && value) {
    varPtr->bits[bit / 32] |= mask;
  } else if (bit / 32 < 7 && !value) {
    varPtr->bits[bit / 32] &= ~mask;
  }
}

void set_bit(s21_decimal* varPtr, int bit, int value) {
  unsigned int mask = 1u << (bit % 32);
  if (bit / 32 < 4 && value) {
    varPtr->bits[bit / 32] |= mask;
  } else if (bit / 32 < 4 && !value) {
    varPtr->bits[bit / 32] &= ~mask;
  }
}

void set_scale(s21_decimal* num, int scale) {
  num->bits[3] &= ~(0xFF << 16);
  num->bits[3] |= (scale << 16);
}

void set_scale_big(s21_big_decimal* num, int scale) {
  num->bits[6] &= ~(0xFF << 16);
  num->bits[6] |= (scale << 16);
}

int get_scale(s21_decimal* num) {
  int result = 0;
  for (int i = 0; i < 8; i++) {
    if (num->bits[3] >> (16 + i) & 1) {
      result += pow(2, i);
    }
  }
  return result;
}

int get_scale_big(s21_big_decimal* num) {
  int result = 0;
  for (int i = 0; i < 8; i++) {
    if (num->bits[6] >> (16 + i) & 1) {
      result += pow(2, i);
    }
  }
  return result;
}

void set_sign(s21_decimal* num, int sign) {
  if (sign) {
    num->bits[3] |= (1u << 31);
  } else {
    num->bits[3] &= ~(1u << 31);
  }
}

int get_sign(s21_decimal* num) { return (num->bits[3] >> 31); }

void clear_bits(s21_decimal* val) { memset(val->bits, 0, sizeof(val->bits)); }
void clear_bits_big(s21_big_decimal* val) {
  memset(val->bits, 0, sizeof(val->bits));
}

void align_scales(s21_decimal* value1, s21_decimal* value2,
                  s21_big_decimal* val1, s21_big_decimal* val2) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  int scale1 = get_scale(value1);
  int scale2 = get_scale(value2);

  copy_s21_decimal_to_s21_big_decimal(value1, val1);
  copy_s21_decimal_to_s21_big_decimal(value2, val2);

  if (scale1 > scale2) {
    while (scale1 > scale2) {
      bit_multiplication(*val2, ten, val2);
      scale2++;
    }
    set_scale(value2, scale2);
  } else if (scale2 > scale1) {
    while (scale2 > scale1) {
      bit_multiplication(*val1, ten, val1);
      scale1++;
    }
    set_scale(value1, scale1);
  }
}

int last_bit_big(s21_big_decimal number) {
  int lastbit = 191;
  while (lastbit >= 0 && get_bit_big(&number, lastbit) == 0) {
    lastbit--;
  }
  if (lastbit == -1) {
    lastbit = 0;
  }
  return lastbit;
}

void copy_s21_decimal_to_s21_big_decimal(s21_decimal* decimal,
                                         s21_big_decimal* big_decimal) {
  for (int i = 0; i < 3; i++) {
    big_decimal->bits[i] = decimal->bits[i];
    big_decimal->bits[i + 3] = 0;
  }
  big_decimal->bits[6] = decimal->bits[3];
}

int is_zero(s21_decimal num1) {
  int result;
  if ((num1.bits[0] == 0) && (num1.bits[1] == 0) && (num1.bits[2] == 0))
    result = 1;
  else {
    result = 0;
  }
  return result;
}

int is_zero_big(s21_big_decimal num1) {
  int result;
  if ((num1.bits[0] == 0) && (num1.bits[1] == 0) && (num1.bits[2] == 0) &&
      (num1.bits[3] == 0) && (num1.bits[4] == 0) && (num1.bits[5]) == 0)
    result = 1;
  else {
    result = 0;
  }
  return result;
}

int shift_left_big(s21_big_decimal* value, int offset) {
  int res = OK;
  int lastbit = last_bit_big(*value);
  if (lastbit + offset > 191) {
    res = INF;
  } else {
    for (int i = 0; i < offset; i++) {
      int bit31 = get_bit_big(value, 31);
      int bit63 = get_bit_big(value, 63);
      int bit95 = get_bit_big(value, 95);
      int bit127 = get_bit_big(value, 127);
      int bit159 = get_bit_big(value, 159);
      value->bits[0] <<= 1;
      value->bits[1] <<= 1;
      value->bits[2] <<= 1;
      value->bits[3] <<= 1;
      value->bits[4] <<= 1;
      value->bits[5] <<= 1;
      if (bit31) set_bit_big(value, 32, 1);
      if (bit63) set_bit_big(value, 64, 1);
      if (bit95) set_bit_big(value, 96, 1);
      if (bit127) set_bit_big(value, 128, 1);
      if (bit159) set_bit_big(value, 160, 1);
    }
  }
  return res;
}

int bit_multiplication(s21_big_decimal val1, s21_big_decimal val2,
                       s21_big_decimal* res) {
  int error_code = OK;
  s21_big_decimal tmp = {0};
  clear_bits_big(res);
  int lastbit = last_bit_big(val1);
  for (int i = 0; i <= lastbit; i++) {
    clear_bits_big(&tmp);
    int currbit = get_bit_big(&val1, i);
    if (currbit) {
      tmp = val2;
      shift_left_big(&tmp, i);
      error_code = bit_addition(*res, tmp, res);
    }
  }
  return error_code;
}

int null_check(const s21_decimal* num1, const s21_decimal* num2,
               const s21_decimal* result) {
  int res = 0;
  if (num1 == NULL || num2 == NULL || result == NULL) {
    res = 1;
  }
  return res;
}
