#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error_code = OK;
  s21_decimal one = {{1, 0, 0, 0}};
  int scale = get_scale(&value);
  int sign = get_sign(&value);
  set_sign(&value, 0);
  if (result == NULL || get_scale(&value) > 28 || value.bits[3] << 16 != 0) {
    error_code = CONVERTING_ERROR;
  } else if (scale == 0) {
    error_code = s21_truncate(value, result);
    set_sign(result, sign);
  } else {
    unsigned long long remainder = 0;
    s21_big_decimal temp = {0};
    copy_s21_decimal_to_s21_big_decimal(&value, &temp);
    for (int i = 0; i < scale; i++) {
      remainder = truncate(temp, &temp, 1);
    }
    error_code = s21_truncate(value, result);
    if (remainder >= 5) s21_add(*result, one, result);
    set_sign(result, sign);
  }
  return error_code;
}
