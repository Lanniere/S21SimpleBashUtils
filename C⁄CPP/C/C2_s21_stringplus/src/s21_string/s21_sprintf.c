#include "s21_sprintf.h"

#include "../s21_string.h"

#define SIZE 5000
#define UINT_MAX 4294967295
#define INT_MAX 2147483647
#define USHRT_MAX 65535

char* s21_strcat(char* dest, char* src);
void flag_width_int(char* buffer, flags* flags);
void flag_width_float(char* buffer, flags* flags);
void format_short(char* buffer, int size, long double value, flags* flags);
int flag_precision_for_g(char* temp, flags* flags, int int_len,
                         double long frac_part);
void flag_precision_for_f(char* temp, flags* flags, double long frac_part);
void flag_precision_for_o(char* temp, flags* flags);
void flag_width_oct(char* buffer, flags* flags);
void flag_compare(flags* flags);
void flag_width_scientific(char* buffer, flags* flags);

void flag_compare(flags* flags) {
  if (flags->minus && flags->zero) {
    flags->zero = 0;
  }
  if (flags->plus && flags->space) {
    flags->space = 0;
  }
}

int is_digit(const char* p) { return (*p >= 48 && *p <= 57); }

void hash_format(char* str, flags* flags, int pos) {
  int len = s21_strlen(str);
  if (flags->specifier == 'p' || flags->specifier == 'x' ||
      flags->specifier == 'X') {
    for (int i = len + 1; i >= 2; i--) {
      str[i] = str[i - 2];
    }
    str[pos] = '0';
    if (flags->specifier == 'X') {
      str[pos + 1] = 'X';
    } else {
      str[pos + 1] = 'x';
    }
    str[len + 2] = '\0';
  }

  if (flags->specifier == 'o') {
    for (int i = len + 1; i >= 0; i--) {
      str[i] = str[i - 1];
    }
    str[pos] = '0';
    str[len + 2] = '\0';
  }
}

void positive_change(int is_negative, long double* value) {
  if (is_negative) {
    *value = -*value;
  }
}

