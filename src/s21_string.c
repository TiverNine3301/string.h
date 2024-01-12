#include "s21_string.h"

// Функция поиска первого вхождения байта 'c' в первых 'n' байтах блока памяти
// 'str'. Возвращает указатель на найденный байт или s21_NULL, если байт не
// найден.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == s21_NULL) {
    errno = EINVAL;  // Установка кода ошибки в случае недопустимых аргументов
    return s21_NULL;
  }

  const unsigned char *s = str;
  unsigned char uc = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    if (s[i] == uc || s[i] == '\0') {
      return (void *)(s + i);
    }
  }

  return s21_NULL;
}

// Функция сравнения первых 'n' байтов блоков памяти 'str1' и 'str2'.
// Возвращает 0, если блоки идентичны, отрицательное значение, если str1 < str2,
// и положительное значение в противном случае.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  if (str1 == s21_NULL || str2 == s21_NULL) {
    errno = EINVAL;  // Установка кода ошибки в случае недопустимых аргументов
    return -1;
  }

  const unsigned char *s1 = str1;
  const unsigned char *s2 = str2;

  for (s21_size_t i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      return (int)(s1[i] - s2[i]);
    }
  }

  return 0;
}

// Функция копирования 'n' байтов из блока памяти 'src' в блок памяти 'dest'.
// Возвращает указатель на 'dest'.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest == s21_NULL || src == s21_NULL) {
    errno = EINVAL;  // Установка кода ошибки в случае недопустимых аргументов
    return s21_NULL;
  }

  unsigned char *d = dest;
  const unsigned char *s = src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

// Функция установки первых 'n' байтов блока памяти 'str' значения 'c'.
// Возвращает указатель на 'str'.
void *s21_memset(void *str, int c, s21_size_t n) {
  if (str == s21_NULL) {
    errno = EINVAL;  // Установка кода ошибки в случае недопустимых аргументов
    return s21_NULL;
  }

  unsigned char *s = str;
  unsigned char uc = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    s[i] = uc;
  }

  return str;
}

// Функция конкатенации строки 'src' с концом строки 'dest'.
// Копирует не более 'n' символов, добавляет завершающий нулевой символ.
// Возвращает указатель на 'dest'.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest == s21_NULL || src == s21_NULL) {
    errno = EINVAL;  // Установка кода ошибки в случае недопустимых аргументов
    return s21_NULL;
  }

  char *d = dest;

  while (*d) {
    d++;
  }

  while (*src && n > 0) {
    *d++ = *src++;
    n--;
  }

  *d = '\0';

  return dest;
}

// Функция поиска первого вхождения символа 'c' в строке 'str'.
// Возвращает указатель на найденный символ или s21_NULL, если символ не найден.
char *s21_strchr(const char *str, int c) {
  if (str == s21_NULL) {
    errno = EINVAL;  // Установка кода ошибки в случае недопустимых аргументов
    return s21_NULL;
  }

  while (*str != '\0') {
    if (*str == (char)c) {
      return (char *)str;
    }
    str++;
  }

  return s21_NULL;
}

// Функция сравнения первых 'n' символов строк 'str1' и 'str2'.
// Возвращает 0, если строки идентичны, отрицательное значение, если str1 <
// str2, и положительное значение в противном случае.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  if (str1 == s21_NULL || str2 == s21_NULL) {
    errno = EINVAL;  // Установка кода ошибки в случае недопустимых аргументов
    return -1;
  }

  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      return (int)(unsigned char)str1[i] - (int)(unsigned char)str2[i];
    }

    if (str1[i] == '\0') {
      return 0;
    }
  }

  return 0;
}

// Функция копирования первых 'n' символов строки 'src' в строку 'dest'.
// Возвращает указатель на 'dest'.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; ++i) {
    dest[i] = src[i];
  }

  return dest;
}

