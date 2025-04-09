#include "../s21_decimal.h"

int add(s21_decimal number_1, s21_decimal number_2, s21_decimal* result,
        int sign_result) {
  int return_value = null_check(&number_1, &number_2, result);
  int zero = 0;
  if (is_zero(number_2) || is_zero(number_1)) {
    zero = 1;
  }
  if (!return_value) {
    clear_bits(result);
    if (!zero) {
      s21_big_decimal num1;
      s21_big_decimal num2;
      s21_big_decimal res = {0};
      copy_s21_decimal_to_s21_big_decimal(&number_1, &num1);
      copy_s21_decimal_to_s21_big_decimal(&number_2, &num2);

      if (get_scale(&number_1) != get_scale(&number_2)) {
        align_scales(&number_1, &number_2, &num1, &num2);
      }
      int bit_additioin_result = OK;
      int conversion_result = OK;
      s21_decimal tmp_res;
      bit_additioin_result = bit_addition(num1, num2, &res);

      if (get_scale(&number_1) > get_scale(&number_2)) {
        set_scale_big(&res, get_scale(&number_1));
      } else {
        set_scale_big(&res, get_scale(&number_2));
      }

      conversion_result = big_to_normal(&res, &tmp_res);
      if (bit_additioin_result == INF || conversion_result == INF) {
        return_value = INF;
      } else {
        *result = tmp_res;
      }
    } else {
      if (is_zero(number_1)) {
        *result = number_2;
      } else {
        *result = number_1;
      }
    }
  }
  if ((return_value == INF) && (sign_result == 1)) {
    return_value = NEGATIVE_INF;
  }
  return return_value;
}

int s21_add(s21_decimal number_1, s21_decimal number_2, s21_decimal* result) {
  return add_check(number_1, number_2, result);
}
