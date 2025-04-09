#include "../s21_string.h"

void* s21_memchr(const void* str, int ch, s21_size_t size) {
  char* s = (char*)str;

  void* result = S21_NULL;
  int flag = 1;

  for (s21_size_t i = 0; i < size && flag; i++)
    if (*s == (char)ch) {
      result = (void*)s;
      flag = 0;
    } else
      s++;

  return result;
}

// memchr - ведет поиск символа в памяти

// Функция memchr() ищет символ c в первых n байтах той области памяти, на
// которую указывает s. Совпадение первого байта с c (представленным как
// беззнаковый символ) останавливает выполнение операции.
