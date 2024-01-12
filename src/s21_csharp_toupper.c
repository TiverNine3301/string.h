#include "s21_string.h"

void *s21_to_upper(const char *str) {
  s21_size_t i = 0;
  char *st = malloc(sizeof(char) * (s21_strlen(str) + 1));
  st = s21_strncpy(st, str, s21_strlen(str) + 1);

  while (st[i]) {
    if (st[i] >= 'a' && st[i] <= 'z') {
      st[i] -= 32;
    }
    i++;
  }
  free(st);
  return st;
}
