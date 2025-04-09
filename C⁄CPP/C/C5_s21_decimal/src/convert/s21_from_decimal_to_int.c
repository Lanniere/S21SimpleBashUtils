#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code = OK;
  s21_decimal int_min = {{0x80000000, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal int_max = {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x00000000}};
  s21_truncate(src, &src);
  if ((s21_is_less(src, int_min)) || (s21_is_greater(src, int_max)) ||
      dst == NULL || get_scale(&src) > 28 || src.bits[3] << 16 != 0)
    error_code = CONVERTING_ERROR;
  else {
    int tmp = *dst;
    int sign = get_sign(&src);
    for (int i = 0; i < 31; i++) {
      int bit;
      bit = get_bit(&src, i);
      tmp += bit * (int)pow(2, i);
    }

    if (sign) tmp *= -1;
    *dst = tmp;
    if (src.bits[0] == 0x80000000 && sign) {
      *dst = 0x80000000;
    }
  }
  return error_code;
}
