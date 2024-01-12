PROJECT_NAME = s21_string
CC = gcc
OS = $(shell uname)

ifeq ($(OS), Linux)
	FLAGS = -Werror -Wall -Wextra -std=c11 -lm -lsubunit
	TEST_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	FLAGS = -Werror -Wall -Wextra -std=c11
	TEST_FLAGS = -lcheck
endif

.PHONY: all clean test s21_string.a gcov_report style clang

all: $(PROJECT_NAME).a

$(PROJECT_NAME).a:
	$(CC) $(FLAGS) -c s21_string.c -o s21_string.o
	$(CC) $(FLAGS) -c s21_sprintf.c -o s21_sprintf.o
	$(CC) $(FLAGS) -c s21_sscanf.c -o s21_sscanf.o
	$(CC) $(FLAGS) -c s21_functions.c -o s21_functions.o
	$(CC) $(FLAGS) -c s21_specificators.c -o s21_specificators.o
	$(CC) $(FLAGS) -c s21_csharp_insert.c -o s21_csharp_insert.o
	$(CC) $(FLAGS) -c s21_csharp_tolower.c -o s21_csharp_tolower.o
	$(CC) $(FLAGS) -c s21_csharp_toupper.c -o s21_csharp_toupper.o
	$(CC) $(FLAGS) -c s21_csharp_trim.c -o s21_csharp_trim.o
	ar rcs $(PROJECT_NAME).a s21_string.o s21_sprintf.o s21_sscanf.o s21_functions.o s21_specificators.o s21_csharp_insert.o s21_csharp_tolower.o s21_csharp_toupper.o s21_csharp_trim.o


test:$(PROJECT_NAME).a
	$(CC) $(FLAGS) s21_tests.c $(PROJECT_NAME).a -o s21_test $(TEST_FLAGS)
	./s21_test

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	make test
	leaks --atExit -- test

gcov_report: clean
	$(CC) $(FLAGS) -c s21_tests.c
	$(CC) $(FLAGS) --coverage s21_tests.o s21_string.c s21_sprintf.c s21_sscanf.c s21_functions.c s21_specificators.c s21_csharp_insert.c s21_csharp_tolower.c s21_csharp_toupper.c s21_csharp_trim.c -o s21_test $(TEST_FLAGS)
	./s21_test
	lcov -d ./ --capture --output-file $(PROJECT_NAME).info
	genhtml $(PROJECT_NAME).info --output-directory report
	open report/index.html

style: clean
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	clang-format -n *.h
	rm -rf .clang-format

clang: clean
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c
	clang-format -i *.h
	rm -rf .clang-format

clean:
	rm -rf *.a *.out *.o s21_test *.html *.css
	rm -rf *.g* *.info report
