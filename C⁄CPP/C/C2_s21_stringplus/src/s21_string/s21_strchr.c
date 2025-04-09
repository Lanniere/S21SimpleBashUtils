#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *tmp = (char *)str;

  while (*tmp != (char)c && *tmp != '\0') {
    tmp++;
  }

  if (*tmp == '\0' && c != '\0') tmp = S21_NULL;

  return tmp;
}

// strchr - определение местонахождения символа в строке
// Функция strchr() возвращает указатель на местонахождение первого совпадения с
// символом c в строке s. Eсли символ не найден, то возвращают NULL.
