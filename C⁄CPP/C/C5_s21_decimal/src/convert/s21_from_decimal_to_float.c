#include "../s21_decimal.h"

union num {
  int integer;
  float flt;
};

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error_code = OK;
  int scale = get_scale(&src);
  int sign = get_sign(&src);
  if (dst == NULL || scale > 28 || src.bits[3] << 16 != 0) {
    error_code = CONVERTING_ERROR;
  } else {
    union num n;
    n.integer = 0;
    for (int i = 0; i < 96; i++) n.flt += get_bit(&src, i) * pow(2, i);
    n.flt /= pow(10, scale);
    if (sign)
      n.integer |= (1u << 31);
    else
      n.integer &= ~(1u << 31);
    *dst = n.flt;
  }
  return error_code;
}