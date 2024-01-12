#include "s21_string.h"

void spec_d(struct options *opt, long int d) {
  char d_str[10000] = {0};
  int min = 0;
  int width = 0;
  if (opt->length_h) d = (short int)d;
  if (!opt->length_l) d = (int)d;
  int length_d = s21_strlen(IntToAnsi(d, d_str, sizeof(d_str)));
  if (opt->accuracy > opt->width) {
    width = opt->accuracy;
  } else if (!opt->width && !opt->accuracy)
    width = length_d;
  else
    width = opt->width;
  if (d < 0) {
    d *= -1;
    min = 1;
    opt->space = 0;
    if (opt->width > opt->accuracy) width -= 1;
  }
  int check_plus = 0;
  if (opt->plus && min == 0) {
    if (opt->accuracy > length_d)
      check_plus = width - length_d - (opt->accuracy - length_d) - 1;
    else
      check_plus = width - length_d - 1;
  } else {
    if (opt->accuracy > length_d)
      check_plus = width - length_d - (opt->accuracy - length_d);
    else
      check_plus = width - length_d;
  }
  int flag_space = 0;
  if (width == opt->accuracy || width == length_d) flag_space = 1;
  if (d >= 0 && !opt->plus && opt->space && flag_space == 1)
    s21_strncat(opt->buf, " ", 1);
  if (opt->minus) {
    opt->zero = 0;
    if (opt->plus && min == 0) s21_strncat(opt->buf, "+", 1);
    if (min == 1) s21_strncat(opt->buf, "-", 1);
    if (opt->accuracy > length_d) {
      for (int i = 0; i < opt->accuracy - length_d; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, IntToAnsi(d, d_str, sizeof(d_str)), length_d);
    if (length_d < width) check_sign(opt, check_plus, min);
  } else {
    if (opt->plus && min == 0 && opt->zero == 1) s21_strncat(opt->buf, "+", 1);
    if (length_d < width)
      check_sign(opt, check_plus, min);
    else if (min == 1)
      s21_strncat(opt->buf, "-", 1);
    if (opt->plus && min == 0 && opt->zero == 0) s21_strncat(opt->buf, "+", 1);
    if (opt->accuracy > length_d) {
      for (int i = 0; i < opt->accuracy - length_d; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, IntToAnsi(d, d_str, sizeof(d_str)), length_d);
  }
}

void spec_c(struct options *opt, char c) {
  char c_arr[] = {c, '\0'};
  int check_plus = opt->width - 1;
  if (opt->width >= 0) {
    if (opt->minus) {
      s21_strncat(opt->buf, c_arr, 1);
      check_sign(opt, check_plus, 0);
    } else {
      check_sign(opt, check_plus, 0);
      s21_strncat(opt->buf, c_arr, 1);
    }
  }
}

void spec_s(struct options *opt, char *s) {
  int check_plus = opt->width - s21_strlen(s);
  if (opt->width >= 0) {
    if (opt->minus) {
      s21_strncat(opt->buf, s, s21_strlen(s));
      check_sign(opt, check_plus, 0);
    } else {
      check_sign(opt, check_plus, 0);
      s21_strncat(opt->buf, s, s21_strlen(s));
    }
  }
}

void spec_u(struct options *opt, unsigned long u) {
  char u_str[10000] = {0};
  int width = 0;
  int min = 0;
  if (opt->length_h) u = (unsigned short)u;
  if (!opt->length_l) u = (unsigned)u;
  if (opt->accuracy >= opt->width)
    width = opt->accuracy;
  else
    width = opt->width;
  int length_u = s21_strlen(IntToAnsi(u, u_str, sizeof(u_str)));
  int check_plus = 0;
  if (opt->accuracy > length_u)
    check_plus = width - length_u - (opt->accuracy - length_u);
  else
    check_plus = width - length_u;
  if (opt->minus) {
    opt->zero = 0;
    if (opt->accuracy > length_u) {
      for (int i = 0; i < opt->accuracy - length_u; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, IntToAnsi(u, u_str, sizeof(u_str)), length_u);
    if (length_u < width) check_sign(opt, check_plus, min);
  } else {
    if (length_u < width) check_sign(opt, check_plus, min);
    if (opt->accuracy > length_u) {
      for (int i = 0; i < opt->accuracy - length_u; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, IntToAnsi(u, u_str, sizeof(u_str)), length_u);
  }
}

void spec_f(struct options *opt, long double f) {
  char f_str[10000] = {0};
  int min = 0;
  if (f < 0.0) {
    min = 1;
    f *= -1;
    opt->space = 0;
    opt->width -= 1;
  }
  int signs = SignAfterPoint(f);
  if (!opt->accuracy && signs <= 6 && opt->accuracy_in == 0)
    opt->accuracy = 6;
  else if (!opt->accuracy && signs > 6 && opt->accuracy_in == 0)
    opt->accuracy = signs;
  int length_f =
      s21_strlen(DoubleToAnsi(f, opt->accuracy, f_str, sizeof(f_str), opt));
  int check_plus = 0;
  if (opt->plus && min == 0)
    check_plus = opt->width - length_f - 1;
  else
    check_plus = opt->width - length_f;
  if (f >= 0 && !opt->plus && opt->space && opt->width - length_f <= 0)
    s21_strncat(opt->buf, " ", 1);
  if (opt->minus) {
    opt->zero = 0;
    if (opt->plus && min == 0) s21_strncat(opt->buf, "+", 1);
    if (min == 1) s21_strncat(opt->buf, "-", 1);
    s21_strncat(opt->buf,
                DoubleToAnsi(f, opt->accuracy, f_str, sizeof(f_str), opt),
                length_f);
    if (opt->flag_for_g) removeTrailingZeros(opt->buf);

    if (length_f < opt->width) check_sign(opt, check_plus, min);
  } else {
    if (opt->plus && min == 0) s21_strncat(opt->buf, "+", 1);
    check_sign(opt, check_plus, min);
    s21_strncat(opt->buf,
                DoubleToAnsi(f, opt->accuracy, f_str, sizeof(f_str), opt),
                length_f);
    if (opt->flag_for_g) removeTrailingZeros(opt->buf);
  }
  if (opt->flag_for_g && (opt->buf[s21_strlen(opt->buf) - 1] == '.'))
    opt->buf[s21_strlen(opt->buf) - 1] = '\0';
}

void spec_x(struct options *opt, unsigned long x) {
  int width = 0;
  char x_str[10000] = {0};
  int min = 0;
  if (opt->length_h) x = (unsigned short)x;
  if (!opt->length_l) x = (unsigned)x;
  if (opt->accuracy >= opt->width)
    width = opt->accuracy;
  else
    width = opt->width;
  int length_x = s21_strlen(DecToHex(x, x_str, sizeof(x_str)));
  if (opt->hash) width -= 2;
  int check_plus = 0;
  if (opt->accuracy > length_x)
    check_plus = width - length_x - (opt->accuracy - length_x);
  else
    check_plus = width - length_x;
  if (opt->minus) {
    opt->zero = 0;
    if (opt->hash) s21_strncat(opt->buf, "0x", 2);
    if (opt->accuracy > length_x) {
      for (int i = 0; i < opt->accuracy - length_x; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, DecToHex(x, x_str, sizeof(x_str)), length_x);
    if (length_x < width) check_sign(opt, check_plus, min);
  } else {
    if (length_x < width) check_sign(opt, check_plus, min);
    if (opt->hash) s21_strncat(opt->buf, "0x", 2);
    if (opt->accuracy > length_x) {
      for (int i = 0; i < opt->accuracy - length_x; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, DecToHex(x, x_str, sizeof(x_str)), length_x);
  }
}

void spec_o(struct options *opt, unsigned long o) {
  int width = 0;
  char o_str[10000] = {0};
  int min = 0;
  opt->zero = 0;
  if (opt->length_h) o = (unsigned short)o;
  if (!opt->length_l) o = (unsigned)o;
  if (opt->accuracy >= opt->width) {
    width = opt->accuracy;
  } else
    width = opt->width;
  int length_o = s21_strlen(DecToOct(o, o_str, sizeof(o_str)));
  int check_plus = 0;
  if (opt->accuracy > length_o)
    check_plus = width - length_o - (opt->accuracy - length_o);
  else
    check_plus = width - length_o;
  if (opt->minus) {
    opt->zero = 0;
    if (opt->hash && length_o >= width) s21_strncat(opt->buf, "0", 1);
    if (opt->accuracy > length_o) {
      for (int i = 0; i < opt->accuracy - length_o; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, DecToOct(o, o_str, sizeof(o_str)), length_o);
    if (length_o < width) check_sign(opt, check_plus, min);
  } else {
    if (length_o < width) check_sign(opt, check_plus, min);
    if (opt->hash && length_o >= width) s21_strncat(opt->buf, "0", 1);
    if (opt->accuracy > length_o) {
      for (int i = 0; i < opt->accuracy - length_o; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, DecToOct(o, o_str, sizeof(o_str)), length_o);
  }
}

void spec_e(struct options *opt, long double e) {
  int min = 0;
  if (e < 0) {
    e *= -1;
    min = 1;
    opt->space = 0;
    opt->width -= 1;
  }
  char e_str[10000] = {0};
  if (!opt->accuracy) opt->accuracy = 6;
  int exp = int_exp(e);
  double mantissa = printExponential(e);
  int length_e = s21_strlen(
      DoubleToAnsi(mantissa, opt->accuracy, e_str, sizeof(e_str), opt));
  int check_plus = 0;
  if (opt->plus && min == 0)
    check_plus = opt->width - length_e - 5;
  else
    check_plus = opt->width - length_e - 4;
  if (e >= 0 && !opt->plus && opt->space && opt->width - length_e <= 0)
    s21_strncat(opt->buf, " ", 1);
  if (opt->minus == 0) check_sign(opt, check_plus, min);
  if (opt->plus && min == 0) s21_strncat(opt->buf, "+", 1);
  if (min == 1 && opt->minus) s21_strncat(opt->buf, "-", 1);
  if (opt->flag_for_g && !opt->hash) {
    s21_strncat(
        opt->buf,
        DoubleToAnsi(mantissa, opt->accuracy, e_str, sizeof(e_str), opt), 17);
    s21_strncpy(opt->buf, removeTrailingZeros(opt->buf), 10000);
    if (opt->buf[s21_strlen(opt->buf) - 1] == '.')
      opt->buf[s21_strlen(opt->buf) - 1] = '\0';
  } else if (opt->flag_for_g && opt->hash) {
    char str[1000] = {0};
    int length = s21_strlen(IntToAnsi((int)mantissa, str, sizeof(str)));
    opt->accuracy = opt->accuracy - length;
    s21_strncat(
        opt->buf,
        DoubleToAnsi(mantissa, opt->accuracy, e_str, sizeof(e_str), opt), 17);
  } else {
    s21_strncat(
        opt->buf,
        DoubleToAnsi(mantissa, opt->accuracy, e_str, sizeof(e_str), opt), 17);
  }
  s21_strncat(opt->buf, "e", 1);
  if (e >= 1)
    s21_strncat(opt->buf, "+", 1);
  else
    s21_strncat(opt->buf, "-", 1);
  exp = abs(exp);
  if (exp < 10) s21_strncat(opt->buf, "0", 1);
  s21_strncat(opt->buf, IntToAnsi(exp, e_str, sizeof(e_str)), 2);
  if (opt->minus == 1)
    if (length_e < opt->width) check_sign(opt, check_plus, min);
}

void spec_g(struct options *opt, double g) {
  char str[1000] = {0};
  if (!opt->length_L) g = (float)g;
  int length = s21_strlen(IntToAnsi((int)g, str, sizeof(str)));
  if (fabs(g) > 0.0001 && fabs(g) < 999999.444444) {
    if (fabs(g) > 1 && !opt->accuracy)
      opt->accuracy = 3;
    else if (fabs(g) > 1 && opt->accuracy)
      opt->accuracy = opt->accuracy - length;
    spec_f(opt, g);
  } else {
    spec_e(opt, g);
  }
}

void spec_p(struct options *opt, void *p) {
  char *str_number = s21_convert((unsigned long long)p);
  int width = 0;
  int min = 0;
  int length_p = s21_strlen(str_number);
  if (opt->accuracy > opt->width) {
    width = opt->accuracy;
  } else if (!opt->width && !opt->accuracy)
    width = length_p;
  else
    width = opt->width;
  int check_plus = 0;
  if (opt->accuracy > length_p)
    check_plus = width - length_p - (opt->accuracy - length_p) - 2;
  else
    check_plus = width - length_p - 2;
  if (opt->minus) {
    opt->zero = 0;
    s21_strncat(opt->buf, "0x", 2);
    if (opt->accuracy > length_p) {
      for (int i = 0; i < opt->accuracy - length_p; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, str_number, 100000);
    if (length_p < width) check_sign(opt, check_plus, min);
  } else {
    if (opt->zero == 1) s21_strncat(opt->buf, "0x", 2);
    if (length_p < width) check_sign(opt, check_plus, min);
    if (opt->zero == 0) s21_strncat(opt->buf, "0x", 2);
    if (opt->accuracy > length_p) {
      for (int i = 0; i < opt->accuracy - length_p; i++)
        s21_strncat(opt->buf, "0", 1);
    }
    s21_strncat(opt->buf, str_number, 10000);
  }
}