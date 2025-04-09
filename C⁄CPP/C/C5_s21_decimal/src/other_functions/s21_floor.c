#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error_code = OK;
  if (result == NULL || get_scale(&value) > 28 || value.bits[3] << 16 != 0) {
    error_code = INF;
  } else if (get_sign(&value) == 1) {
    int scale = get_scale(&value);
    set_sign(&value, 0);
    if (scale == 0)
      error_code = s21_truncate(value, result);
    else {
      error_code = s21_truncate(value, result);
      if (!is_zero(value) && get_mantissa(value)) result->bits[0] += 1;
    }
    set_sign(result, 1);
  } else {
    error_code = s21_truncate(value, result);
  }
  return error_code;
}