// Функция поиска длины префикса строки 'str1', содержащего только символы
// отсутствующие в строке 'str2'.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *p1, *p2;
  s21_size_t count = 0;

  for (p1 = str1; *p1 != '\0'; ++p1) {
    for (p2 = str2; *p2 != '\0'; ++p2) {
      if (*p1 == *p2) {
        return count;
      }
    }
    ++count;
  }

  return count;
}

// Макрос для определения текущей операционной системы
#ifdef __APPLE__
#define MAX 106
char *errorList[] = {"Undefined error: 0",
                     "Operation not permitted",
                     "No such file or directory",
                     "No such process",
                     "Interrupted system call",
                     "Input/output error",
                     "Device not configured",
                     "Argument list too long",
                     "Exec format error",
                     "Bad file descriptor",
                     "No child processes",
                     "Resource deadlock avoided",
                     "Cannot allocate memory",
                     "Permission denied",
                     "Bad address",
                     "Block device required",
                     "Resource busy",
                     "File exists",
                     "Cross-device link",
                     "Operation not supported by device",
                     "Not a directory",
                     "Is a directory",
                     "Invalid argument",
                     "Too many open files in system",
                     "Too many open files",
                     "Inappropriate ioctl for device",
                     "Text file busy",
                     "File too large",
                     "No space left on device",
                     "Illegal seek",
                     "Read-only file system",
                     "Too many links",
                     "Broken pipe",
                     "Numerical argument out of domain",
                     "Result too large",
                     "Resource temporarily unavailable",
                     "Operation now in progress",
                     "Operation already in progress",
                     "Socket operation on non-socket",
                     "Destination address required",
                     "Message too long",
                     "Protocol wrong type for socket",
                     "Protocol not available",
                     "Protocol not supported",
                     "Socket type not supported",
                     "Operation not supported",
                     "Protocol family not supported",
                     "Address family not supported by protocol family",
                     "Address already in use",
                     "Can't assign requested address",
                     "Network is down",
                     "Network is unreachable",
                     "Network dropped connection on reset",
                     "Software caused connection abort",
                     "Connection reset by peer",
                     "No buffer space available",
                     "Socket is already connected",
                     "Socket is not connected",
                     "Can't send after socket shutdown",
                     "Too many references: can't splice",
                     "Operation timed out",
                     "Connection refused",
                     "Too many levels of symbolic links",
                     "File name too long",
                     "Host is down",
                     "No route to host",
                     "Directory not empty",
                     "Too many processes",
                     "Too many users",
                     "Disc quota exceeded",
                     "Stale NFS file handle",
                     "Too many levels of remote in path",
                     "RPC struct is bad",
                     "RPC version wrong",
                     "RPC prog. not avail",
                     "Program version wrong",
                     "Bad procedure for program",
                     "No locks available",
                     "Function not implemented",
                     "Inappropriate file type or format",
                     "Authentication error",
                     "Need authenticator",
                     "Device power is off",
                     "Device error",
                     "Value too large to be stored in data type",
                     "Bad executable (or shared library)",
                     "Bad CPU type in executable",
                     "Shared library version mismatch",
                     "Malformed Mach-o file",
                     "Operation canceled",
                     "Identifier removed",
                     "No message of desired type",
                     "Illegal byte sequence",
                     "Attribute not found",
                     "Bad message",
                     "EMULTIHOP (Reserved)",
                     "No message available on STREAM",
                     "ENOLINK (Reserved)",
                     "No STREAM resources",
                     "Not a STREAM",
                     "Protocol error",
                     "STREAM ioctl timeout",
                     "Operation not supported on socket",
                     "Policy not found",
                     "State not recoverable",
                     "Previous owner died",
                     "Interface output queue is full"};
