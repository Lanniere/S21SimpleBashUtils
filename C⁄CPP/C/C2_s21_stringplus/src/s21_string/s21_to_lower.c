#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;

  char *tmp = (char *)str;

  char *copy = calloc(s21_strlen(str) + 1, sizeof(char));
  char *res = copy;

  for (; *tmp != '\0'; tmp++) {
    if (*tmp >= 'A' && *tmp <= 'Z') {
      *copy = *tmp + 32;
    } else {
      *copy = *tmp;
    }
    copy++;
  }

  return (void *)res;
}
