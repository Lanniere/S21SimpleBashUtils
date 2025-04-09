#include <errno.h>
#include <limits.h>
#include <stdio.h>

#include "../s21_string.h"

int s21_isdigit(int c) { return c >= '0' && c <= '9'; }

int s21_isspace(int c) {
  return c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' ||
         c == '\r';
}

int s21_tolower(int c) {
  if (c >= 'A' && c <= 'Z') {
    return c + 'a' - 'A';
  }
  return c;
}

int s21_isalpha(int c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

long s21_strtol(const char *nptr, char **endptr, int base) {
  const char *s = nptr;
  long result = 0;
  int sign = 1;
  int any = 0;
  int overflow = 0;
  int digit = 0;
  int valid_digit = 1;

  while (s21_isspace((unsigned char)*s)) {
    s++;
  }

  if (*s == '-') {
    sign = -1;
    s++;
  } else if (*s == '+') {
    s++;
  }

  if ((base == 0 || base == 16) && s[0] == '0' &&
      (s[1] == 'x' || s[1] == 'X')) {
    s += 2;
    base = 16;
  } else if (base == 0 && s[0] == '0') {
    base = 8;
  } else if (base == 0) {
    base = 10;
  }

  if (base < 2 || base > 36) {
    if (endptr != NULL) {
      *endptr = (char *)nptr;
    }
    errno = EINVAL;
    return 0;
  }

  while (*s != '\0' && !overflow && valid_digit) {
    if (s21_isdigit((unsigned char)*s)) {
      digit = *s - '0';
    } else if (s21_isalpha((unsigned char)*s)) {
      digit = s21_tolower((unsigned char)*s) - 'a' + 10;
    } else {
      valid_digit = 0;
    }

    if (valid_digit && digit < base) {
      if (result > (LONG_MAX - digit) / base) {
        errno = ERANGE;
        overflow = 1;
      } else {
        result = result * base + digit;
        any = 1;
        s++;
      }
    } else {
      valid_digit = 0;
    }
  }

  if (endptr != NULL) {
    *endptr = (char *)(any ? s : nptr);
  }

  if (overflow) {
    return sign == 1 ? LONG_MAX : LONG_MIN;
  }

  return sign * result;
}
