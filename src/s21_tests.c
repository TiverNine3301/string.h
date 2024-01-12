#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(s21_sprintf_f_test) {
  char str[80];
  char str_orig[80];

  double b = 1;
  int res_1 = s21_sprintf(str, "%.f", b);
  int res_1_orig = sprintf(str_orig, "%.f", b);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  double b_2 = 0.00000002345;
  int res_2 = s21_sprintf(str, "%+-10.3f", b_2);
  int res_2_orig = sprintf(str_orig, "%+-10.3f", b_2);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  long double b_3 = -23.087654;
  int res_3 = s21_sprintf(str, "%20.10Lf", b_3);
  int res_3_orig = sprintf(str_orig, "%20.10Lf", b_3);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);
  double b_4 = 0;
  int res_4 = s21_sprintf(str, "%0+.15F", b_4);
  int res_4_orig = sprintf(str_orig, "%0+.15F", b_4);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  long double b_5 = 0;
  int res_5 = s21_sprintf(str, "%#.0Lf", b_5);
  int res_5_orig = sprintf(str_orig, "%#.0Lf", b_5);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  double b_6 = 1.0 / 0.0;

  int res_6 = s21_sprintf(str, "%#10.0f", b_6);
  int res_6_orig = sprintf(str_orig, "%#10.0f", b_6);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  double b_8 = 1;
  int res_8 = s21_sprintf(str, "%f", b_8);
  int res_8_orig = sprintf(str_orig, "%f", b_8);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  double b_9 = 0.00345;
  int res_9 = s21_sprintf(str, "%f", b_9);
  int res_9_orig = sprintf(str_orig, "%f", b_9);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  double b_10 = 0.00345;
  int res_10 = s21_sprintf(str, "%f", b_10);
  int res_10_orig = sprintf(str_orig, "%f", b_10);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_g_test) {
  char str[80];
  char str_orig[80];

  double b_1 = -22.25600;
  int res_1 = s21_sprintf(str, "%+-10.3G", b_1);
  int res_1_orig = sprintf(str_orig, "%+-10.3G", b_1);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_prc_test) {
  char str[80];
  char str_orig[80];

  int res_1 = s21_sprintf(str, "%%");
  int res_1_orig = sprintf(str_orig, "%%");
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%10%");

  ck_assert_int_eq(res_2, 10);
  ck_assert_str_eq(str, "         %");

  int a_prc = 14;
  int res_3 = s21_sprintf(str, "hhhh%0*%", a_prc);

  ck_assert_int_eq(res_3, 18);
  ck_assert_str_eq(str, "hhhh0000000000000%");

  int width_prc = 30;
  int res_4 = s21_sprintf(str, "%-*%12345", width_prc);

  ck_assert_int_eq(res_4, 35);
  ck_assert_str_eq(str, "%                             12345");

  int res_5 = s21_sprintf(str, "abc%%defg");
  int res_5_orig = sprintf(str_orig, "abc%%defg");

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_test) {
  char str[80];
  char str_origin[80];
  const char *format_str1 = "Hello";
  char c = 'X';
  char d = 'Y';
  int result1 = s21_sprintf(str, format_str1, c);
  int result_origin1 = sprintf(str_origin, format_str1, c);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(str, str_origin);

  const char *format_str2 = "Hello, %c %c";
  int result2 = s21_sprintf(str, format_str2, c, d);
  int result_origin2 = sprintf(str_origin, format_str2, c, d);
  ck_assert_int_eq(result2, result_origin2);
  ck_assert_str_eq(str, str_origin);

  char *s1 = "world!";
  char *s2 = "Hello world!";
  const char *format_str3 = "Hello, %10s %10.15s";
  int result3 = s21_sprintf(str, format_str3, s1, s2);
  int result_origin3 = sprintf(str_origin, format_str3, s1, s2);
  ck_assert_int_eq(result3, result_origin3);
  ck_assert_str_eq(str, str_origin);
}
END_TEST

START_TEST(s21_sprintf_e_test) {
  char str[80];
  char str_origin[80];
  const char *format_str1 = "% 10.12LE yo";
  long double mantissa1 = 0.0000003044058697058435;
  int result1 = s21_sprintf(str, format_str1, mantissa1);
  int result_origin1 = sprintf(str_origin, format_str1, mantissa1);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(str, str_origin);

  const char *format_str2 = "%-20.7e yo";
  double mantissa2 = -4044050;
  int result2 = s21_sprintf(str, format_str2, mantissa2);
  int result_origin2 = sprintf(str_origin, format_str2, mantissa2);
  ck_assert_int_eq(result2, result_origin2);
  ck_assert_str_eq(str, str_origin);

  const char *format_str3 = "%-.5E yo";
  double mantissa3 = 0.00;
  int result3 = s21_sprintf(str, format_str3, mantissa3);
  int result_origin3 = sprintf(str_origin, format_str3, mantissa3);
  ck_assert_int_eq(result3, result_origin3);
  ck_assert_str_eq(str, str_origin);

  const char *format_str4 = "Hello %+020.15E %LE yo";
  double mantissa4 = 1.004554367;
  long double mantissa5 = -432432455454;
  int result4 = s21_sprintf(str, format_str4, mantissa4, mantissa5);
  int result_origin4 = sprintf(str_origin, format_str4, mantissa4, mantissa5);
  ck_assert_int_eq(result4, result_origin4);
  ck_assert_str_eq(str, str_origin);

  const char *format_str5 = "This is infinite: %-20.5e and this is nan: %20e";
  double infinite = 1.0 / 0.0;
  double not_a_number = infinite * 0.0;
  int result5 = s21_sprintf(str, format_str5, infinite, not_a_number);
  int result_origin5 = sprintf(str_origin, format_str5, infinite, not_a_number);
  ck_assert_int_eq(result5, result_origin5);
  ck_assert_str_eq(str, str_origin);

  const char *format_str6 = "% -10.14E yo";
  double mantissa6 = 0.00003044058697058435;
  int result6 = s21_sprintf(str, format_str6, mantissa6);
  int result_origin6 = sprintf(str_origin, format_str6, mantissa6);
  ck_assert_int_eq(result6, result_origin6);
  ck_assert_str_eq(str, str_origin);
}
END_TEST

