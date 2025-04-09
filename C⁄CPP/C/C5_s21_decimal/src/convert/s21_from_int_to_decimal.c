#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code_error = OK;
  if (dst != NULL) {
    s21_decimal tmp = *dst;
    if (src < 0) {
      tmp.bits[3] |= 0xFFFFFFFF << 31;
      src = src * -1;
    }
    set_scale(&tmp, 0);
    tmp.bits[0] = src;
    *dst = tmp;
  } else {
    code_error = CONVERTING_ERROR;
  }
  return code_error;
}