#elif __linux__
#define MAX 133
char *errorList[] = {"Success",
                     "Operation not permitted",
                     "No such file or directory",
                     "No such process",
                     "Interrupted system call",
                     "Input/output error",
                     "No such device or address",
                     "Argument list too long",
                     "Exec format error",
                     "Bad file descriptor",
                     "No child processes",
                     "Resource temporarily unavailable",
                     "Cannot allocate memory",
                     "Permission denied",
                     "Bad address",
                     "Block device required",
                     "Device or resource busy",
                     "File exists",
                     "Invalid cross-device link",
                     "No such device",
                     "Not a directory",
                     "Is a directory",
                     "Invalid argument",
                     "Too many open files in system",
                     "Too many open files",
                     "Inappropriate ioctl for device",
                     "Text file busy",
                     "File too large",
                     "No space left on device",
                     "Illegal seek",
                     "Read-only file system",
                     "Too many links",
                     "Broken pipe",
                     "Numerical argument out of domain",
                     "Numerical result out of range",
                     "Resource deadlock avoided",
                     "File name too long",
                     "No locks available",
                     "Function not implemented",
                     "Directory not empty",
                     "Too many levels of symbolic links",
                     "Unknown error 41",
                     "No message of desired type",
                     "Identifier removed",
                     "Channel number out of range",
                     "Level 2 not synchronized",
                     "Level 3 halted",
                     "Level 3 reset",
                     "Link number out of range",
                     "Protocol driver not attached",
                     "No CSI structure available",
                     "Level 2 halted",
                     "Invalid exchange",
                     "Invalid request descriptor",
                     "Exchange full",
                     "No anode",
                     "Invalid request code",
                     "Invalid slot",
                     "Unknown error 58",
                     "Bad font file format",
                     "Device not a stream",
                     "No data available",
                     "Timer expired",
                     "Out of streams resources",
                     "Machine is not on the network",
                     "Package not installed",
                     "Object is remote",
                     "Link has been severed",
                     "Advertise error",
                     "Srmount error",
                     "Communication error on send",
                     "Protocol error",
                     "Multihop attempted",
                     "RFS specific error",
                     "Bad message",
                     "Value too large for defined data type",
                     "Name not unique on network",
                     "File descriptor in bad state",
                     "Remote address changed",
                     "Can not access a needed shared library",
                     "Accessing a corrupted shared library",
                     ".lib section in a.out corrupted",
                     "Attempting to link in too many shared libraries",
                     "Cannot exec a shared library directly",
                     "Invalid or incomplete multibyte or wide character",
                     "Interrupted system call should be restarted",
                     "Streams pipe error",
                     "Too many users",
                     "Socket operation on non-socket",
                     "Destination address required",
                     "Message too long",
                     "Protocol wrong type for socket",
                     "Protocol not available",
                     "Protocol not supported",
                     "Socket type not supported",
                     "Operation not supported",
                     "Protocol family not supported",
                     "Address family not supported by protocol",
                     "Address already in use",
                     "Cannot assign requested address",
                     "Network is down",
                     "Network is unreachable",
                     "Network dropped connection on reset",
                     "Software caused connection abort",
                     "Connection reset by peer",
                     "No buffer space available",
                     "Transport endpoint is already connected",
                     "Transport endpoint is not connected",
                     "Cannot send after transport endpoint shutdown",
                     "Too many references: cannot splice",
                     "Connection timed out",
                     "Connection refused",
                     "Host is down",
                     "No route to host",
                     "Operation already in progress",
                     "Operation now in progress",
                     "Stale file handle",
                     "Structure needs cleaning",
                     "Not a XENIX named type file",
                     "No XENIX semaphores available",
                     "Is a named type file",
                     "Remote I/O error",
                     "Disk quota exceeded",
                     "No medium found",
                     "Wrong medium type",
                     "Operation canceled",
                     "Required key not available",
                     "Key has expired",
                     "Key has been revoked",
                     "Key was rejected by service",
                     "Owner died",
                     "State not recoverable",
                     "Operation not possible due to RF-kill",
                     "Memory page has hardware error"};
#endif

char unknownerror[100] = {0};

