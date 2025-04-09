#include <stdlib.h>

#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t line1 = s21_strlen(dest);
  s21_size_t line2 = s21_strlen(src);

  s21_size_t line = 0;
  if (n < line2)
    line = line1 + n + 1;
  else
    line = line1 + line2 + 1;

  for (s21_size_t i = line1, j = 0; i < line - 1; i++, j++) dest[i] = src[j];

  dest[line - 1] = '\0';

  return dest;
}

// strncat - конкатенация двух строк
// добавляет первый n символ строки src к строке dest,
// перезаписывая символ `\0' в конце dest и добавляя к строке символ окончания
// `\0'. Строки не могут перекрываться, а в строке dest должно хватать
// свободного места для размещения объединенных строк Bозвращаeт указатель на
// строку, получившуюся в результате объединения dest