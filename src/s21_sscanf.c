#include "s21_string.h"

int s21_sscanf(const char *str, const char *sto, ...) {
  int n = 0;
  va_list app;
  va_start(app, sto);
  char **book = (char **)&str;
  char *lo = (char *)str;
  int width = 0;
  int flag = 0;
  int n_check = 1;
  int accuracy = 0;
  char format = 0;
  int specifier = 0;
  char *v = (char *)sto;
  while (*v) {
    if (*v == '%') {
      v++;
      if (*v == '*') {
        flag = 1;
        v++;
      }
      s21_sscanf_analysis((const char **)&v, (const int *)&width,
                          (const int *)&accuracy, (const char *)&format,
                          (const int *)&specifier);
      void *ssa = s21_NULL;
      if ((specifier != -1) && (specifier != 10)) {
        ssa = va_arg(app, void *);
      }
      if ((specifier <= 3) && (specifier > 0)) {
        s21_nouns_int_main_function(
            ssa, (const int *)&width, (const char *)&format,
            (const int *)&specifier, (const char **)book, (const int)flag);
      }
      if ((specifier <= 5) && (specifier > 3)) {
        s21_int_main_function(ssa, (const int *)&width, (const char *)&format,
                              (const int *)&specifier, (const char **)book,
                              (const int)flag, (const int *)&n_check);
      }
      if ((specifier <= 7) && (specifier > 5)) {
        s21_double_main_function(ssa, (const int *)&width,
                                 (const int *)&accuracy, (const char *)&format,
                                 (const int *)&specifier, (const char **)book,
                                 (const int)flag);
      }
      if ((specifier <= 10) && (specifier > 7)) {
        s21_char_main_function(ssa, (const int *)&width, (const char *)&format,
                               (const int *)&specifier, (const char **)book,
                               (const int)flag);
      }
      if ((specifier <= 12) && (specifier > 10)) {
        s21_indicator_main_function(ssa, (const char *)&format,
                                    (const int *)&specifier, (const char *)lo,
                                    (const char **)book, (const int *)&width,
                                    (const int)flag);
      }
      if ((specifier != -1) && (specifier != 12) && (specifier != 10) &&
          n_check == 1) {
        n++;
      }
    }
    if ((*v != '%') && (*v)) {
      while ((**book == *v) && (*v != '%')) {
        (*book)++;
        v++;
      }
    }
    if ((*v != '%') && (*v)) {
      v++;
    }
  }
  va_end(app);
  return n;
}

void s21_sscanf_analysis(const char **str2c, const int *widthc,
                         const int *accuracyc, const char *formatc,
                         const int *specifierc) {
  char **str2 = (char **)str2c;
  int *width = (int *)widthc;
  int *accuracy = (int *)accuracyc;
  char *format = (char *)formatc;
  int *specifier = (int *)specifierc;
  s21_analysis_width_accuracy((const char **)str2, (const int *)width,
                              (const int *)accuracy);
  s21_analysis_format((const char **)str2, (const char *)format);
  s21_analysis_specifier((const char **)str2, (const char *)format,
                         (const int *)specifier);
  return;
}

void s21_analysis_width_accuracy(const char **strc, const int *widthc,
                                 const int *accuracyc) {
  char **str = (char **)strc;
  int *width = (int *)widthc;
  int *accuracy = (int *)accuracyc;
  *width = 0;
  *accuracy = 0;
  char *c = *str;
  while (*c >= 48 && *c <= 58) {
    *width *= 10;
    *width += *c - 48;
    c++;
  }
  *str = c;
  return;
}

void s21_analysis_format(const char **strc, const char *formatc) {
  char **str = (char **)strc;
  char *format = (char *)formatc;
  *format = 'b';
  char *c = *str;
  switch (*c) {
    case 'h':
      *format = 'h';
      break;
    case 'l':
      *format = 'l';
      break;
    case 'L':
      *format = 'L';
      break;
    default:
      break;
  }
  if (*format != 'b') {
    c++;
    *str = c;
  }
  return;
}

