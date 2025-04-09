#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *tmp = (char *)str;

  s21_size_t len = s21_strlen(str);

  while (*tmp != '\0') tmp++;

  for (; len > 0 && *tmp != (char)c; len--) {
    tmp--;
  }

  if (len == 0 && *tmp != (char)c) tmp = S21_NULL;

  return tmp;
}

// strrchr - определение местонахождения символа в строке
// Возвращает указатель на местонахождение последнего совпадения с символом c в
// строке s Возвращают указатель на совпадения с соответствующим символом, а
// если символ не найден, то возвращают NULL.
//