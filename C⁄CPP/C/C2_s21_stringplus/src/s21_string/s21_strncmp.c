#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  for (int i = 0; (n > 0) && !result; n--, i++) {
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
    }
  }
  return result;
}

// strncmp - сравнение двух строк
// Сравнивает первый n сивол строки str1 со строкой str2.
// Она возвращает целое число, которое меньше, больше нуля или равно ему,
// Eсли str1 соответственно меньше, больше или равно str2.
//