void s21_analysis_specifier(const char **strc, const char *formatc,
                            const int *specifierc) {
  char **str = (char **)strc;
  char *format = (char *)formatc;
  int *specifier = (int *)specifierc;
  char *c = *str;
  switch (*c) {
    case 'o':
      *specifier = 1;
      break;  //   unsigned int для 1-8
    case 'u':
      *specifier = 2;
      break;  //   unsigned int для 1-10
    case 'x':
      *specifier = 3;
      break;  //   int unsigned для 1-16
    case 'd':
      *specifier = 4;
      break;  //   int для 1-10
    case 'i':
      *specifier = 5;
      break;  //   int для 1-16 для 1-8 для 1-10
    case 'f':
      *specifier = 6;
      break;  //   float для 1-10
    case 'e':
      *specifier = 6;
      break;  //   float для 1-10
    case 'g':
      *specifier = 6;
      break;  //   float для 1-10
    case 'a':
      *specifier = 7;
      break;  //   float для 1-16
    case 'c':
      *specifier = 8;
      break;  //   char
    case 's':
      *specifier = 9;
      break;  //   char для строки
    case '%':
      *specifier = 10;
      break;  //  char для символа %
    case 'p':
      *specifier = 11;
      break;  //  void** для хз чего
    case 'n':
      *specifier = 12;
      break;  //  int* для кол-во считанных элементов
    case 'F':
      *specifier = 6;
      break;
    case 'E':
      *specifier = 6;
      break;
    case 'G':
      *specifier = 6;
      break;
    case 'X':
      *specifier = 3;
      *format = 'l';
      break;
    default:
      *specifier = -1;
      break;
  }
  c++;
  *str = c;
  return;
}

void s21_checking_sign(const int *signc, const char **cc) {
  char **c = (char **)cc;
  int *sign = (int *)signc;
  if (**c == '-') {
    *sign = *sign * -1;
    (*c)++;
  }
  if (**c == '+') {
    (*c)++;
  }
  return;
}

void s21_line_8_un_int(const unsigned long long int *outc, const char **cc,
                       const int *massc) {
  unsigned long long int *out = (unsigned long long int *)outc;
  char **c = (char **)cc;
  int *mass = (int *)massc;
  for (int i = 0;
       (((55 >= **c) && (**c >= 48)) && ((i < *mass - 1) || (*mass == 0)));
       i++, (*c)++) {
    *out = *out * 8 + **c - 48;
  }
  return;
}

void s21_line_10_un_int(const unsigned long long int *outc, const char **cc,
                        const int *massc) {
  unsigned long long int *out = (unsigned long long int *)outc;
  char **c = (char **)cc;
  int *mass = (int *)massc;
  if (**c >= 48 && **c <= 57) {
    for (int i = 0;
         (((57 >= **c) && (**c >= 48)) && ((i < *mass) || (*mass == 0)));
         i++, (*c)++) {
      *out = *out * 10 + **c - 48;
    }
  }
  return;
}

void s21_line_16_un_int(const unsigned long long int *outc, const char **cc,
                        const int *massc) {
  unsigned long long int *out = (unsigned long long int *)outc;
  char **c = (char **)cc;
  int *mass = (int *)massc;
  for (int i = 0;
       ((((57 >= **c) && (**c >= 48)) || ((70 >= **c) && (**c >= 65)) ||
         ((102 >= **c) && (**c >= 97))) &&
        ((i < *mass) || (*mass == 0)));
       i++, (*c)++) {
    if ((57 >= **c) && (**c >= 48)) {
      *out = *out * 16 + **c - 48;
    } else {
      if ((70 >= **c) && (**c >= 65)) {
        *out = *out * 16 + **c - 55;
      } else {
        *out = *out * 16 + **c - 87;
      }
    }
  }
  return;
}

void s21_record(const void **outc, const void *inc, const int bite) {
  void **out = (void **)outc;
  void *in = (void *)inc;
  s21_memcpy(*out, in, bite);
  char *c = (char *)*out;
  c = c + bite;
  *out = (void *)c;
  return;
}

void s21_nouns_int_main_function(const void *outtc, const int *widthc,
                                 const char *formatc, const int *specifierc,
                                 const char **bookc, const int flag) {
  void *out = (void *)outtc;
  int *width = (int *)widthc;
  char *format = (char *)formatc;
  int *specifier = (int *)specifierc;
  char **book = (char **)bookc;
  int minus = 0;
  long long int v = 0;
  while (**book == ' ') {
    (*book)++;
  }
  if (*specifier == 1) {
    v = s21_int((const int *)width, (const char **)book, 8);
  }
  if (*specifier == 2) {
    v = s21_int((const int *)width, (const char **)book, 10);
  }
  if (*specifier == 3) {
    if (**book == '-') {
      (*book)++;
      minus = 1;
    }
    if (**book == '0') (*book)++;
    if (**book == 'x' || **book == 'X') (*book)++;
    while ((**book >= 48 && **book <= 57) || (**book >= 65 && **book <= 70) ||
           (**book >= 97 && **book <= 102)) {
      v = s21_int((const int *)width, (const char **)book, 16);
    }
    if (minus == 1) v = -v;
  }
  if (flag == 0) {
    if (*format == 'b') {
      int x = v;
      s21_record((const void **)&out, (const void *)&x, sizeof(int));
    }
    if (*format == 'h') {
      short int x = v;
      s21_record((const void **)&out, (const void *)&x, sizeof(short int));
    }
    if (*format == 'l') {
      long int x = v;
      s21_record((const void **)&out, (const void *)&x, sizeof(long int));
    }
  }
  return;
}

