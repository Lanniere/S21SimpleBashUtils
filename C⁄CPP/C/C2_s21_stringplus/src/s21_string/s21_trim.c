#include <stdlib.h>

#include "../s21_string.h"

// Returns a new string in which all leading and trailing occurrences of a set
// of specified characters (trim_chars) from the given string (src) are removed.
// In case of any error, return NULL

int left_side(const char *src, const char *trim_chars, int end) {
  int count = 0;
  int size = s21_strlen(trim_chars);
  for (int i = 0; i < size; i++) {
    if (src[end] == trim_chars[i]) count = 1;
  }
  return count;
}

int right_side(const char *src, const char *trim_chars, int end) {
  int count = 0;
  end--;
  int size = s21_strlen(trim_chars);
  for (int i = 0; i < size; i++) {
    if (src[end] == trim_chars[i]) count = 1;
  }
  return count;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *src_new = S21_NULL;
  if (src) {
    if (trim_chars != S21_NULL && trim_chars[0]) {
      s21_size_t size = s21_strlen(src) + 1;
      src_new = calloc(size, sizeof(char));
      s21_size_t start = 0, end = s21_strlen(src);
      while (left_side(src, trim_chars, start)) {
        start++;
      }
      if (start != end) {
        while (right_side(src, trim_chars, end)) end--;
      } else {
        src_new[0] = '\0';
      }
      for (int i = 0; start < end; i++) {
        src_new[i] = src[start];
        start++;
      }
    } else {
      src_new = s21_trim(src, "\t\n");
    }
  }
  return src_new;
}
