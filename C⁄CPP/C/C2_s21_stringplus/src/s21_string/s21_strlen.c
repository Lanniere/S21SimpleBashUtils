#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  char *tmp = (char *)str;
  s21_size_t length = 0;

  while (*tmp != '\0') {
    length++;
    tmp++;
  }

  return length;
}

// strlen - вычисляет длину строки
// Вычисляет длину строки s. Завершающий символ `\0'не учитывается.
// Функция strlen() возвращает количество символов в строке s.