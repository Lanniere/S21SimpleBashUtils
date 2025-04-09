#include <stdio.h>

#include "../s21_string.h"

int s21_strcmp(const char* str1, const char* str2) {
  while (*str1 && *str2) {
    if (*str1 != *str2) {
      return (unsigned char)*str1 - (unsigned char)*str2;
    }
    str1++;
    str2++;
  }
  return (unsigned char)*str1 - (unsigned char)*str2;
}