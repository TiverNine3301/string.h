#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t size_all = s21_strlen(src) + s21_strlen(str) + 1;
  char *str_res = malloc(sizeof(char) * size_all);

  s21_size_t i = 0;
  s21_size_t j = 0;
  s21_size_t k = 0;

  if (s21_strlen(src) <= start_index) {
    str_res = s21_NULL;
  } else {
    for (; i < start_index; i++) {
      str_res[k] = src[i];
      k++;
    }

    for (; j < s21_strlen(str); j++) {
      str_res[k] = str[j];
      k++;
    }

    for (; i < s21_strlen(src); i++) {
      str_res[k] = src[i];
      k++;
    }
    str_res[k] = '\0';
  }

  free(str_res);
  return str_res;
}
