C = gcc
CC = gcc -c
ARCR= ar cr
RLIB = ranlib
RM = rm -rf
GENHTML = genhtml

SOURCE = *.c
TESTS = tests/*c
OBJ = *.o
ARCHIVE = s21_matrix.a
ALLEX = $(OBJ) $(ARCHIVE) a.out *.gch *.gcno *.info *.gcda report
EXGCOVREP = a.out *.gcno *.info *.gcda

RUN_OUT = ./a.out

WFLAGS = -Wall -Werror -Wextra
LFLAGS = -lm -lpthread -lcheck
ifeq ($(shell uname), Linux)
LFLAGS = -lcheck -lsubunit -lm -lrt -lpthread
endif
DFLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --leak-check=full --track-origins=yes --trace-children=yes --quiet 
# --vgdb=yes --vgdb-error=1 --vgdb-error=0 --vgdb-stop-at=startu --vgdb-stop-at=startup --vgdb-error=0 

#	gcc $(SOURCE)
all:$(ARCHIVE) test

deb:
	gcc .debug/main.c *.c -o a.out 

valgrind: valgrind_build

valgrind_build: $(ARCHIVE)
	$(CC) $(TESTS) -g
	$(C) $(OBJ) -L. $(ARCHIVE) $(LFLAGS) 
	$(RM) $(OBJ)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./a.out

$(ARCHIVE):
	$(CC) $(WFLAGS) $(SOURCE) 
	$(ARCR) $(ARCHIVE) $(OBJ)
	$(RLIB) $(ARCHIVE)
	$(RM) $(OBJ)

test: $(ARCHIVE)
	$(CC) $(TESTS)
	$(C) $(OBJ) -L. $(ARCHIVE) $(LFLAGS)
	$(RM) $(OBJ)
	$(RUN_OUT)

gcov: gcov_report

gcov_report: $(ARCHIVE)
	$(C) $(DFLAGS) $(SOURCE) $(TESTS) $(LFLAGS)
	$(RUN_OUT)
	lcov -t "test" -o *.info -c -d .
	$(GENHTML) -o report/ *info
	open ./report/index.html
	$(RM) $(EXGCOVREP)

clean:
	$(RM) $(ALLEX)
	
rebuild: clean all

style:
	cp ../materials/linters/.clang-format .
	cp ../materials/linters/.clang-format ./tests
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n tests/*.c
	clang-format -n tests/*.h
	rm ./.clang-format
	rm ./tests/.clang-format