void s21_int_main_function(const void *outtc, const int *widthc,
                           const char *formatc, const int *specifierc,
                           const char **bookc, const int flag,
                           const int *n_check) {
  void *out = (void *)outtc;
  int *width = (int *)widthc;
  char *format = (char *)formatc;
  int *specifier = (int *)specifierc;
  char **book = (char **)bookc;
  int *n = (int *)n_check;
  int minus = 0;
  long long int v = 0;
  while (**book == ' ') {
    (*book)++;
  }
  if ((**book >= 48 && **book <= 57) || **book == '-') {
    if (*specifier == 4) {
      v = s21_int((const int *)width, (const char **)book, 10);
    }
    if (*specifier == 5) {
      if (**book == '-') {
        (*book)++;
        minus = 1;
      }
      if (**book == '0') {
        (*book)++;
        if ((**book == 'X') || (**book == 'x')) {
          (*book)++;
          while ((**book >= 48 && **book <= 57) ||
                 (**book >= 65 && **book <= 70) ||
                 (**book >= 97 && **book <= 102)) {
            v = s21_int((const int *)width, (const char **)book, 16);
          }
        } else {
          v = s21_int((const int *)width, (const char **)book, 8);
        }
      } else {
        v = s21_int((const int *)width, (const char **)book, 10);
      }
      if (minus == 1) v = -v;
    }
    if (flag == 0) {
      if (*format == 'b') {
        int x = v;
        s21_record((const void **)&out, (const void *)&x, sizeof(int));
      }
      if (*format == 'h') {
        short int x = v;
        s21_record((const void **)&out, (const void *)&x, sizeof(short int));
      }
      if (*format == 'l') {
        long int x = v;
        s21_record((const void **)&out, (const void *)&x, sizeof(long int));
      }
    }
  } else
    *n = 0;
  return;
}

void s21_double_main_function(const void *outtc, const int *widthc,
                              const int *accuracyc, const char *formatc,
                              const int *specifierc, const char **bookc,
                              const int flag) {
  void *out = (void *)outtc;
  int *width = (int *)widthc;
  char *format = (char *)formatc;
  int *specifier = (int *)specifierc;
  char **book = (char **)bookc;
  int min = 0;
  int exp = 0;
  int *accuracy = (int *)accuracyc;

  long double v = 0;
  while (**book == ' ') {
    (*book)++;
  }
  if (*specifier == 6) {
    v = s21_double((const int *)width, (const int *)accuracy,
                   (const char **)book, 10);
    if (**book == 'e' || (**book == 'E')) {
      (*book)++;
      if ((**book) == '-')
        min = 1;
      else {
        while (**book >= 48 && **book <= 57) {
          exp = s21_int((const int *)width, (const char **)book, 10);
        }
      }
      if (min == 0)
        v = v * pow(10, exp);
      else
        v = v * pow(0.1, exp);
    }
  }
  if (*specifier == 7) {
    int sist = 10;
    if (**book == '0') {
      (*book)++;
      if ((**book == 'X') || (**book == 'x')) {
        if (**book == 'X') {
          sist = 16;
        } else {
          sist = 8;
        }
        (*book)++;
      } else {
        (*book)--;
      }
    }
    v = s21_double((const int *)width, (const int *)accuracy,
                   (const char **)book, sist);
  }
  if (flag == 0) {
    if (*format == 'b') {
      float x = v;
      s21_record((const void **)&out, (const void *)&x, sizeof(float));
    }
    if (*format == 'l') {
      double x = v;
      s21_record((const void **)&out, (const void *)&x, sizeof(double));
    }
    if (*format == 'L') {
      long double x = v;
      s21_record((const void **)&out, (const void *)&x, sizeof(long double));
    }
  }
  return;
}

long long int s21_int(const int *widthc, const char **strc, const int sist) {
  int *width = (int *)widthc;
  char **str = (char **)strc;
  unsigned long long int out = 0;
  int sign = 1;
  s21_checking_sign((const int *)&sign, (const char **)str);
  switch (sist) {
    case 8:
      s21_line_8_un_int((const unsigned long long int *)&out,
                        (const char **)str, (const int *)width);
      break;
    case 10:
      s21_line_10_un_int((const unsigned long long int *)&out,
                         (const char **)str, (const int *)width);
      break;
    case 16:
      s21_line_16_un_int((const unsigned long long int *)&out,
                         (const char **)str, (const int *)width);
      break;
  }
  return ((long long int)out) * sign;
}

