#include "../s21_decimal.h"

int auxiliary_greater(s21_big_decimal value_1, s21_big_decimal value_2,
                      bool code_error) {
  int stop = 0;
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

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  bool code_error = false;
  int sign1 = get_sign(&value_1);
  int sign2 = get_sign(&value_2);

  s21_big_decimal val1;
  s21_big_decimal val2;
  copy_s21_decimal_to_s21_big_decimal(&value_1, &val1);
  copy_s21_decimal_to_s21_big_decimal(&value_2, &val2);

  if (get_scale(&value_1) != get_scale(&value_2)) {
    align_scales(&value_1, &value_2, &val1, &val2);
  }

  if (sign1 != 0 && sign2 == 0) {
    code_error = false;
  } else if (sign1 == 0 && sign2 != 0) {
    code_error = true;
  } else if (sign1 != 0 && sign2 != 0) {
    code_error = auxiliary_greater(val2, val1, code_error);
  } else if (sign1 == 0 && sign2 == 0) {
    code_error = auxiliary_greater(val1, val2, code_error);
  } else {
    code_error = false;
  }
  return code_error;
}