char *s21_strerror(int errnum) {
  char *ptr = s21_NULL;
  if (errnum > MAX || errnum < 0) {
    char number[30] = {0};
    s21_my_itoa(errnum, number);
#ifdef __APPLE__
    s21_memset(unknownerror, 0, 100);
    s21_strncat(unknownerror, "Unknown error: ", 100);
#endif
#ifdef __linux__
    s21_memset(unknownerror, 0, 100);
    s21_strncat(unknownerror, "Unknown error ", 100);
#endif
    s21_strncat(unknownerror, number, 100);
    ptr = (char *)unknownerror;
  } else {
    ptr = (char *)errorList[errnum];
  }
  return ptr;
}

void s21_my_itoa(int n, char arr[]) {
  int i = 0, sign = 0;
  if ((sign = n) < 0) n = -n;
  do {
    arr[i++] = n % 10 + 48;
  } while ((n /= 10) > 0);
  if (sign < 0) arr[i++] = '-';
  arr[i] = '\0';
  s21_my_reverse(arr);
}

void s21_my_reverse(char arr[]) {
  int i = 0;
  int j = 0;
  char c = '\0';
  for (i = 0, j = s21_strlen(arr) - 1; i < j; i++, j--) {
    c = arr[i];
    arr[i] = arr[j];
    arr[j] = c;
  }
}

// Функция вычисления длины строки 'str'.
s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;

  while (*str != '\0') {
    length++;
    str++;
  }

  return length;
}

// Функция поиска первого вхождения любого символа из строки 'str2' в строке
// 'str1'. Возвращает указатель на найденный символ или s21_NULL, если символ не
// найден.
char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1) {
    const char *p = str2;
    while (*p) {
      if (*p == *str1) {
        return (char *)str1;
      }
      p++;
    }
    str1++;
  }
  return s21_NULL;
}

// Функция поиска последнего вхождения символа 'c' в строке 'str'.
// Возвращает указатель на последнее вхождение символа или s21_NULL, если символ
// не найден.
char *s21_strrchr(const char *str, int c) {
  const char *last_occurrence = s21_NULL;

  while (*str != '\0') {
    if (*str == (char)c) {
      last_occurrence = str;
    }
    str++;
  }

  if (*str == (char)c) {
    return (char *)str;
  } else {
    return (char *)last_occurrence;
  }
}

// Функция поиска подстроки 'needle' в строке 'haystack'.
// Возвращает указатель на начало найденной подстроки или s21_NULL, если
// подстрока не найдена.
char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') {
    return (char *)haystack;
  }

  while (*haystack != '\0') {
    const char *h = haystack;
    const char *n = needle;

    while (*n != '\0' && *h == *n) {
      h++;
      n++;
    }

    if (*n == '\0') {
      return (char *)haystack;
    }

    haystack++;
  }

  return s21_NULL;
}

// Функция извлечения токена из строки 'str' с использованием разделителей из
// строки 'delim'.
char *s21_strtok(char *str, const char *delim) {
  static char *lastToken = s21_NULL;  // указатель на последний токен
  char *token;  // указатель на текущий токен

  // Если передана новая строка, начинаем разбор с неё
  if (str != s21_NULL) {
    lastToken = str;
  } else if (lastToken == s21_NULL) {
    // Если исходной строки нет и последний токен не установлен, возвращаем
    // s21_NULL
    return s21_NULL;
  }

  // Пропускаем начальные разделители
  while (*lastToken != '\0' && s21_strchr(delim, *lastToken) != s21_NULL) {
    ++lastToken;
  }

  // Если достигнут конец строки после пропуска разделителей, возвращаем
  // s21_NULL
  if (*lastToken == '\0') {
    lastToken = s21_NULL;
    return s21_NULL;
  }

  // Устанавливаем указатель на текущий токен
  token = lastToken;

  // Ищем конец токена
  while (*lastToken != '\0' && s21_strchr(delim, *lastToken) == s21_NULL) {
    ++lastToken;
  }

  // Если достигнут конец строки после токена, устанавливаем lastToken в
  // s21_NULL
  if (*lastToken == '\0') {
    lastToken = s21_NULL;
  } else {
    // Заменяем разделитель в конце токена нулевым символом
    *lastToken = '\0';
    ++lastToken;
  }

  return token;
}