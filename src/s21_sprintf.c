#include "s21_string.h"

int s21_sprintf(char *buf, const char *format, ...) {
  va_list arg;
  *buf = '\0';
  va_start(arg, format);
  while (*format) {
    if (*format == '%') {
      format++;
      struct options opt = {0};
      format = all_flags(&opt, format, &arg);
      s21_strncat(buf, opt.buf, s21_strlen(opt.buf));
    } else
      s21_strncat(buf, format, 1);
    format++;
  }
  return s21_strlen(buf);
}

const char *flags(const char *format, struct options *opt) {
  while (format) {
    if (*format == '-')
      opt->minus = 1;
    else if (*format == '+')
      opt->plus = 1;
    else if (*format == ' ')
      opt->space = 1;
    else if (*format == '#')
      opt->hash = 1;
    else if (*format == '0')
      opt->zero = 1;
    else
      break;
    format++;
  }
  if (opt->plus) opt->space = 0;
  if (opt->minus) opt->zero = 0;
  return format;
}

const char *spec_width(const char *format, int *width, va_list *arg) {
  *width = 0;
  if (*format == '*') {
    *width = va_arg(*arg, int);
    format++;
  }
  while (format) {
    if (*format >= 48 && *format <= 58) {
      *width *= 10;
      *width += *format - 48;
    } else
      break;
    format++;
  }
  return format;
}

const char *all_flags(struct options *opt, const char *format, va_list *arg) {
  format = flags(format, opt);
  format = spec_width(format, &opt->width, arg);
  if (*format == '.') {
    opt->accuracy_in = 1;
    format++;
    format = spec_width(format, &opt->accuracy, arg);
  }
  if (*format == 'l') {
    opt->length_l = 1;
    format++;
  } else if (*format == 'L') {
    opt->length_L = 1;
    format++;
  } else if (*format == 'h') {
    opt->length_h = 1;
    format++;
  }
  opt->specifiers = *format;
  check_specificators(opt, format, arg);
  return format;
}

void check_specificators(struct options *opt, const char *format,
                         va_list *arg) {
  if (opt->specifiers == 'd') {
    long int d = va_arg(*arg, long int);
    spec_d(opt, d);
  }
  if (opt->specifiers == 'c') {
    char c = (char)va_arg(*arg, int);
    spec_c(opt, c);
  }
  if (opt->specifiers == 'f' || opt->specifiers == 'F') {
    long double f = 0.0;
    if (opt->length_L) {
      f = va_arg(*arg, long double);
    } else {
      f = va_arg(*arg, double);
    }
    if (isinf(f) != 0)
      divOnZero(opt, "inf");
    else if (isnan(f) != 0)
      divOnZero(opt, "nan");
    else
      spec_f(opt, f);
  }
  if (opt->specifiers == 'u') {
    unsigned long u = va_arg(*arg, unsigned long);
    spec_u(opt, u);
  }
  if (opt->specifiers == '%') {
    if (*format - 1 != '%') spec_c(opt, '%');
  }
  if (opt->specifiers == 's') {
    char *s = (char *)va_arg(*arg, char *);
    spec_s(opt, s);
  }
  if (opt->specifiers == 'x') {
    unsigned long x = va_arg(*arg, unsigned long);
    spec_x(opt, x);
  }
  if (opt->specifiers == 'X') {
    unsigned long x = va_arg(*arg, unsigned long);
    spec_x(opt, x);
    for (int i = 0; i < (int)s21_strlen(opt->buf); i++) {
      if (opt->buf[i] >= 97 && opt->buf[i] <= 122) opt->buf[i] -= 32;
    }
  }
  if (opt->specifiers == 'o') {
    unsigned long o = va_arg(*arg, unsigned long);
    spec_o(opt, o);
  }
  if (opt->specifiers == 'e' || opt->specifiers == 'E') {
    long double e = 0.0;
    if (opt->length_L) {
      e = va_arg(*arg, long double);
    } else {
      e = va_arg(*arg, double);
    }
    if (isinf(e) != 0)
      divOnZero(opt, "inf");
    else if (isnan(e) != 0)
      divOnZero(opt, "nan");
    else if (e == 0)
      ExpZero(e, opt);
    else
      spec_e(opt, e);
    if (opt->specifiers == 'E') {
      for (int i = 0; i < (int)s21_strlen(opt->buf); i++) {
        if (opt->buf[i] >= 97 && opt->buf[i] <= 122) opt->buf[i] -= 32;
      }
    }
  }
  if (opt->specifiers == 'g' || opt->specifiers == 'G') {
    opt->flag_for_g = 1;
    long double g = 0.0;
    if (opt->length_L) {
      g = va_arg(*arg, long double);
    } else {
      g = va_arg(*arg, double);
    }
    if (isinf(g))
      divOnZero(opt, "inf");
    else if (isnan(g) != 0)
      divOnZero(opt, "nan");
    else if (g == 0)
      ExpZero(g, opt);
    else
      spec_g(opt, g);
    if (opt->specifiers == 'G') {
      for (int i = 0; i < (int)s21_strlen(opt->buf); i++) {
        if (opt->buf[i] >= 97 && opt->buf[i] <= 122) opt->buf[i] -= 32;
      }
    }
  }
  if (opt->specifiers == 'p') {
    void *p = va_arg(*arg, void *);
    spec_p(opt, p);
  }
}
