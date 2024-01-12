#ifndef S21_STRING_H
#define S21_STRING_H

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct options {
  int minus;
  int plus;
  int space;
  int hash;
  int width;
  int zero;
  int accuracy_in;
  int accuracy;
  int length_l;
  int length_L;
  int length_h;
  char specifiers;
  int flag_for_g;
  char buf[10000];
};

typedef unsigned long s21_size_t;

#define s21_NULL ((void *)0)

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
void *s21_memchr(const void *str, int c, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
void s21_my_itoa(int n, char arr[]);
void s21_my_reverse(char arr[]);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

// SPRINTF by cedricho
int s21_sprintf(char *buf, const char *format, ...);
const char *flags(const char *format, struct options *opt);
const char *spec_width(const char *format, int *width, va_list *arg);
const char *all_flags(struct options *opt, const char *format, va_list *arg);
void check_specificators(struct options *opt, const char *format, va_list *arg);
void check_sign(struct options *opt, int check_plus, int min);
void spec_d(struct options *opt, long int d);
void spec_c(struct options *opt, char c);
void spec_s(struct options *opt, char *s);
void spec_f(struct options *opt, long double f);
void spec_u(struct options *opt, unsigned long u);
void spec_x(struct options *opt, unsigned long x);
void spec_o(struct options *opt, unsigned long o);
void spec_e(struct options *opt, long double e);
void spec_g(struct options *opt, double g);
void spec_p(struct options *opt, void *p);
void divOnZero(struct options *opt, char str[3]);
void ExpZero(double e, struct options *opt);
void processArgument(void *arg);
char *s21_convert(unsigned long long num);
int SignAfterPoint(double x);
char *removeTrailingZeros(char *numStr);
double printExponential(double num);
int int_exp(double num);
char *DecToHex(long int dig, char str[], s21_size_t len);
char *DecToOct(long int dig, char str[], s21_size_t len);
char *IntToAnsi(long int dig, char str[], s21_size_t len);
char *DoubleToAnsi(double dig, s21_size_t acc, char str[], s21_size_t len,
                   struct options *opt);
char *reverse(char *str);
void Swap(char *a, char *b);
//
int s21_sscanf(const char *str, const char *sto, ...);
void s21_sscanf_analysis(const char **str2, const int *width,
                         const int *accuracy, const char *format,
                         const int *specifier);
void s21_analysis_width_accuracy(const char **strc, const int *widthc,
                                 const int *accuracyc);
void s21_analysis_format(const char **str, const char *format);
void s21_analysis_specifier(const char **str, const char *format,
                            const int *specifier);

void s21_record(const void **out, const void *in, const int bite);

void s21_nouns_int_main_function(const void *outt, const int *width,
                                 const char *format, const int *specifier,
                                 const char **book, const int flag);
void s21_int_main_function(const void *outt, const int *width,
                           const char *format, const int *specifier,
                           const char **book, const int flag,
                           const int *n_check);
void s21_double_main_function(const void *outt, const int *width,
                              const int *accuracy, const char *format,
                              const int *specifier, const char **book,
                              const int flag);

long double s21_double(const int *width, const int *accuracy, const char **str,
                       int sist);
long long int s21_int(const int *width, const char **str, int sist);
void s21_v_drob(const double *end, int sist);
void s21_char_main_function(const void *outt, const int *width,
                            const char *format, const int *specifier,
                            const char **book, const int flag);
void s21_indicator_main_function(const void *outt, const char *format,
                                 const int *specifier, const char *str,
                                 const char **book, const int *width,
                                 const int flag);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif
