#include "../s21_decimal.h"

int s21_from_str_to_decimal(char *num, s21_decimal *dst);

int check_nulls(char *num);

int get_float_scale(char *num);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error_code = OK;
  if (fabsf(src) > 79228162514264337593543950335.0 || fabsf(src) == INFINITY ||
      isnan(src) || dst == NULL) {
    error_code = CONVERTING_ERROR;
  } else if (fabsf(src) < 1e-28 && fabsf(src) > 0.f) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    error_code = CONVERTING_ERROR;
  } else {
    char num[64];
    sprintf(num, "%.6e", src);
    int bits = 0;

    memcpy(&bits, &src, 4);
    s21_decimal tmp = {0};
    short int scale = s21_from_str_to_decimal(num, &tmp);
    if (bits < 0)
      set_sign(&tmp, 1);
    else
      set_sign(&tmp, 0);
    set_scale(&tmp, scale);
    *dst = tmp;
  }
  return error_code;
}

int s21_from_str_to_decimal(char *num, s21_decimal *dst) {
  s21_decimal summand = {{1, 0, 0, 0}}, tmp = {0}, multyplier = {{10, 0, 0, 0}};
  int exponent = get_float_scale(num), exp_min = 0;
  int flag = 0, first_digit = (*num) - '0', meaningless_nulls = 0,
      nulls = check_nulls(num);
  while (*num != 'e') {
    if (!(*num == '.') && !(*num == '-') &&
        (meaningless_nulls != (6 - nulls) || (!flag)) &&
        ((exponent + exp_min) < 28 || (*num == '1')) && (flag != 2)) {
      int offset = 1;
      s21_decimal tmp2 = {{(*num) - '0', 0, 0, 0}}, res = {0};
      exp_min = flag ? exp_min + 1 : exp_min;
      if (((exponent + exp_min) >= 28 && *num == '1')) {
        if (*(num + offset) == '.') offset = 2;
        if (*(num + offset) >= '5') s21_add(tmp2, summand, &tmp2);
      }
      s21_add(tmp, tmp2, &tmp);
      if (((!flag && (nulls != 6)) ||
           ((meaningless_nulls + 1) < (6 - nulls))) &&
          (exponent + exp_min < 28))
        s21_mul(tmp, multyplier, &res);
      else
        s21_add(tmp, res, &res);
      tmp = res;
      meaningless_nulls = flag ? meaningless_nulls + 1 : meaningless_nulls;
      if (exp_min + exponent >= 28 && first_digit > 1 && nulls == 0) {
        tmp.bits[0] /= 10;
        exp_min--;
        flag = 2;
        if (*(num + offset) >= '5') s21_add(tmp, summand, &tmp);
      }
    } else if (*num == '.')
      flag = 1;
    num++;
  }
  num++;
  exponent = exp_min;
  if (*num == '-') {
    num++;
    exponent = (((*(num)) - '0') * 10) + exponent + ((*(num + 1)) - '0');
  } else if (*num == '+') {
    num++;
    exponent = exponent - (((*(num)) - '0') * 10) - (((*(num + 1)) - '0'));
    while ((exponent) < 0) {
      s21_mul(tmp, multyplier, &tmp);
      exponent++;
    }
  }
  *dst = tmp;
  return exponent;
}

int check_nulls(char *num) {
  char *ptr = strchr(num, '.');
  int count = 0;
  while (*ptr != 'e') {
    if (*ptr == '0')
      count++;
    else
      count = 0;
    ptr++;
  }
  return count;
}

int get_float_scale(char *num) {
  int scale = 0;
  char *ptr;
  if (strrchr(num, '+')) {
    ptr = strrchr(num, '+');
    ptr++;
    scale = scale - (((*(ptr++)) - '0') * 10);
    scale = scale - ((*ptr) - '0');
  } else if (strrchr(num, '-')) {
    ptr = strrchr(num, '-');
    ptr++;
    scale = (((*(ptr++)) - '0') * 10) + scale;
    scale = (*ptr) - '0' + scale;
  }
  return scale;
}