START_TEST(s21_sprintf_p_test) {
  char str[80];
  char str_origin[80];
  int a = 10;
  char *format_str1 = "This is the pointer: %p\n";
  int result1 = s21_sprintf(str, format_str1, &a);
  int result_origin1 = sprintf(str_origin, format_str1, &a);

  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(str, str_origin);

  char *pointer = "Test";
  double double_pointer = 84759375969;

  char *format_str2 = "To the left: %-20p!\nTo the right %20p!";

  int result2 = s21_sprintf(str, format_str2, pointer, &double_pointer);
  int result_origin2 =
      sprintf(str_origin, format_str2, pointer, &double_pointer);
  ck_assert_int_eq(result2, result_origin2);
  ck_assert_str_eq(str, str_origin);
}
END_TEST

START_TEST(s21_sprintf_o_test) {
  int arr1[] = {0, -1, 1, 123, 1234, -1383, 9387};
  char str[80];
  char str1[80];
  int res = s21_sprintf(str, "%o", arr1[0]);
  int res1 = sprintf(str1, "%o", arr1[0]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%-12.3lo", (unsigned long)arr1[4]);
  res1 = sprintf(str1, "%-12.3lo", (unsigned long)arr1[4]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%010.5o", arr1[5]);
  ck_assert_str_eq(str, "37777775231");
  ck_assert_int_eq(res, 11);

  res = s21_sprintf(str, "%0#3.7o gterth", arr1[6]);
  ck_assert_str_eq(str, "0022253 gterth");
  ck_assert_int_eq(res, 14);

  res = s21_sprintf(str, "%-.4o gterth", arr1[6]);
  res1 = sprintf(str1, "%-.4o gterth", arr1[6]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%-#.9o gterth", arr1[6]);
  res1 = sprintf(str1, "%-#.9o gterth", arr1[6]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "hello %0.o gterth", arr1[6]);
  ck_assert_str_eq(str, "hello 22253 gterth");
  ck_assert_int_eq(res, 18);

  res = s21_sprintf(str, "hello %#o gterth", arr1[6]);
  res1 = sprintf(str1, "hello %#o gterth", arr1[6]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "hello %*.o gterth", 5, arr1[6]);
  res1 = sprintf(str1, "hello %*.o gterth", 5, arr1[6]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "hello %010.7o gterth", arr1[6]);
  ck_assert_str_eq(str, "hello    0022253 gterth");
  ck_assert_int_eq(res, 23);

  res = s21_sprintf(str, "%010.7ho", (unsigned short)arr1[6]);
  ck_assert_str_eq(str, "   0022253");
  ck_assert_int_eq(res, 10);
}
END_TEST

START_TEST(s21_sprintf_x_X_test) {
  int arr1[] = {0, -1, 1, 123, 1234, -1383, 9387};
  char str[80];
  char str1[80];
  int res = s21_sprintf(str, "%x", arr1[0]);
  int res1 = sprintf(str1, "%x", arr1[0]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%#10.7hx", (unsigned short)arr1[3]);
  res1 = sprintf(str1, "%#10.7hx", (unsigned short)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%-#10.3lx", (unsigned long)arr1[3]);
  res1 = sprintf(str1, "%-#10.3lx", (unsigned long)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%X", arr1[0]);
  res1 = sprintf(str1, "%X", arr1[0]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%#10.7lX", (unsigned long)arr1[3]);
  res1 = sprintf(str1, "%#10.7lX", (unsigned long)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%-#10.3hX", (unsigned short)arr1[3]);
  res1 = sprintf(str1, "%-#10.3hX", (unsigned short)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%-#*.3hX", 10, (unsigned short)arr1[3]);
  res1 = sprintf(str1, "%-#*.3hX", 10, (unsigned short)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_sprintf_c_test) {
  char str[80];
  char str1[80];
  char x = 'c';
  int res = s21_sprintf(str, "%-10c", x);
  int res1 = sprintf(str1, "%-10c", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%10c", x);
  res1 = sprintf(str1, "%10c", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_sprintf_s_test) {
  char str[80];
  char str1[80];
  char *x = "blablabla";
  int res = s21_sprintf(str, "%-11.10s", x);
  int res1 = sprintf(str1, "%-11.10s", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%11.8s", x);
  res1 = sprintf(str1, "%11.8s", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_sprintf_u_test) {
  char str[80];
  char str_orig[80];
  unsigned int a = 2345;

  int res_1 = s21_sprintf(str, "%10.5u", a);
  int res_1_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%10.5u", a);
  int res_2_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5u", a);
  int res_3_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%0u", a);
  int res_4_orig = sprintf(str_orig, "%0u", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%-u", a);
  int res_5_orig = sprintf(str_orig, "%-u", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%u", a);
  int res_6_orig = sprintf(str_orig, "%u", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%5u", a);
  int res_7_orig = sprintf(str_orig, "%5u", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "%05u", a);
  int res_8_orig = sprintf(str_orig, "%05u", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%-5u", a);
  int res_9_orig = sprintf(str_orig, "%-5u", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%.5u", a);
  int res_10_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%.5u", a);
  int res_11_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%-.5u", a);
  int res_12_orig = sprintf(str_orig, "%-.5u", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "%-10.5u", a);
  int res_13_orig = sprintf(str_orig, "%-10.5u", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%3.5u", a);
  int res_14_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%-3.5u", a);
  int res_15_orig = sprintf(str_orig, "%-3.5u", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "%6.2u", a);
  int res_16_orig = sprintf(str_orig, "%6.2u", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%3.2u", a);
  int res_17_orig = sprintf(str_orig, "%3.2u", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%01u", a);
  int res_18_orig = sprintf(str_orig, "%01u", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%hu", (unsigned short)a);
  int res_19_orig = sprintf(str_orig, "%hu", (unsigned short)a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%lu", (unsigned long)a);
  int res_20_orig = sprintf(str_orig, "%lu", (unsigned long)a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test) {
  char str[80];
  char str_orig[80];
  int a = 2345;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%05d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%hd", (unsigned short)a);
  int res_26_orig = sprintf(str_orig, "%hd", (unsigned short)a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);

  int res_27 = s21_sprintf(str, "%ld", (unsigned long)a);
  int res_27_orig = sprintf(str_orig, "%ld", (unsigned long)a);

  ck_assert_int_eq(res_27, res_27_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_2) {
  char str[80];
  char str_orig[80];
  int a = -23454546;

  int res_1 = s21_sprintf(str, "%10.*d", 5, a);
  int res_1_orig = sprintf(str_orig, "%10.*d", 5, a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%0*d", 5, a);
  int res_10_orig = sprintf(str_orig, "%0*d", 5, a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_3) {
  char str[80];
  char str_orig[80];
  int a = 234;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+6.2d", a);
  int res_26_orig = sprintf(str_orig, "%+6.2d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);

  int res_27 = s21_sprintf(str, "%+6.3d", a);
  int res_27_orig = sprintf(str_orig, "%+6.3d", a);

  ck_assert_int_eq(res_27, res_27_orig);
  ck_assert_str_eq(str, str_orig);

  int res_28 = s21_sprintf(str, "%+6.4d", a);
  int res_28_orig = sprintf(str_orig, "%+6.4d", a);

  ck_assert_int_eq(res_28, res_28_orig);
  ck_assert_str_eq(str, str_orig);

  int res_29 = s21_sprintf(str, "%-6.2d", -a);
  int res_29_orig = sprintf(str_orig, "%-6.2d", -a);

  ck_assert_int_eq(res_29, res_29_orig);
  ck_assert_str_eq(str, str_orig);

  int res_30 = s21_sprintf(str, "%+05d", a);
  int res_30_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_30, res_30_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_4) {
  char str[80];
  char str_orig[80];
  int a = -23;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_5) {
  char str[80];
  char str_orig[80];
  int a = -2344;

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_6) {
  char str[80];
  char str_orig[80];
  int a = 23;

  int res_1 = s21_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%+0d", a);
  int res_5_orig = sprintf(str_orig, "%+0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-+d", a);
  int res_6_orig = sprintf(str_orig, "%-+d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-+5d", a);
  int res_11_orig = sprintf(str_orig, "%-+5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-+.5d", a);
  int res_18_orig = sprintf(str_orig, "%-+.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-+10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-+10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-+3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-+3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_0) {
  char str[80];
  char str_orig[80];
  int a = 0;

  int res_1 = s21_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%05d", a);
  int res_5_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(test_s21_memchr) {
  const char str[] = "Hello, World!";
  char target = 'W';

  void *result = s21_memchr(str, target, sizeof(str));
  void *std_result = memchr(str, target, sizeof(str));

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_s21_memcmp) {
  const char str1[] = "Hello, World!";
  const char str2[] = "Hello, World!";
  const char str3[] = "Hello, C!";
  const char str4[] = "Hello, Worl!";

  int result1 = s21_memcmp(str1, str2, sizeof(str1));
  ck_assert_int_eq(result1, 0);

  int result2 = s21_memcmp(str1, str3, sizeof(str1));
  ck_assert_int_ne(result2, 0);

  int result3 = s21_memcmp(str1, str4, sizeof(str1));
  ck_assert_int_ne(result3, 0);
}
END_TEST

START_TEST(test_s21_memcpy) {
  const char src[] = "Hello, World!";
  char dest[sizeof(src)];

  s21_memcpy(dest, src, sizeof(src));

  ck_assert_mem_eq(dest, src, sizeof(src));
}
END_TEST

START_TEST(test_s21_memset) {
  char str[20];

  // Игнорируем возвращаемое значение, так как оно не используется в данном
  // тесте
  (void)s21_memset(str, 'A', sizeof(str));

  // Сравниваем только первые 10 символов
  ck_assert_mem_eq(str, "AAAAAAAAAA", 10);
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest[20] = "Hello, ";
  const char src[] = "World!";

  (void)s21_strncat(dest, src, sizeof(dest));

  // Проверяем, что результат корректно завершается нулевым символом
  ck_assert_str_eq(dest, "Hello, World!");
}
END_TEST

START_TEST(test_s21_strncmp) {
  const char str1[] = "Hello, World!";
  const char str2[] = "Hello, Universe!";
  s21_size_t n = 6;

  // Используем s21_strncmp и стандартный strncmp для сравнения результатов
  int result = s21_strncmp(str1, str2, n);
  int std_result = strncmp(str1, str2, n);

  // Сравниваем результаты
  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_s21_strchr) {
  const char str[] = "Hello, World!";
  char target = 'W';

  // Используем s21_strchr и стандартную strchr для сравнения результатов
  char *result = s21_strchr(str, target);
  char *std_result = strchr(str, target);

  // Сравниваем результаты
  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_s21_strncpy) {
  const char src[] = "Hello, World!";
  char dest[20];

  (void)s21_strncpy(dest, src, sizeof(dest));

  // Проверяем, что результат корректно завершается нулевым символом
  ck_assert_str_eq(dest, "Hello, World!");
}
END_TEST

START_TEST(test_s21_strcspn) {
  const char str1[] = "Hello, World!";
  const char str2[] = " ,!";

  // Используем s21_strcspn и стандартную strcspn
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t std_result = strcspn(str1, str2);

  // Сравниваем результаты
  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_s21_strerror_known_error) {
  ck_assert_str_eq(s21_strerror(ENOENT), "No such file or directory");
}
END_TEST

START_TEST(test_s21_strerror_unknown_error) {
  ck_assert_str_eq(s21_strerror(999), "Unknown error: 999");
}
END_TEST

START_TEST(test_s21_my_itoa_positive) {
  char result[10];
  s21_my_itoa(123, result);
  ck_assert_str_eq(result, "123");
}
END_TEST

START_TEST(test_s21_my_itoa_negative) {
  char result[10];
  s21_my_itoa(-456, result);
  ck_assert_str_eq(result, "-456");
}
END_TEST

START_TEST(test_s21_my_reverse) {
  char str[] = "hello";
  s21_my_reverse(str);
  ck_assert_str_eq(str, "olleh");
}
END_TEST

START_TEST(test_s21_strlen) {
  const char *str1 = "Hello, World!";
  const char *str2 = "";
  const char *str3 = "   ";  // Строка из пробелов

  ck_assert_int_eq(s21_strlen(str1), 13);
  ck_assert_int_eq(s21_strlen(str2), 0);
  ck_assert_int_eq(s21_strlen(str3), 3);
}
END_TEST

START_TEST(test_s21_strpbrk) {
  const char *str1 = "abcdef";
  const char *str2 = "12345";
  const char *result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(result, s21_NULL);

  const char *str3 = "Hello, World!";
  const char *str4 = "aeiou";
  result = s21_strpbrk(str3, str4);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_int_eq(*result, 'e');
}
END_TEST

START_TEST(test_s21_strrchr) {
  const char *str = "hello world";
  const char *result = s21_strrchr(str, 'l');
  const char *expected = strrchr(str, 'l');
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_empty_needle) {
  const char *haystack = "";
  const char *needle = "";
  char *result = s21_strstr(haystack, needle);
  ck_assert_str_eq(result, haystack);
}
END_TEST

START_TEST(test_s21_strstr_found) {
  const char *haystack = "Hello, world!";
  const char *needle = "world!";
  char *result = s21_strstr(haystack, needle);
  ck_assert_str_eq(result, "world!");
}
END_TEST

START_TEST(test_s21_strstr_not_found) {
  const char *haystack = "Hello, world!";
  const char *needle = "foo";
  char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_strtok_basic) {
  // Тестирование базового случая
  char str[] = "This is, a test-string";
  const char delim[] = " ,";

  char *token = s21_strtok(str, delim);
  ck_assert_str_eq(token, "This");

  token = s21_strtok(s21_NULL, delim);
  ck_assert_str_eq(token, "is");

  token = s21_strtok(s21_NULL, delim);
  ck_assert_str_eq(token, "a");

  token = s21_strtok(s21_NULL, delim);
  ck_assert_str_eq(token, "test-string");

  token = s21_strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token, s21_NULL);
}
END_TEST

START_TEST(test_strtok_empty_string) {
  // Тестирование с пустой строкой
  char str[] = "";
  const char delim[] = " ,";

  char *token = s21_strtok(str, delim);
  ck_assert_ptr_eq(token, s21_NULL);
}
END_TEST

START_TEST(test_strtok_no_delimiters) {
  // Тестирование строки без разделителей
  char str[] = "This_is_a_test_string";
  const char delim[] = ",;";

  char *token = s21_strtok(str, delim);
  ck_assert_str_eq(token, "This_is_a_test_string");

  token = s21_strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token, s21_NULL);
}
END_TEST

START_TEST(s21_to_lower_test) {
  char test_1[] = "1234567890";
  char test_2[] = "i_LOVE_verter";
  char test_3[] = "10A.B,C!@#$^&*";
  char test_4[] = "   ";
  char test_5[] = "QWERTY";
  char test_6[] = "QwErTy";

  char test_11[] = "1234567890";
  char test_22[] = "i_love_verter";
  char test_33[] = "10a.b,c!@#$^&*";
  char test_44[] = "   ";
  char test_55[] = "qwerty";
  char test_66[] = "qwerty";

  ck_assert_str_eq(s21_to_lower(test_1), test_11);
  ck_assert_str_eq(s21_to_lower(test_2), test_22);
  ck_assert_str_eq(s21_to_lower(test_3), test_33);
  ck_assert_str_eq(s21_to_lower(test_4), test_44);
  ck_assert_str_eq(s21_to_lower(test_5), test_55);
  ck_assert_str_eq(s21_to_lower(test_6), test_66);
}
END_TEST

START_TEST(s21_to_upper_test) {
  char test_1[] = "1234567890";
  char test_2[] = "i_LOVE_verter";
  char test_3[] = "10a.b,c!@#$^&*";
  char test_4[] = "   ";
  char test_5[] = "qwerty";
  char test_6[] = "QwErTy";

  char test_11[] = "1234567890";
  char test_22[] = "I_LOVE_VERTER";
  char test_33[] = "10A.B,C!@#$^&*";
  char test_44[] = "   ";
  char test_55[] = "QWERTY";
  char test_66[] = "QWERTY";

  ck_assert_str_eq(s21_to_upper(test_1), test_11);
  ck_assert_str_eq(s21_to_upper(test_2), test_22);
  ck_assert_str_eq(s21_to_upper(test_3), test_33);
  ck_assert_str_eq(s21_to_upper(test_4), test_44);
  ck_assert_str_eq(s21_to_upper(test_5), test_55);
  ck_assert_str_eq(s21_to_upper(test_6), test_66);
}
END_TEST

START_TEST(s21_insert_test) {
  char test_1[] = "1234567890";
  char test_1_2[] = "abc";
  int n1 = 3;

  char test_2[] = "abc";
  char test_2_2[] = "1";
  int n2 = 1;

  char test_3[] = "1234567890";
  char test_3_2[] = "abc";
  int n3 = 0;

  char test_4[] = "123";
  char test_4_2[] = "abc";
  int n4 = 2;

  char test_5[] = "!@#$^&*";
  char test_5_2[] = "A.1,BC";
  int n5 = 1;

  char test_6[] = "   ";
  char test_6_2[] = "123";
  int n6 = 2;

  char test_res_1[] = "123abc4567890";
  char test_res_2[] = "a1bc";
  char test_res_3[] = "abc1234567890";
  char test_res_4[] = "12abc3";
  char test_res_5[] = "!A.1,BC@#$^&*";
  char test_res_6[] = "  123 ";

  ck_assert_str_eq(s21_insert(test_1, test_1_2, n1), test_res_1);
  ck_assert_str_eq(s21_insert(test_2, test_2_2, n2), test_res_2);
  ck_assert_str_eq(s21_insert(test_3, test_3_2, n3), test_res_3);
  ck_assert_str_eq(s21_insert(test_4, test_4_2, n4), test_res_4);
  ck_assert_str_eq(s21_insert(test_5, test_5_2, n5), test_res_5);
  ck_assert_str_eq(s21_insert(test_6, test_6_2, n6), test_res_6);
}
END_TEST

START_TEST(s21_trim_test) {
  char test_1[] = "34";
  char trim_char_1[] = "9999999";
  char test_2[] = "   12345   ";
  char trim_char_2[] = " ";

  char test_3[] = "10A.B,C!@#$^&*";
  char trim_char_3[] = "1&*";

  char test_4[] = "111111222233334444555555";
  char trim_char_4[] = "15";

  char test_5[] = "   1   ";
  char trim_char_5[] = ";;adfgsdfg";

  char test_6[] = "     I love verter     ";
  char trim_char_6[] = " ";

  char test_trim_res_1[] = "34";
  char test_trim_res_2[] = "12345";
  char test_trim_res_3[] = "0A.B,C!@#$^";
  char test_trim_res_4[] = "222233334444";
  char test_trim_res_5[] = "   1   ";
  char test_trim_res_6[] = "I love verter";
  ck_assert_str_eq(s21_trim(test_1, trim_char_1), test_trim_res_1);
  ck_assert_str_eq(s21_trim(test_2, trim_char_2), test_trim_res_2);
  ck_assert_str_eq(s21_trim(test_3, trim_char_3), test_trim_res_3);
  ck_assert_str_eq(s21_trim(test_4, trim_char_4), test_trim_res_4);
  ck_assert_str_eq(s21_trim(test_5, trim_char_5), test_trim_res_5);
  ck_assert_str_eq(s21_trim(test_6, trim_char_6), test_trim_res_6);
}
END_TEST

START_TEST(sscanf_test) {
  short int sh1 = 0, sh2 = 0;
  long int ll1 = 0, ll2 = 0;
  int c = 0, res1 = 0, res2 = 0, g = 0;
  res1 = sscanf("123456789, -12345, 1234", "%hd, %ld, %2d", &sh1, &ll1, &c);
  res2 = s21_sscanf("123456789, -12345, 1234", "%hd, %ld, %2d", &sh2, &ll2, &g);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_1) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char test_cmp[] = "123 321";
  sscanf(test_cmp, "%d%d", &a, &b);
  s21_sscanf(test_cmp, "%d%d", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_2) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char test_cmp[] = "123 q321";
  sscanf(test_cmp, "%d%d", &a, &b);
  s21_sscanf(test_cmp, "%d%d", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_3) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char test_cmp[] = "q123 q321";
  int a1 = sscanf(test_cmp, "%d%d", &a, &b);
  int a2 = s21_sscanf(test_cmp, "%d%d", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
  ck_assert_int_eq(a2, a1);
}
END_TEST

START_TEST(test_my_s21_scanf_int_4) {
  short int a = 1;
  short int b = 1;
  short int c = 1;
  short int d = 1;
  char test_cmp[] = "123456789 345678321";
  sscanf(test_cmp, "%hd%hd", &a, &b);
  s21_sscanf(test_cmp, "%hd%hd", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}

START_TEST(test_my_s21_scanf_int_5) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char test_cmp[] = "123456789345678321";
  sscanf(test_cmp, "%4d%d", &a, &b);
  s21_sscanf(test_cmp, "%4d%d", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_6) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char a1 = 'p';
  char a2 = 'p';
  char test_cmp[] = "q123 321";
  sscanf(test_cmp, "%c%d%d", &a1, &a, &b);
  s21_sscanf(test_cmp, "%c%d%d", &a2, &c, &d);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_7) {
  int a = 1;
  int c = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char test_cmp[] = "q123 321";
  sscanf(test_cmp, "%s %d", a1, &a);
  s21_sscanf(test_cmp, "%s %d", a2, &c);
  ck_assert_str_eq(a1, a2);
  ck_assert_int_eq(a, c);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_8) {
  int a = 1;
  int c = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char test_cmp[] = "q123 321";
  sscanf(test_cmp, "%s%d", a1, &a);
  s21_sscanf(test_cmp, "%s%d", a2, &c);
  ck_assert_str_eq(a1, a2);
  ck_assert_int_eq(a, c);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_9) {
  int a = 1;
  int c = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "qHELLO 321";
  sscanf(test_cmp, "%c%s%d", &d, a1, &a);
  s21_sscanf(test_cmp, "%c%s%d", &d1, a2, &c);
  ck_assert_str_eq(a1, a2);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(d, d1);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_10) {
  int a = 1;
  int c = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "qHELLO 321";
  sscanf(test_cmp, "%s%c%d", a1, &d, &a);
  s21_sscanf(test_cmp, "%s%c%d", a2, &d1, &c);
  ck_assert_str_eq(a1, a2);
  // ck_assert_int_eq(a, c);
  ck_assert_int_eq(d, d1);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_11) {
  float a = 1;
  float c = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "qHELLO 321.12";
  sscanf(test_cmp, "%s%c%F", a1, &d, &a);
  s21_sscanf(test_cmp, "%s%c%F", a2, &d1, &c);
  ck_assert_str_eq(a1, a2);
  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_12) {
  float a = 1;
  float c = 1;
  int i = 1;
  int i1 = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "-0xF2qHELLO 321.12";
  sscanf(test_cmp, "%i%s%c%f", &i, a1, &d, &a);
  s21_sscanf(test_cmp, "%i%s%c%f", &i1, a2, &d1, &c);
  ck_assert_str_eq(a1, a2);
  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_13) {
  float a = 1;
  float c = 1;
  int i = 1;
  int i1 = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "0xF2 qHELLO 321.12";
  int res = sscanf(test_cmp, "%x%s%c%f", &i, a1, &d, &a);
  int res1 = s21_sscanf(test_cmp, "%x%s%c%f", &i1, a2, &d1, &c);
  ck_assert_int_eq(i1, i);
  ck_assert_str_eq(a1, a2);
  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(res1, res);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_14) {
  float a = 1;
  float c = 1;
  unsigned int i = 1;
  unsigned int i1 = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "-0x2fqHELLO 321.12";
  int res = sscanf(test_cmp, "%x%s%c%f", &i, a1, &d, &a);
  int res1 = s21_sscanf(test_cmp, "%x%s%c%f", &i1, a2, &d1, &c);
  ck_assert_int_eq(i1, i);
  ck_assert_str_eq(a1, a2);
  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(res1, res);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_17) {
  float a = 1;
  float c = 1;
  int i = 1;
  int i1 = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "024HELLO 321.12";
  sscanf(test_cmp, "%o%s%c%f", &i, a1, &d, &a);
  s21_sscanf(test_cmp, "%o%s%c%f", &i1, a2, &d1, &c);
  ck_assert_str_eq(a1, a2);
  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_18) {
  float a = 1;
  float c = 1;
  int i = 1;
  int i1 = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "024HELLO 321.12";
  sscanf(test_cmp, "%2i%s%c%f", &i, a1, &d, &a);
  s21_sscanf(test_cmp, "%2i%s%c%f", &i1, a2, &d1, &c);
  ck_assert_str_eq(a1, a2);
  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_19) {
  float a = 1;
  float c = 1;
  int i = 1;
  int i1 = 1;
  char *a1 = malloc(sizeof(char) * 10);
  char *a2 = malloc(sizeof(char) * 10);
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "024HELLO 321.12";
  sscanf(test_cmp, "%i%s%c%7f", &i, a1, &d, &a);
  s21_sscanf(test_cmp, "%i%s%c%7f", &i1, a2, &d1, &c);
  ck_assert_str_eq(a1, a2);
  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
  free(a1);
  free(a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_20) {
  float a = 1;
  float c = 1;
  int i = 1;
  int i1 = 1;

  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "024v 321.12";
  sscanf(test_cmp, "%i%c%f", &i, &d, &a);
  s21_sscanf(test_cmp, "%i%c%f", &i1, &d1, &c);

  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_21) {
  float a = 1;
  float c = 1;
  int i = 1;
  int i1 = 1;
  char d = 'e';
  char d1 = 'e';
  char test_cmp[] = "024v 321.12";
  sscanf(test_cmp, "%4i%c%f", &i, &d, &a);
  s21_sscanf(test_cmp, "%4i%c%f", &i1, &d1, &c);

  ck_assert_float_eq(a, c);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_15) {
  long int a = 1;
  long int b = 1;
  long int c = 1;
  long int d = 1;
  char test_cmp[] = "123456789 345678321";
  sscanf(test_cmp, "%ld%ld", &a, &b);
  s21_sscanf(test_cmp, "%ld%ld", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_16) {
  long int a = 1;
  long int b = 1;
  long int c = 1;
  long int d = 1;
  char test_cmp[] = "123456789 345678321";
  sscanf(test_cmp, "%4ld%ld", &a, &b);
  s21_sscanf(test_cmp, "%4ld%ld", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_23) {
  int i = 1;
  int i1 = 1;
  char test_cmp[] = "453";
  sscanf(test_cmp, "%x", &i);
  s21_sscanf(test_cmp, "%x", &i1);

  ck_assert_int_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_27) {
  int i = 1;
  int i1 = 1;
  int d = 'e';
  int d1 = 'e';
  char test_cmp[] = "000023 0000012";
  sscanf(test_cmp, "%o%o", &i, &d);
  s21_sscanf(test_cmp, "%o%o", &i1, &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_28) {
  int i = 1;
  int i1 = 1;
  int d = 'e';
  int d1 = 'e';
  char test_cmp[] = "023 012";
  sscanf(test_cmp, "%o%o", &i, &d);
  s21_sscanf(test_cmp, "%o%o", &i1, &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_29) {
  int i = 1;
  int i1 = 1;
  int d = 'e';
  int d1 = 'e';
  char test_cmp[] = "023 012";
  sscanf(test_cmp, "%d%d", &i, &d);
  s21_sscanf(test_cmp, "%d%d", &i1, &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_33) {
  int i = 1;
  int i1 = 1;
  int d = 'e';
  int d1 = 'e';
  char test_cmp[] = "-023 -012";
  sscanf(test_cmp, "%o%o", &i, &d);
  s21_sscanf(test_cmp, "%o%o", &i1, &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_42) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char test_cmp[] = "0xf2 0x2f";
  sscanf(test_cmp, "%x%x", &a, &b);
  s21_sscanf(test_cmp, "%x%x", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_43) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char test_cmp[] = "0xf2 0x23";
  sscanf(test_cmp, "%x%x", &a, &b);
  s21_sscanf(test_cmp, "%x%x", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_44) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char test_cmp[] = "0xf2 0x23";
  sscanf(test_cmp, "%x%x", &a, &b);
  s21_sscanf(test_cmp, "%x%x", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_45) {
  long int a = 1;
  long int b = 1;
  long int c = 1;
  long int d = 1;
  char test_cmp[] = "0xf2 0x23";
  sscanf(test_cmp, "%lx%lx", &a, &b);
  s21_sscanf(test_cmp, "%lx%lx", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_46) {
  short int a = 1;
  short int b = 1;
  short int c = 1;
  short int d = 1;
  char test_cmp[] = "0xf2 0x23";
  sscanf(test_cmp, "%hx%hx", &a, &b);
  s21_sscanf(test_cmp, "%hx%hx", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_47) {
  short int a = 1;
  short int b = 1;
  short int c = 1;
  short int d = 1;
  char test_cmp[] = "025 0999";
  sscanf(test_cmp, "%ho%ho", &a, &b);
  s21_sscanf(test_cmp, "%ho%ho", &c, &d);
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);
}
END_TEST

START_TEST(test_my_s21_scanf_int_31) {
  float i = 1;
  float i1 = 1;

  char test_cmp[] = "1.1234E34";
  sscanf(test_cmp, "%f", &i);
  s21_sscanf(test_cmp, "%f", &i1);
  ck_assert_float_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_32) {
  float i = 1;
  float i1 = 1;

  char test_cmp[] = "1.1234e34";
  sscanf(test_cmp, "%f", &i);
  s21_sscanf(test_cmp, "%f", &i1);
  ck_assert_float_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_34) {
  float i = 1;
  float i1 = 1;

  char test_cmp[] = "1.1234e34";
  sscanf(test_cmp, "%e", &i);
  s21_sscanf(test_cmp, "%e", &i1);
  ck_assert_float_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_35) {
  float i = 1;
  float i1 = 1;

  char test_cmp[] = "1.1234e34";
  sscanf(test_cmp, "%E", &i);
  s21_sscanf(test_cmp, "%E", &i1);
  ck_assert_float_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_63) {
  float i = 1;
  float i1 = 1;

  char test_cmp[] = "-1.1234e34";
  sscanf(test_cmp, "%f", &i);
  s21_sscanf(test_cmp, "%f", &i1);
  ck_assert_float_eq(i1, i);
}
END_TEST

START_TEST(test_my_s21_scanf_int_133) {
  uint32_t a1 = 0, a2 = 0;
  const char str[] = "0xFFFFFFFF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf((char *)str, fstr, &a1);
  uint32_t res2 = sscanf((char *)str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_my_s21_scanf_int_99) {
  int n1 = 0, n2 = 5;

  const char str[512] = "50 60 70 80";
  const char fstr[512] = "%n";

  int16_t res1 = s21_sscanf((char *)str, fstr, &n1);
  int16_t res2 = sscanf((char *)str, fstr, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("s21_string");
  TCase *tc1_1 = tcase_create("s21_string");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, s21_sprintf_o_test);
  tcase_add_test(tc1_1, s21_sprintf_f_test);
  tcase_add_test(tc1_1, s21_sprintf_g_test);
  tcase_add_test(tc1_1, s21_sprintf_prc_test);
  tcase_add_test(tc1_1, s21_sprintf_test);
  tcase_add_test(tc1_1, s21_sprintf_e_test);
  tcase_add_test(tc1_1, s21_sprintf_p_test);
  tcase_add_test(tc1_1, s21_sprintf_o_test);
  tcase_add_test(tc1_1, s21_sprintf_x_X_test);
  tcase_add_test(tc1_1, s21_sprintf_c_test);
  tcase_add_test(tc1_1, s21_sprintf_s_test);
  tcase_add_test(tc1_1, s21_sprintf_u_test);
  tcase_add_test(tc1_1, s21_sprintf_d_test);
  tcase_add_test(tc1_1, s21_sprintf_d_test_2);
  tcase_add_test(tc1_1, s21_sprintf_d_test_3);
  tcase_add_test(tc1_1, s21_sprintf_d_test_4);
  tcase_add_test(tc1_1, s21_sprintf_d_test_5);
  tcase_add_test(tc1_1, s21_sprintf_d_test_6);
  tcase_add_test(tc1_1, s21_sprintf_d_test_0);
  tcase_add_test(tc1_1, test_s21_memchr);
  tcase_add_test(tc1_1, test_s21_memcmp);
  tcase_add_test(tc1_1, test_s21_memcpy);
  tcase_add_test(tc1_1, test_s21_memset);
  tcase_add_test(tc1_1, test_s21_strncat);
  tcase_add_test(tc1_1, test_s21_strchr);
  tcase_add_test(tc1_1, test_s21_strncmp);
  tcase_add_test(tc1_1, test_s21_strncpy);
  tcase_add_test(tc1_1, test_s21_strcspn);
  tcase_add_test(tc1_1, test_s21_strerror_known_error);
  tcase_add_test(tc1_1, test_s21_strerror_unknown_error);
  tcase_add_test(tc1_1, test_s21_my_itoa_positive);
  tcase_add_test(tc1_1, test_s21_my_itoa_negative);
  tcase_add_test(tc1_1, test_s21_my_reverse);
  tcase_add_test(tc1_1, test_s21_strlen);
  tcase_add_test(tc1_1, test_s21_strpbrk);
  tcase_add_test(tc1_1, test_s21_strrchr);
  tcase_add_test(tc1_1, test_s21_strstr_empty_needle);
  tcase_add_test(tc1_1, test_s21_strstr_found);
  tcase_add_test(tc1_1, test_s21_strstr_not_found);
  tcase_add_test(tc1_1, test_strtok_basic);
  tcase_add_test(tc1_1, test_strtok_empty_string);
  tcase_add_test(tc1_1, test_strtok_no_delimiters);

  tcase_add_test(tc1_1, s21_to_lower_test);
  tcase_add_test(tc1_1, s21_to_upper_test);
  tcase_add_test(tc1_1, s21_insert_test);
  tcase_add_test(tc1_1, s21_trim_test);

  tcase_add_test(tc1_1, sscanf_test);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_1);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_2);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_3);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_4);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_5);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_6);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_7);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_8);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_9);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_10);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_11);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_12);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_13);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_14);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_17);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_18);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_19);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_20);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_21);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_15);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_16);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_23);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_27);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_28);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_29);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_42);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_43);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_44);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_45);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_46);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_31);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_32);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_34);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_35);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_63);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_133);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_47);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_33);
  tcase_add_test(tc1_1, test_my_s21_scanf_int_99);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
