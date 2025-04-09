#include "../s21_decimal.h"

int s21_sub(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  return sub_check(number_1, number_2, result);
}

int sub(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  int return_value = null_check(&number_1, &number_2, result);
  int zero = 0;
  if (is_zero(number_2) || is_zero(number_1)) {
    zero = 1;
  }
  if (!return_value) {
    clear_bits(result);
    if (!zero) {
      s21_big_decimal num1 = {0};
      s21_big_decimal num2 = {0};
      s21_big_decimal res = {0};

      copy_s21_decimal_to_s21_big_decimal(&number_1, &num1);
      copy_s21_decimal_to_s21_big_decimal(&number_2, &num2);

      if (get_scale(&number_1) != get_scale(&number_2)) {
        align_scales(&number_1, &number_2, &num1, &num2);
      }

      int bit_substraction_result = OK;
      s21_decimal tmp_res = {0};
      bit_substraction_result = bit_substraction(num1, num2, &res);
      if (get_scale(&number_1) > get_scale(&number_2)) {
        result->bits[3] = tmp_res.bits[3];
      } else {
        result->bits[3] = tmp_res.bits[3];
      }
      if (!bit_substraction_result)
        bit_substraction_result = big_to_normal(&res, &tmp_res);

      if (bit_substraction_result == NEGATIVE_INF) {
        return_value = NEGATIVE_INF;
      } else {
        *result = tmp_res;
        if (get_scale(&number_1) > get_scale(&number_2)) {
          result->bits[3] = number_1.bits[3];
        } else {
          result->bits[3] = number_2.bits[3];
        }
      }
    } else {
      if (is_zero(number_1)) {
        *result = number_2;
      } else {
        *result = number_1;
      }
    }
  }
  return return_value;
}
