#include "../s21_decimal.h"

int s21_div(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  int error_code = null_check(&number_1, &number_2, result);
  if (is_zero(number_2)) {
    error_code = DIVISION_BY_ZERO;
  }
  if (!error_code) {
    int add_error_code = OK;
    clear_bits(result);
    int res_sign = 0;
    int scale = get_scale(&number_1) - get_scale(&number_2);
    if (get_sign(&number_1) != get_sign(&number_2)) {
      res_sign = 1;
    }

    set_scale(&number_2, 0);
    set_scale(&number_1, 0);
    set_sign(&number_2, 0);
    set_sign(&number_1, 0);

    s21_big_decimal num1;
    s21_big_decimal num2;
    s21_big_decimal res = {0};
    copy_s21_decimal_to_s21_big_decimal(&number_1, &num1);
    copy_s21_decimal_to_s21_big_decimal(&number_2, &num2);
    s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
    s21_big_decimal ostatok = {0};

    bit_division(num1, num2, &ostatok, &num1);
    bits_copy(num1, &res);

    int pos = last_bit_big(res);
    while (!is_zero_big(ostatok) && (pos < 195) && (scale < 29)) {
      bit_multiplication(ostatok, ten, &ostatok);
      bit_division(ostatok, num2, &ostatok, &num1);
      error_code = bit_multiplication(res, ten, &res);
      add_error_code = bit_addition(res, num1, &res);
      pos = last_bit_big(res);
      scale++;
    }

    if ((pos > 95) && (scale == 0)) {
      error_code = INF;
    }

    if ((scale < 0) || error_code || add_error_code) {
      if (res_sign) {
        error_code = NEGATIVE_INF;
      } else {
        error_code = INF;
      }
    } else {
      set_scale_big(&res, scale);
      big_to_normal(&res, result);
      set_sign(result, res_sign);
    }
  }
  return error_code;
}

void bits_copy(s21_big_decimal src, s21_big_decimal *dest) {
  dest->bits[0] = src.bits[0];
  dest->bits[1] = src.bits[1];
  dest->bits[2] = src.bits[2];
  dest->bits[3] = src.bits[3];
  dest->bits[4] = src.bits[4];
  dest->bits[5] = src.bits[5];
  dest->bits[6] = src.bits[6];
}

void bit_division(s21_big_decimal number1, s21_big_decimal number2,
                  s21_big_decimal *remainder, s21_big_decimal *res) {
  clear_bits_big(remainder);
  clear_bits_big(res);
  for (int i = last_bit_big(number1); i >= 0; i--) {
    if (get_bit_big(&number1, i)) {
      set_bit_big(remainder, 0, 1);
    }

    if (is_greater_or_equal(*remainder, number2)) {
      bit_substraction(*remainder, number2, remainder);
      if (i != 0) {
        shift_left_big(remainder, 1);
      }
      if (get_bit_big(&number1, i - 1)) {
        set_bit_big(remainder, 0, 1);
      }

      shift_left_big(res, 1);
      set_bit_big(res, 0, 1);
    } else {
      shift_left_big(res, 1);
      if (i != 0) {
        shift_left_big(remainder, 1);
      }
      if (((i - 1) >= 0) && get_bit_big(&number1, i - 1)) {
        set_bit_big(remainder, 0, 1);
      }
    }
  }
}

int is_greater_or_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
  return (is_greater(value_1, value_2) || is_equal(value_1, value_2));
}

int is_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
  int stop = 0;
  int code_error = true;
  for (int i = 5; i >= 0 && stop == 0; i--) {
    if (value_1.bits[i] != value_2.bits[i]) {
      code_error = false;
      stop = 1;
    }
  }
  return code_error;
}

int is_greater(s21_big_decimal value_1, s21_big_decimal value_2) {
  int stop = 0;
  int code_error = false;
  int scale1 = get_scale_big(&value_1);
  int scale2 = get_scale_big(&value_2);
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};

  if (scale1 > scale2) {
    while (scale1 > scale2) {
      bit_multiplication(value_2, ten, &value_2);
      scale2++;
    }
    set_scale_big(&value_2, scale2);
  } else if (scale2 > scale1) {
    while (scale2 > scale1) {
      bit_multiplication(value_1, ten, &value_1);
      scale1++;
    }
    set_scale_big(&value_1, scale1);
  }

  for (int i = 5; i >= 0 && stop == 0; i--) {
    if (value_1.bits[i] < value_2.bits[i]) {
      code_error = false;
      stop = 1;
    } else if (value_1.bits[i] > value_2.bits[i]) {
      code_error = true;
      stop = 1;
    }
  }
  return code_error;
}
