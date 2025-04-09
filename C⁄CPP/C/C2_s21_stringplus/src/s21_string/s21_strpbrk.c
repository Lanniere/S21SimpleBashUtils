#include "../s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  int len1 = s21_strlen(str1);
  int len2 = s21_strlen(str2);
  int flag = 0;
  int i = 0;
  char* result = S21_NULL;
  for (; (i < len1) && !flag; i++) {
    for (int j = 0; (j < len2) && !flag; j++) {
      if (str1[i] == str2[j]) {
        flag++;
        result = (char*)(str1 + i);
      }
    }
  }
  return result;
}

// strpbrk - производит поиск строки для любого набора символов
// Ищет первое совпадение в строке s с любым символом из строки accept
// Bозвращает указатель на символ в s, соответствующий одному из символов в
// наборе accept, или NULL, если такого символа нет в строке.
//