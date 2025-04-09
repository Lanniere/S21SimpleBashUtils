#include "../s21_decimal.h"

int add_check(s21_decimal num1, s21_decimal num2, s21_decimal* result) {
  int res = null_check(&num1, &num2, result);

  if (!res) {
    int sign1 = get_sign(&num1);
    int sign2 = get_sign(&num2);
    set_sign(&num1, 0);
    set_sign(&num2, 0);
    if (sign1 && sign2) {
      res = add(num1, num2, result, 1);
      set_sign(result, 1);
    } else if (!sign1 && !sign2) {
      res = add(num1, num2, result, 0);
      set_sign(result, 0);
    } else {
      if (s21_is_greater_or_equal(num1, num2)) {
        res = sub(num1, num2, result);
        set_sign(result, sign1);
      } else {
        res = sub(num2, num1, result);
        set_sign(result, sign2);
      }
    }
  }
  return res;
}

int sub_check(s21_decimal num1, s21_decimal num2, s21_decimal* result) {
  int res = null_check(&num1, &num2, result);
  if (!res) {
    int sign1 = get_sign(&num1);
    int sign2 = get_sign(&num2);
    set_sign(&num1, 0);
    set_sign(&num2, 0);
    if ((sign1 && sign2) || (!sign1 && !sign2)) {
      if (s21_is_greater_or_equal(num1, num2)) {
        res = sub(num1, num2, result);
        set_sign(result, sign1);
      } else {
        res = sub(num2, num1, result);
        set_sign(result, !sign2);
      }
    } else if (!sign1 && sign2) {
      res = add(num1, num2, result, 1);
      set_sign(result, 0);
    } else if (sign1 && !sign2) {
      res = add(num1, num2, result, 0);
      set_sign(result, 1);
    }

    if (res == 1) {
      res = 2;
    } else if (res == 2) {
      res = 1;
    }
  }

  return res;
}
