C = gcc
CC = gcc -c
ARCR= ar cr
RLIB = ranlib
RM = rm -rf
GENHTML = genhtml

SOURCE = *.c
TESTS = tests/*c
OBJ = *.o
ARCHIVE = calc.a
ALLEX = $(OBJ) $(ARCHIVE) a.out *.gch *.gcno *.info *.gcda report
EXGCOVREP = a.out *.gcno *.info *.gcda

RUN_OUT = ./a.out
OS := $(shell uname)

WFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
LFLAGS = -lm -lpthread -lcheck
DFLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --quiet --leak-check=full --track-origins=yes --trace-children=yes

ifeq ($(shell uname), Linux)
LFLAGS = -lcheck -lsubunit -lm -lrt -lpthread
endif

QQQ = qmake

COPY = MyCalc.app/Contents/MacOS/MyCalc ../build

ifeq ($(shell uname), Linux)
COPY = MyCalc ../build
endif

all: clean install

install:
	mkdir build
	cd calc && $(QQQ) && make && mv $(COPY) && cd ..

uninstall:
	make -C calc/ uninstall
	make -C calc/ distclean
	rm -rf build

dist:
	if [ ! -e build ]; then make install ; fi
	@if [ -e Archive_Calc_v1.0 ]; then rm -rf Archive_Calc_v1.0 ; fi
	mkdir Archive_Calc_v1.0
	mkdir Archive_Calc_v1.0/src
	mv ./build/MyCalc Archive_Calc_v1.0/src/
	tar cvzf Archive_Calc_v1.0.tgz Archive_Calc_v1.0/
	rm -rf Archive_Calc_v1.0/

dvi:
	open description.txt

clean:
	@if [ -e Archive_Calc_v1.0 ]; then rm -rf Archive_Calc_v1.0 ; fi
	@if [ -e build ]; then rm -rf build ; fi
	@if [ -e calc/Makefile ]; then rm calc/Makefile ; fi
	$(RM) $(ALLEX)

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

style:
	cp ../materials/linters/.clang-format .
	cp ../materials/linters/.clang-format ./tests
	cp ../materials/linters/.clang-format ./calc/
	clang-format -n *.c *.h tests/*.c tests/*.h calc/*.cpp calc/*.h
	rm .clang-format tests/.clang-format calc/.clang-format

leak: test
	leaks -atExit -- ./a.out

valgrind: valgrind_build

valgrind_build: $(ARCHIVE)
	$(CC) $(TESTS) -g
	$(C) $(OBJ) -L. $(ARCHIVE) $(LFLAGS)
	$(RM) $(OBJ)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./a.out
