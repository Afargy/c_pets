C = gcc
CC = gcc -c
ARCR= ar cr
RLIB = ranlib
RM = rm
GENHTML = genhtml

SOURCE = *.c
TESTS = tests/*.c
OBJ = *.o
ARCHIVE = s21_decimal.a
ALLEX = $(OBJ) $(ARCHIVE) a.out *.gch *.gcno *.info *.gcda report
EXGCOVREP = a.out *.gcno *.info *.gcda

RUN_OUT = ./a.out

WFLAGS = -Wall -Werror -Wextra
LFLAGS = -lm -lpthread -lcheck
ifeq ($(shell uname), Linux)
LFLAGS = -lcheck -lsubunit -lm -lrt -lpthread
endif
DFLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

all: s21_decimal.a test

valgrind: valgrind_build

valgrind_build: s21_decimal.a
	$(CC) $(TESTS)
	$(C) $(OBJ) -L. $(ARCHIVE) $(LFLAGS)
	$(RM) $(OBJ)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./a.out

s21_decimal.a:
	$(CC) $(WFLAGS) $(SOURCE)
	$(ARCR) $(ARCHIVE) $(OBJ)
	$(RLIB) $(ARCHIVE)
	$(RM) $(OBJ)

test: s21_decimal.a
	$(CC) $(TESTS)
	$(C) $(OBJ) -L. $(ARCHIVE) $(LFLAGS)
	$(RM) $(OBJ)
	$(RUN_OUT)

gcov_report: s21_decimal.a
	$(C) $(DFLAGS) $(SOURCE) $(TESTS) $(LFLAGS)
	$(RUN_OUT)
	lcov -t "test" -o *.info -c -d .
	$(GENHTML) -o report/ *info
	open ./report/index.html
	$(RM) $(EXGCOVREP)

clean:
	$(RM) -rf $(ALLEX)

clean_a:
	$(RM) $(ARCHIVE)

rebuild: clean_a all

style:
	cp ../materials/linters/.clang-format .
	cp ../materials/linters/.clang-format ./tests
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n tests/*.c
	clang-format -n tests/*.h
	rm ./.clang-format
	rm ./tests/.clang-format