long double s21_double(const int *widthc, const int *accuracyc,
                       const char **strc, int sist) {
  int *width = (int *)widthc;
  char **str = (char **)strc;
  int *accuracy = (int *)accuracyc;
  unsigned long long int out1 = 0;
  unsigned long long int out2 = 0;
  int sign = 1;
  s21_checking_sign((const int *)&sign, (const char **)str);
  switch (sist) {
    case 8:
      s21_line_8_un_int((const unsigned long long int *)&out1,
                        (const char **)str, (const int *)width);
      break;
    case 10:
      s21_line_10_un_int((const unsigned long long int *)&out1,
                         (const char **)str, (const int *)width);
      break;
    case 16:
      s21_line_16_un_int((const unsigned long long int *)&out1,
                         (const char **)str, (const int *)width);
      break;
  }
  if ('.' == **str) {
    (*str)++;
    switch (sist) {
      case 8:
        s21_line_8_un_int((const unsigned long long int *)&out2,
                          (const char **)str, (const int *)accuracy);
        break;
      case 10:
        s21_line_10_un_int((const unsigned long long int *)&out2,
                           (const char **)str, (const int *)accuracy);
        break;
      case 16:
        s21_line_16_un_int((const unsigned long long int *)&out2,
                           (const char **)str, (const int *)accuracy);
        break;
    }
  }
  double end = out2;
  s21_v_drob((const double *)&end, sist);
  return (((long double)out1) + end) * sign;
}

void s21_v_drob(const double *endc, int sist) {
  double *end = (double *)endc;
  while (*end >= 1) {
    *end = *end / sist;
  }
  return;
}

void s21_char_main_function(const void *outtc, const int *widthc,
                            const char *formatc, const int *specifierc,
                            const char **bookc, const int flag) {
  void *out = (void *)outtc;
  int *width = (int *)widthc;
  char *format = (char *)formatc;
  int *specifier = (int *)specifierc;
  char **book = (char **)bookc;
  if (*specifier == 8) {
    if (*width == 0) {
      (*width)++;
    }
    for (int i = 0; i < *width; i++) {
      if (*format == 'b') {
        char x = (char)**book;
        s21_record((const void **)&out, (const void *)&x, sizeof(char));
        (*book)++;
      }
      if (*format == 'l') {
        wchar_t x = (wchar_t) * *book;
        if (flag == 0) {
          s21_record((const void **)&out, (const void *)&x, sizeof(wchar_t));
        }
        (*book)++;
      }
    }
  }
  if (*specifier == 9) {
    int i = 0;
    while (**book == ' ') {
      (*book)++;
    }
    while ((**book != ' ') && ((*width == 0) || (i < *width))) {
      if (*format == 'b') {
        char x = (char)**book;
        s21_record((const void **)&out, (const void *)&x, sizeof(char));
        (*book)++;
      }
      if (*format == 'l') {
        wchar_t x = (wchar_t) * *book;
        s21_record((const void **)&out, (const void *)&x, sizeof(wchar_t));
        (*book)++;
      }
      i++;
    }
    void *x = ((void *)0);
    if (flag == 0) {
      s21_record((const void **)&out, (const void *)&x, sizeof(void *));
    }
  }
  if (*specifier == 10) {
    if (*width == 0) {
      (*width)++;
    }
    for (int i = 0; i < *width; i++) {
      if ((char)**book == '%') {
        (*book)++;
      }
    }
  }
  return;
}

void s21_indicator_main_function(const void *outtc, const char *formatc,
                                 const int *specifierc, const char *strc,
                                 const char **bookc, const int *widthc,
                                 const int flag) {
  void *out = (void *)outtc;
  int *width = (int *)widthc;
  char *format = (char *)formatc;
  int *specifier = (int *)specifierc;
  char **book = (char **)bookc;
  char *stk = (char *)strc;
  if (*specifier == 11) {
    long long v = 0;
    if (**book == '0') {
      (*book)++;
      if (**book == 'x') {
        (*book)++;
      }
    }
    v = s21_int((const int *)width, (const char **)book, 16);
    void *x = (void *)v;
    if (flag == 0) {
      s21_record((const void **)&out, (const void *)&x, sizeof(void *));
    }
  }
  if (*specifier == 12) {
    long long v = 0;
    while (stk != *book) {
      stk++;
      v++;
    }
    if (flag == 0) {
      if (*format == 'b') {
        int x = (int)v;
        s21_record((const void **)&out, (const void *)&x, sizeof(int));
      }
      if (*format == 'h') {
        short int x = (short int)v;
        s21_record((const void **)&out, (const void *)&x, sizeof(short int));
      }
      if (*format == 'l') {
        long int x = (long int)v;
        s21_record((const void **)&out, (const void *)&x, sizeof(long int));
      }
    }
  }
  return;
}