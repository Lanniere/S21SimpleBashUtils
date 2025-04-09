CC = gcc
TFLAGS =-Wall -Werror -Wextra -std=c11 
FLAGS = -Wall -Werror -Wextra -std=c11 -c 
LDFLAGS = -lcheck -lsubunit -lgcov
AR = ar rcs
LIBS = -lm
BRANCHES = --rc lcov_branch_coverage=1
LIBNAME = s21_decimal.a
TESTS_LCOV_NAME = s21_decimal_tests_gcov

LCOV = $(shell which lcov || echo ~/.local/bin/lcov)
GHTML = $(shell which genhtml || echo ~/.local/bin/genhtml)

FOLDERS := . compare convert arifmetic other_functions
SRC = $(foreach dir,$(FOLDERS),$(wildcard $(dir)/*.c))
OBJ= $(patsubst %.c, %.o,$(SRC))

TESTFOLDER = tests
TESTFILES = $(wildcard $(TESTFOLDER)/*.c)

all: clean $(LIBNAME)

$(LIBNAME): $(OBJ)
	@$(AR) $@ $^

%.o: %.c
	$(CC) $(FLAGS) $< -o $@ $(LIBS)


decimal:
	$(CC) $(CFLAGS) ./arifmetic/*.c ./compare/*.c other_functions/*.c ./*.c -o 1 -g -lm 

test: clean $(LIBNAME)
	$(CC) $(TFLAGS) $(TESTFILES) $(LIBNAME) -o test $(LDFLAGS) $(LIBS)
	./test

gcov_report: FLAGS+= --coverage -fprofile-arcs -ftest-coverage 
gcov_report: clean test
	$(LCOV) --capture -o test.info -d . $(BRANCHES)
	$(GHTML) test.info  -o report $(BRANCHES)
	open report/index.html

clang-i:
	cp ../materials/linters/.clang-format ./
	@clang-format -i $(shell find . -name '*.c' -or -name '*.h')

clang-n:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(shell find . -name '*.c' -or -name '*.h')

valgrind-test:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=definite,possible ./test

cppcheck:
	cppcheck cppcheck --enable=all --suppress=missingIncludeSystem ../src

.PHONY: clean

clean:
	rm -f $(OBJ) $(LIBNAME) test .clang-format 1 arifmetic/*.gc* compare/*.gc* convert/*.gc* other_functions/*.gc*
	rm -rf test.info *.gcda *.gcno test_coverage coverage_report report temp.info s21_decimal_tests_gcov
