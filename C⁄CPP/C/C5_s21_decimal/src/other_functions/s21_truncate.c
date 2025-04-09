#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error_code = OK;
  int scale = get_scale(&value);
  if (result == NULL || get_scale(&value) > 28 || value.bits[3] << 16 != 0) {
    error_code = INF;
  } else {
    set_scale(&value, 0);
    while (scale--) {
      unsigned long remainder = 0;
      for (int i = 2; i >= 0; i--) {
        unsigned long temp;
        temp = (remainder << 32) | value.bits[i];
        value.bits[i] = temp / 10;
        remainder = temp % 10;
      }
    }
    *result = value;
  }
  return error_code;
}
