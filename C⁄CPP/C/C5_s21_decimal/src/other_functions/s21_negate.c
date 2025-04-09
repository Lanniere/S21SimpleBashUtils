#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int code_error = 0;
  if ((result == NULL) || (get_scale(&value) > 28) ||
      (value.bits[3] << 16 != 0)) {
    code_error = 1;
  } else {
    s21_decimal tmp = {{1, 0, 0, SIGN}};
    code_error = s21_mul(value, tmp, result) == 0 ? 0 : 1;
  }
  return code_error;
}
