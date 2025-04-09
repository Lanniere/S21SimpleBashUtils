#include "../s21_decimal.h"

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  return s21_is_greater(num2, num1);
}