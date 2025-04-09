#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  int flag = 1;

  for (int i = 0; str1[0] != '\0' && flag; i++) {
    if (s21_strchr(str2, str1[i]) == S21_NULL)
      result++;
    else
      flag = 0;
  }

  return result;
}

// strcspn - поиск набора символов в строке
// Вычисляет длину начального сегмента строки s, состоящего только из символов
// строки accept. Возвращает количество символов в начальном сегменте s, который
// составляют символы из accept.
//