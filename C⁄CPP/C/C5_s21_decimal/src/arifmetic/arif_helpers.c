#include "../s21_decimal.h"

int big_to_normal(s21_big_decimal *source, s21_decimal *result) {
  clear_bits(result);
  int res = OK;
  int scale = get_scale_big(source);
  int pos = last_bit_big(*source);

  unsigned long long remainder = 0;
  s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0}};

  while (((pos > 95) && (scale > 0)) || (scale > 28)) {
    remainder = remainder * 10 + truncate(*source, source, 1);
    pos = last_bit_big(*source);
    scale--;
  }

  if (((remainder % 10) > 5) ||
      (((remainder % 10) == 5) && ((remainder / 10) > 0))) {
    res = bit_addition(*source, one, source);
  } else if (((remainder % 10) == 5) && ((source->bits[0] % 2) == 1)) {
    res = bit_addition(*source, one, source);
  }

  pos = last_bit_big(*source);
  if ((pos > 95) && (scale == 0)) {
    res = INF;
  }

  if (!res) {
    int i = 95;
    if (pos <= 95) {
      i = pos;
    }
    for (; (i >= 0); i--, pos--) {
      int bit = get_bit_big(source, pos);
      set_bit(result, i, bit);
    }
    result->bits[3] = source->bits[6];
    set_scale(result, scale);
  }
  return res;
}

unsigned long long truncate(s21_big_decimal value, s21_big_decimal *result,
                            int scale) {
  unsigned long long remainder = 0;
  while (scale--) {
    for (int i = 5; i >= 0; i--) {
      unsigned long long temp;
      temp = (remainder << 32) | value.bits[i];
      value.bits[i] = temp / 10;
      remainder = temp % 10;
    }
  }
  *result = value;
  return remainder;
}

int bit_addition(s21_big_decimal value1, s21_big_decimal value2,
                 s21_big_decimal *res) {
  int return_val = OK;
  int buffer = 0;
  s21_big_decimal buf = {0};

  for (int i = 0; i < 192; i++) {
    int current_bit1 = get_bit_big(&value1, i);
    int current_bit2 = get_bit_big(&value2, i);

    if (!current_bit1 && !current_bit2) {
      if (buffer) {
        set_bit_big(&buf, i, 1);
        buffer = 0;
      } else {
        set_bit_big(&buf, i, 0);
      }
    } else if (current_bit1 != current_bit2) {
      if (buffer) {
        set_bit_big(&buf, i, 0);
        buffer = 1;
      } else {
        set_bit_big(&buf, i, 1);
      }
    } else {
      if (buffer) {
        set_bit_big(&buf, i, 1);
        buffer = 1;
      } else {
        set_bit_big(&buf, i, 0);
        buffer = 1;
      }
    }
    if (i == 191 && buffer == 1) return_val = INF;
  }

  *res = buf;

  return return_val;
}

int bit_substraction(s21_big_decimal value1, s21_big_decimal value2,
                     s21_big_decimal *res) {
  int return_val = OK;
  int buffer = 0;

  s21_big_decimal buf = {{0, 0, 0, 0, 0, 0, 0}};

  for (int i = 0; i < 192; i++) {
    int current_bit1 = get_bit_big(&value1, i);
    int current_bit2 = get_bit_big(&value2, i);

    if (!current_bit1 && !current_bit2) {
      if (buffer) {
        buffer = 1;
        set_bit_big(&buf, i, 1);
      } else {
        set_bit_big(&buf, i, 0);
      }
    } else if (current_bit1 && !current_bit2) {
      if (buffer) {
        buffer = 0;
        set_bit_big(&buf, i, 0);
      } else {
        set_bit_big(&buf, i, 1);
      }
    } else if (!current_bit1 && current_bit2) {
      if (buffer) {
        buffer = 1;
        set_bit_big(&buf, i, 0);
      } else {
        buffer = 1;
        set_bit_big(&buf, i, 1);
      }
    } else if (current_bit1 && current_bit2) {
      if (buffer) {
        buffer = 1;
        set_bit_big(&buf, i, 1);
      } else {
        set_bit_big(&buf, i, 0);
      }
    }
  }

  if (buffer) {
    return_val = NEGATIVE_INF;
  } else {
    *res = buf;
  }
  return return_val;
}

int get_mantissa(s21_decimal value) {
  int exist = false;
  int scale = get_scale(&value);
  set_scale(&value, 0);
  while (scale--) {
    unsigned long remainder = 0;
    for (int i = 2; i >= 0; i--) {
      unsigned long temp;
      temp = (remainder << 32) | value.bits[i];
      value.bits[i] = temp / 10;
      remainder = temp % 10;
      if (i == 0 && remainder > 0) {
        exist = true;
      }
    }
  }
  return exist;
}