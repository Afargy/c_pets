CC = gcc
FLAGS = -Wall -Werror -Wextra

all: quest1

quest1: s21_cat
quest2: strcmp_tests
quest3: strcpy_tests
quest4: strcat_tests

s21_cat:
	$(CC) $(FLAGS) s21_cat_modules.c s21_cat.c -o s21_cat

test:
	sh test_func_cat.sh

test_leaks:
	sh test_leak_cat.sh

clean:
	rm -rf *.o | rm -rf *.a && rm -rf *.so | rm s21_cat

rebuild: clean all