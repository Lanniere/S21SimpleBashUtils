#include "../s21_decimal.h"

int s21_mul(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  int error_code = null_check(&number_1, &number_2, result);
  if (!error_code) {
    clear_bits(result);
    int res_sign;
    if (get_sign(&number_1) != get_sign(&number_2)) {
      res_sign = 1;
    } else {
      res_sign = 0;
    }

    s21_big_decimal num1;
    s21_big_decimal num2;
    s21_big_decimal res = {0};
    copy_s21_decimal_to_s21_big_decimal(&number_1, &num1);
    copy_s21_decimal_to_s21_big_decimal(&number_2, &num2);

    s21_decimal tmp = {{0, 0, 0, 0}};
    int inf_check = OK;

    inf_check = bit_multiplication(num1, num2, &res);
    int scale = get_scale(&number_1) + get_scale(&number_2);
    set_scale_big(&res, scale);
    if (!inf_check) inf_check = big_to_normal(&res, &tmp);

    if (inf_check == INF) {
      if (res_sign) {
        error_code = NEGATIVE_INF;
      } else {
        error_code = INF;
      }
    } else {
      *result = tmp;
      set_sign(result, res_sign);
    }
  }
  return error_code;
}
