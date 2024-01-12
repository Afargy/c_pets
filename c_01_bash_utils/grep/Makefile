CC = gcc
FLAGS = -Wall -Werror -Wextra

all: quest1

quest1: s21_grep
quest2: strcmp_tests
quest3: strcpy_tests
quest4: strcat_tests

s21_grep:
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

test:
	sh test_func_grep.sh

test_leaks:
	sh test_leak_grep.sh

clean:
	rm -rf *.o | rm -rf *.a && rm -rf *.so | rm s21_grep

rebuild: clean all