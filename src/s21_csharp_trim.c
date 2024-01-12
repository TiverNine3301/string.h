#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  s21_size_t size = s21_strlen(src);
  char *sr = (char *)malloc(sizeof(char) * size);
  s21_size_t size1 = s21_strlen(sr);
  int start_char = 0;
  int end_char = size - 1;
  for (; s21_strchr(trim_chars, src[start_char]) != s21_NULL; start_char++)
    ;
  for (; s21_strchr(trim_chars, src[end_char]) != s21_NULL; end_char--)
    ;

  s21_memset(sr, 0, size1);
  for (int i = 0; start_char <= end_char; i++) {
    sr[i] = src[start_char++];
  }
  free(sr);
  return sr;
}
