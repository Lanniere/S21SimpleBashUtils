#include "../s21_string.h"

void s21_strcpy(char dest[], const char source[]) {
  int i = 0;
  while (1) {
    dest[i] = source[i];
    if (source[i] == '\0') {
      break;
    }
    i++;
  }
}