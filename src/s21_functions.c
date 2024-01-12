#include "s21_string.h"

void check_sign(struct options *opt, int check_plus, int min) {
  if (opt->zero == 1) {
    if (min == 1) s21_strncat(opt->buf, "-", 1);
    for (int i = 0; i < check_plus; i++) s21_strncat(opt->buf, "0", 1);
  } else if (opt->minus) {
    for (int i = 0; i < check_plus; i++) s21_strncat(opt->buf, " ", 1);
  } else if (!opt->minus) {
    for (int i = 0; i < check_plus; i++) s21_strncat(opt->buf, " ", 1);
    if (min == 1) s21_strncat(opt->buf, "-", 1);
  }
}

int int_exp(double num) {
  int exp = 0;
  double mantissa = num;
  while (mantissa >= 10.0 || mantissa <= -10.0) {
    mantissa /= 10.0;
    exp++;
  }
  while (mantissa < 1 && mantissa > -1.0) {
    mantissa *= 10;
    exp++;
  }
  return exp;
}

double printExponential(double num) {
  double mantissa = num;
  while (mantissa >= 10.0 || mantissa <= -10.0) {
    mantissa /= 10.0;
  }
  while (mantissa < 1.0 && mantissa > -1.0) {
    mantissa *= 10.0;
  }
  return mantissa;
}
void Swap(char *a, char *b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

char *reverse(char *str) {
  char *begin = str;
  char *end = str;
  for (; *end; ++end) {
    ;
  }
  for (--end; begin < end; ++begin, --end) {
    Swap(begin, end);
  }
  return str;
}

int SignAfterPoint(double x) {
  int y = (int)x;
  x = x - y;
  double p = 1;
  int i = 0;
  if (x != 0) {
    while (x < p) {
      p /= 10;
      i++;
    }
  }
  return i;
}
char *DecToOct(long int dig, char str[], s21_size_t len) {
  int i = 0;
  int x = 0;
  if (dig < 0) dig *= -1;
  while (dig && (i < (int)len - 1)) {
    x = dig % 8;
    str[i++] = x + 48;
    dig /= 8;
  }
  if ((i == 0) && (i < (int)len)) {
    str[i++] = '0';
  }
  str[i] = '\0';
  reverse(str);
  return str;
}
char *DecToHex(long int dig, char str[], s21_size_t len) {
  int i = 0;
  int x = 0;
  if (dig < 0) dig *= -1;
  while (dig && (i < (int)len - 1)) {
    x = dig % 16;
    str[i++] = x < 10 ? x + '0' : x - 10 + 'a';
    dig /= 16;
  }
  if ((i == 0) && (i < (int)len)) {
    str[i++] = '0';
  }
  str[i] = '\0';
  reverse(str);
  return str;
}
char *IntToAnsi(long int dig, char str[], s21_size_t len) {
  int i = 0;
  while (dig && (i < (int)len - 1)) {
    str[i++] = (dig % 10) + '0';
    dig /= 10;
  }
  if ((i == 0) && (i < (int)len)) {
    str[i++] = '0';
  }
  str[i] = '\0';
  reverse(str);
  return str;
}

char *DoubleToAnsi(double dig, s21_size_t acc, char str[], s21_size_t len,
                   struct options *opt) {
  int hi = (int)dig;
  double lo = 0;
  char lo_c[10000] = {0};
  double ost = dig - hi;
  if (opt->accuracy_in == 1 && opt->accuracy == 0) {
    if (ost > 0.4) {
      hi = hi + 1;
    }
  }
  double l = ost * pow(10, acc + 1);
  if ((int)l % 10 > 4) {
    lo = ost * pow(10.0, acc) + 1;
  } else
    lo = round(ost * pow(10, acc));
  int lo_count = s21_strlen(IntToAnsi(lo, lo_c, sizeof(lo_c)));
  IntToAnsi(hi, str, len);

  if (opt->accuracy != 0 || opt->hash == 1) s21_strncat(str, ".", 1);
  if (opt->accuracy != 0) {
    for (int i = 0; i < (int)(acc - lo_count); i++) s21_strncat(str, "0", 1);
    s21_strncat(str, lo_c, 10000);
  }
  return str;
}
char *removeTrailingZeros(char *numStr) {
  int len = s21_strlen(numStr);
  int dotPos = -1;
  for (int i = 0; i < len; i++) {
    if (numStr[i] == '.') {
      dotPos = i;
      break;
    }
  }
  for (int i = len - 1; i > dotPos; i--) {
    if (numStr[i] == '0') {
      numStr[i] = '\0';
    } else {
      break;
    }
  }
  if (numStr[len - 1] == '.') {
    numStr[len - 1] = '\0';
  }
  return numStr;
}

char *s21_convert(unsigned long long num) {
  static char buffer[50] = {0};
  char *ptr = '\0';
  char d[10000] = {0};

  ptr = &buffer[49];
  while (num != 0) {
    s21_sprintf(d, "%x", num % 16);
    *--ptr = *d;
    num /= 16;
  }
  return (ptr);
}

void divOnZero(struct options *opt, char str[3]) {
  int check_plus = 0;
  int min = 0;
  if (opt->plus)
    check_plus = opt->width - 3 - 1;
  else
    check_plus = opt->width - 3;
  if (!opt->plus && opt->space && opt->width - 3 <= 0)
    s21_strncat(opt->buf, " ", 1);
  if (opt->minus) {
    opt->zero = 0;
    if (opt->plus) s21_strncat(opt->buf, "+", 1);
    s21_strncat(opt->buf, str, 3);
    if (3 < opt->width) check_sign(opt, check_plus, min);
  } else {
    if (3 < opt->width) check_sign(opt, check_plus, min);
    if (opt->plus) s21_strncat(opt->buf, "+", 1);
    s21_strncat(opt->buf, str, 3);
  }
}

void ExpZero(double e, struct options *opt) {
  if (!opt->accuracy) opt->accuracy = 6;
  int min = 0;
  if (e < 0.0) {
    e *= -1;
    min = 1;
    opt->space = 0;
    opt->width -= 1;
  }
  double mantissa = e;
  int exp = 0;
  char e_str[10000] = {0};
  int length_e =
      s21_strlen(DoubleToAnsi(e, opt->accuracy, e_str, sizeof(e_str), opt));
  int check_plus = 0;
  if (opt->plus && min == 0)
    check_plus = opt->width - length_e - 5;
  else
    check_plus = opt->width - length_e - 4;
  if (e >= 0 && !opt->plus && opt->space && opt->width - length_e <= 0)
    s21_strncat(opt->buf, " ", 1);
  if (opt->minus == 0)
    if (length_e < opt->width) check_sign(opt, check_plus, min);
  if (opt->plus && e >= 0) s21_strncat(opt->buf, "+", 1);
  if (min == 1 && opt->minus) s21_strncat(opt->buf, "-", 1);
  if (opt->flag_for_g) {
    s21_strncat(
        opt->buf,
        DoubleToAnsi(mantissa, opt->accuracy, e_str, sizeof(e_str), opt), 17);
    s21_strncpy(opt->buf, removeTrailingZeros(opt->buf), 10000);
    if (opt->buf[s21_strlen(opt->buf) - 1] == '.')
      opt->buf[s21_strlen(opt->buf) - 1] = '\0';
  } else {
    s21_strncat(
        opt->buf,
        DoubleToAnsi(mantissa, opt->accuracy, e_str, sizeof(e_str), opt), 17);
  }
  s21_strncat(opt->buf, "e", 1);
  if (e >= 0)
    s21_strncat(opt->buf, "+", 1);
  else
    s21_strncat(opt->buf, "-", 1);
  exp = abs(exp);
  if (exp < 10) s21_strncat(opt->buf, "0", 1);
  s21_strncat(opt->buf, IntToAnsi(exp, e_str, sizeof(e_str)), 2);
  if (opt->minus == 1)
    if (length_e < opt->width) check_sign(opt, check_plus, min);
}