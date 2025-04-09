#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  bool code_error = true;
  s21_big_decimal val1;
  s21_big_decimal val2;
  copy_s21_decimal_to_s21_big_decimal(&value_1, &val1);
  copy_s21_decimal_to_s21_big_decimal(&value_2, &val2);

  align_scales(&value_1, &value_2, &val1, &val2);

  if (get_sign(&value_1) != get_sign(&value_2)) {
    code_error = false;
  } else {
    int stop = 0;
    for (int i = 5; i >= 0 && stop == 0; i--) {
      if (val1.bits[i] != val2.bits[i]) {
        code_error = false;
        stop = 1;
      }
    }
  }
  return code_error;
}
