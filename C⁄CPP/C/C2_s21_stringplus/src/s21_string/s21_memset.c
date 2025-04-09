#include "../s21_string.h"

void* s21_memset(void* str, int c, s21_size_t n) {
  char* result = (char*)str;

  while (n) {
    *result = c;
    result++;
    n--;
  }
  return str;
}

// memset - заполняет память определенным символом
// Функция memset() заполняет первые n байтов той области памяти, на которую
// указывает s, постоянным байтом c возвращает указатель на область памяти s.