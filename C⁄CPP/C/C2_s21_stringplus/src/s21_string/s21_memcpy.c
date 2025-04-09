#include "../s21_string.h"

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  char* result = (char*)dest;
  char* src_ptr = (char*)src;
  while (n) {
    *result = *src_ptr;
    result++;
    src_ptr++;
    n--;
  }
  return dest;
}

// memcpy - копирует область памяти
// Функция memcpy() копирует n байтов из области памяти src в область памяти
// dest. Области памяти не могут пересекаться. Возвращает указатель на dest.