void head_symbol(flags* flags, char* temp, int is_negative) {
  if (is_negative) {
    temp[0] = '-';
  }
  if (!is_negative && flags->plus) {
    temp[0] = '+';
  }
  if (!is_negative && flags->space) {
    temp[0] = ' ';
  }
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);
  const char* p = format;
  char* bufp = str;
  char temp[1024];

  while (*p) {
    if (*p == '%') {
      p++;
      flags flags = {0};

      p = parse_format(p, &flags, args);
      flag_compare(&flags);
      switch (flags.specifier) {
        case 'd':
        case 'i': {
          long long value;
          if (s21_strcmp(flags.length_modifier, "h") == 0) {
            value = (short)va_arg(args, int);
          } else if (s21_strcmp(flags.length_modifier, "l") == 0) {
            value = va_arg(args, long);
          } else {
            value = va_arg(args, int);
          }
          format_int(temp, sizeof(temp), value, &flags);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 'u': {
          unsigned long long value;
          if (s21_strcmp(flags.length_modifier, "h") == 0) {
            value = (unsigned short)va_arg(args, unsigned int);
          } else if (s21_strcmp(flags.length_modifier, "l") == 0) {
            value = va_arg(args, unsigned long);
          } else {
            value = va_arg(args, unsigned int);
          }
          format_unsigned_int(temp, sizeof(temp), value, &flags, 10, 0);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 'o': {
          unsigned long long value;
          if (s21_strcmp(flags.length_modifier, "h") == 0) {
            value = (unsigned short)va_arg(args, unsigned int);
          } else if (s21_strcmp(flags.length_modifier, "l") == 0) {
            value = va_arg(args, unsigned long);
          } else {
            value = va_arg(args, unsigned int);
          }
          format_unsigned_int(temp, sizeof(temp), value, &flags, 8, 0);
          format_hash(temp, &flags);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 'x':
        case 'X': {
          unsigned long long value;
          if (s21_strcmp(flags.length_modifier, "h") == 0) {
            value = (unsigned short)va_arg(args, unsigned int);
          } else if (s21_strcmp(flags.length_modifier, "l") == 0) {
            value = va_arg(args, unsigned long);
          } else {
            value = va_arg(args, unsigned int);
          }
          format_unsigned_int(temp, sizeof(temp), value, &flags, 16,
                              flags.specifier == 'X');
          format_hash(temp, &flags);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 'c': {
          char value = (char)va_arg(args, int);
          format_char(temp, value, &flags);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 's': {
          const char* value = va_arg(args, const char*);
          format_string(temp, value, &flags);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 'f':
        case 'F': {
          long double value;
          if (s21_strcmp(flags.length_modifier, "L") == 0) {
            value = va_arg(args, long double);
          } else {
            value = va_arg(args, double);
          }
          format_float(temp, sizeof(temp), value, &flags);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 'g':
        case 'G': {
          long double value;
          if (s21_strcmp(flags.length_modifier, "L") == 0) {
            value = va_arg(args, long double);
          } else {
            value = va_arg(args, double);
          }
          format_short(temp, sizeof(temp), value, &flags);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 'e':
        case 'E': {
          long double value;
          if (s21_strcmp(flags.length_modifier, "L") == 0) {
            value = va_arg(args, long double);
          } else {
            value = va_arg(args, double);
          }
          int uppercase = 0;
          if (flags.specifier == 'E') uppercase = 1;
          format_scientific(temp, sizeof(temp), value, &flags, uppercase);
          s21_strcpy(bufp, temp);
          bufp += s21_strlen(temp);
          break;
        }
        case 'n': {
          int* value = va_arg(args, int*);
          *value = bufp - str;
          break;
        }
        case '%': {
          *bufp++ = '%';
          break;
        }
      }
    } else {
      *bufp++ = *p++;
    }
  }

  *bufp = '\0';
  va_end(args);

  return s21_strlen(str);
}

const char* parse_format(const char* format, flags* flags, va_list args) {
  const char* p = format;
  flags->precision = -1;

  while (*p == '-' || *p == '+' || *p == ' ' || *p == '#' || *p == '0') {
    switch (*p) {
      case '-':
        flags->minus = 1;
        break;
      case '+':
        flags->plus = 1;
        break;
      case ' ':
        flags->space = 1;
        break;
      case '#':
        flags->hash = 1;
        break;
      case '0':
        flags->zero = 1;
        break;
    }
    p++;
  }

  if (is_digit(p) || (*p == '*')) {
    if (is_digit(p)) flags->width = s21_strtol(p, (char**)&p, 10);
    // if (is_digit(p)) flags->width = string_to_number(p);
    if (*p == '*') {
      flags->width = va_arg(args, int);
      p++;
    }
    // p++;
    // if(flags->width >= 10) p++;
  }

  if (*p == '.' || (*p == '*')) {
    p++;
    int check = 0;
    if (is_digit(p)) {
      flags->precision = s21_strtol(p, (char**)&p, 10);
      check++;
    }
    if (*p == '*') {
      flags->precision = va_arg(args, int);
      p++;
      check++;
    }
    if (check == 0) {
      flags->precision = 0;
    }
  }

  if (*p == 'h' || *p == 'l' || *p == 'L') {
    flags->length_modifier[0] = *p++;
    if ((*p == 'h' || *p == 'l') && (flags->length_modifier[0] == 'h' ||
                                     flags->length_modifier[0] == 'l')) {
      flags->length_modifier[1] = *p++;
    }
  }

  if (s21_strchr("cdieEfgGosuxXpn%", *p)) {
    flags->specifier = *p++;
  }
  return p;
}

void reverse_string(char* str, int len) {
  for (int i = 0; i < len / 2; ++i) {
    char t = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = t;
  }
}

void format_short(char* buffer, int size, long double value, flags* flags) {
  char temp[size];
  int check = 0;
  int int_len = 0;
  int is_negative = value < 0;
  positive_change(is_negative, &value);

  long long int_part = (long long)value;
  long double frac_part = value - int_part;

  if (int_part == 0) {
    temp[int_len++] = '0' + (int_part % 10);
  }

  while (int_part > 0) {
    temp[int_len++] = '0' + (int_part % 10);
    int_part /= 10;
  }

  temp[int_len] = '\0';
  reverse_string(temp, int_len);

  int start = (is_negative || flags->plus || flags->space) ? 1 : 0;
  if (flags->precision == -1) {
    flags->precision = 6;
  }
  if (flags->precision == 0 && temp[0] == '0') {
    flags->precision = 1;
  }

  check = flag_precision_for_g(temp, flags, int_len, frac_part);

  if (start) {
    temp[s21_strlen(temp)] = '\0';

    for (int i = s21_strlen(temp) + 1; i > 0; i--) {
      temp[i] = temp[i - 1];
    }
    head_symbol(flags, temp, is_negative);
  }

  if (!check) {
    s21_strncpy(buffer + start, temp, int_len);
    start += int_len;
    int counter;
    temp[start++] = '.';
    int len = 0;

    for (int i = 1; i <= flags->precision + 1; i++) {
      frac_part *= 10;
      counter = (int)frac_part % 10;
      len++;
    }

    long long int_part = (long long)frac_part / 10;
    if (int_part > 10000) {
      int_part++;
    }
    for (int i = flags->precision + 1; i >= start; i--) {
      counter = int_part % 10;
      temp[i] = '0' + counter;
      int_part /= 10;
    }

    while (temp[len - 1] == '0') {
      len--;
      temp[len] = '\0';
    }
  }
  s21_strcpy(buffer, temp);
}

void format_float(char* buffer, int size, long double value, flags* flags) {
  char temp[size];

  int int_len = 0;

  int is_negative = value < 0;
  positive_change(is_negative, &value);

  long long int_part = (long long)value;
  long double frac_part = value - int_part;

  if (int_part == 0) {
    temp[int_len++] = '0' + (int_part % 10);
  }

  while (int_part > 0) {
    temp[int_len++] = '0' + (int_part % 10);
    int_part /= 10;
  }
  temp[int_len] = '\0';
  reverse_string(temp, int_len);

  int start = (is_negative || flags->plus || flags->space) ? 1 : 0;
  if (flags->precision == -1) {
    flags->precision = 6;
  }
  flag_precision_for_f(temp, flags, frac_part);

  if (start) {
    temp[s21_strlen(temp)] = '\0';

    for (int i = s21_strlen(temp) + 1; i > 0; i--) {
      temp[i] = temp[i - 1];
    }
    head_symbol(flags, temp, is_negative);
  }

  flag_width_float(temp, flags);
  s21_strcpy(buffer, temp);
}

void format_int(char* buffer, int size, long long value, flags* flags) {
  ;
  char temp[size];
  int len = 0;

  int is_negative = value < 0;
  unsigned long long abs_value = is_negative ? -value : value;

  if (abs_value == 0 && flags->precision != 0) {
    temp[len++] = '0' + (abs_value % 10);
  }

  while (abs_value > 0) {
    temp[len++] = '0' + (abs_value % 10);
    abs_value = abs_value / 10;
  }

  if (flags->precision > len) {
    int padding = flags->precision - len;
    while (padding-- > 0) {
      temp[len++] = '0';
    }
  }

  if (is_negative) {
    temp[len++] = '-';
  } else if (flags->plus) {
    temp[len++] = '+';
  } else if (flags->space) {
    temp[len++] = ' ';
  }

  temp[len] = '\0';

  reverse_string(temp, len);
  flag_width_int(temp, flags);
  s21_strcpy(buffer, temp);
}

void format_unsigned_int(char* buffer, int size, unsigned long long value,
                         flags* flags, int base, int uppercase) {
  char temp[size];
  char* digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  int len = 0;

  do {
    temp[len++] = digits[value % base];
    value /= base;
  } while (value > 0);

  reverse_string(temp, len);
  temp[len] = '\0';

  flag_precision_for_o(temp, flags);
  flag_width_oct(temp, flags);
  s21_strcpy(buffer, temp);
}

void format_char(char* buffer, char value, flags* flags) {
  int size = flags->width > 0 ? flags->width - 1 : 0;
  if (flags->minus) {
    buffer[0] = value;
    s21_memset(buffer + 1, ' ', size);
  } else {
    s21_memset(buffer, ' ', size);
    buffer[size] = value;
  }
  buffer[size + 1] = '\0';
}

void format_string(char* buffer, const char* value, flags* flags) {
  int len = s21_strlen(value);
  if (flags->precision >= 0 && len > flags->precision) {
    len = flags->precision;
  }

  int padding = flags->width - len;
  if (padding > 0) {
    if (flags->minus) {
      s21_strncpy(buffer, value, len);
      s21_memset(buffer + len, ' ', padding);
    } else {
      s21_memset(buffer, ' ', padding);
      s21_strncpy(buffer + padding, value, len);
    }
    buffer[flags->width] = '\0';
  } else {
    s21_strncpy(buffer, value, len);
    buffer[len] = '\0';
  }
}

void format_scientific(char* buffer, int size, long double value, flags* flags,
                       int uppercase) {
  char temp[size];
  int len = 0;
  int counter = 0;

  int is_negative = value < 0;
  positive_change(is_negative, &value);

  long long int_part = (long long)value;
  long double frac_part = value - int_part;

  int temp_len = 0;
  while (int_part > 10) {
    double ostatok = int_part % 10;
    frac_part = (frac_part / 10) + ostatok / 10;
    int_part /= 10;
    counter++;
  }

  int round = (int)(frac_part * 10);
  temp[temp_len++] = '0' + (int_part % 10);
  if (round > 4 && flags->precision == 0) {
    temp[temp_len - 1]++;
  }

  round = (int)(frac_part * 10);
  temp[0] = '0' + (int_part % 10);
  temp[1] = '\0';
  if (round > 4 && flags->precision == 0) {
    temp[temp_len - 1]++;
  }

  if (flags->precision == -1) {
    flags->precision = 6;
  }

  flag_precision_for_f(temp, flags, frac_part);

  len = s21_strlen(temp);
  if (uppercase) {
    temp[len] = 'E';
  } else {
    temp[len] = 'e';
  }

  temp[len + 1] = '+';

  if (counter > 10) {
    temp[len + 2] = counter / 10 + 48;
  } else {
    temp[len + 2] = '0';
  }

  temp[len + 3] = counter % 10 + 48;
  temp[len + 4] = '\0';
  flag_width_scientific(temp, flags);
  s21_strcpy(buffer, temp);
}

void format_hash(char* str, flags* flags) {
  if (!(str[0] == '0' && str[1] == '\0')) {
    if (flags->specifier == 'x' || flags->specifier == 'X' ||
        flags->specifier == 'o') {
      int pos = 0;
      while (str[pos] == ' ') {
        pos++;
      }

      if (flags->hash) {
        hash_format(str, flags, pos);
      }
    }
  }
}

char* s21_strcat(char* dest, char* src) {
  char* ptr = dest;
  while (*ptr != '\0') {
    ptr++;
  }

  while (*src != '\0') {
    *ptr = *src;
    ptr++;
    src++;
  }
  *ptr = '\0';
  return dest;
}

void flag_width_oct(char* buffer, flags* flags) {
  int len = s21_strlen(buffer);
  char filler = ' ';
  if (flags->zero) {
    filler = '0';
  }
  if (flags->hash) {
    len += 2;
  }
  if (len < flags->width) {
    if (flags->zero) {
      for (int i = flags->width - len, j = 0; j < len; i++, j++) {
        buffer[i] = buffer[j];
      }
      s21_memset(buffer, filler, flags->width - len);
    } else {
      for (int y = 0; y < flags->width - len; y++) {
        if (flags->minus) {
          for (int i = len; i < flags->width; i++) {
            buffer[i] = filler;
          }
        } else {
          for (int i = len + y; i > 0; i--) {
            buffer[i] = buffer[i - 1];
          }
          buffer[y] = filler;
        }
      }
    }
    buffer[flags->width] = '\0';
  }
}

void flag_width_int(char* buffer, flags* flags) {
  int len = s21_strlen(buffer);
  int dif = flags->width - len;
  // printf("%d %d\n", flags->width, len);
  char filler = ' ';
  if (flags->zero) {
    filler = '0';
  }
  if (len < flags->width) {
    for (int y = 0; y < dif; y++) {
      if (flags->minus) {
        for (int i = len; i < flags->width; i++) {
          buffer[i] = filler;
        }
      } else {
        for (int i = len + y; i > 0; i--) {
          buffer[i] = buffer[i - 1];
        }
        buffer[y] = filler;
      }
    }
    buffer[flags->width] = '\0';
  }
}

void flag_width_float(char* buffer, flags* flags) {
  int len = s21_strlen(buffer);
  int dif = flags->width - len;
  for (int y = 0; y < dif; y++) {
    for (int i = len + y; i > 0; i--) {
      buffer[i] = buffer[i - 1];
    }
    buffer[y] = ' ';
  }
}

int flag_precision_for_g(char* temp, flags* flags, int int_len,
                         double long frac_part) {
  int result = 0;
  if (flags->precision != 1) {
    if (int_len == flags->precision) {
      temp[flags->precision] = '\0';
      result = 1;
    }
    if (int_len < flags->precision) {
      flags->precision = flags->precision - int_len;
      char frac[flags->precision];
      int counter;
      int len = 0;

      for (int i = 1; i <= flags->precision; i++) {
        frac_part *= 10;
        counter = (int)frac_part % 10;
        len++;
      }

      frac[0] = '.';
      long long int_part = (long long)frac_part;
      if (int_part > 1000) {
        int_part++;
      }

      for (int i = flags->precision; i > 0; i--) {
        counter = int_part % 10;
        frac[i] = '0' + counter;
        int_part /= 10;
      }
      frac[flags->precision] = '\0';

      temp = s21_strcat(temp, frac);
      result = 1;
    }
  }
  return result;
}

void flag_precision_for_f(char* temp, flags* flags, double long frac_part) {
  if (flags->precision != 0) {
    char frac[flags->precision];
    int counter;
    int len = 0;

    for (int i = 1; i <= flags->precision + 1; i++) {
      frac_part *= 10;
      counter = (int)frac_part % 10;
      len++;
    }

    frac[0] = '.';
    long long int_part = (long long)frac_part;
    if (int_part > 1000000) {
      int_part++;
    }

    for (int i = flags->precision + 1; i > 0; i--) {
      counter = int_part % 10;
      frac[i] = '0' + counter;
      int_part /= 10;
    }

    while (frac[len] == '0') {
      len--;
    }
    frac[len + 1] = '\0';
    if (flags->precision >= len) {
      for (int i = len + 1; i <= flags->precision; i++) {
        frac[i] = '0';
      }
    } else {
      for (int i = flags->precision, done = 0; i >= 0 && !done; i--) {
        if ((frac[i + 1] < 58) && (frac[i + 1] > 52) && frac[i] != '9' &&
            frac[i] != '.') {
          frac[i]++;
          done++;
        } else if ((frac[i + 1] < 58) && (frac[i + 1] > 52)) {
          frac[i] = '0';
        }
      }
    }
    frac[flags->precision + 1] = '\0';
    temp = s21_strcat(temp, frac);
  }
}

void flag_width_scientific(char* buffer, flags* flags) {
  int len = s21_strlen(buffer);
  char filler = ' ';
  if (flags->zero) {
    filler = '0';
  }
  int dif = flags->width - len;
  for (int y = 0; y < dif; y++) {
    for (int i = len + y; i > 0; i--) {
      buffer[i] = buffer[i - 1];
    }
    buffer[y] = filler;
  }
}

void flag_precision_for_o(char* temp, flags* flags) {
  int len = s21_strlen(temp);
  if (flags->precision > len) {
    for (int y = 0; y < flags->precision - len; y++) {
      for (int i = len + y; i > 0; i--) {
        temp[i] = temp[i - 1];
      }
    }
    for (int i = 0; i < flags->precision - len; i++) {
      temp[i] = '0';
    }
    temp[flags->precision] = '\0';
  }
}
