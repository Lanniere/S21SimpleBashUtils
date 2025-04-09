CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lm
LDFLAGS = -lcheck -lsubunit -lgcov
BRANCHES = --rc lcov_branch_coverage=1
AR = ar rcs
LIBNAME = s21_matrix.a

LCOV = $(shell which lcov || echo ~/.local/bin/lcov)
GHTML = $(shell which genhtml || echo ~/.local/bin/genhtml)


FOLDERS := function_matrix
SRC = $(foreach dir,$(FOLDERS),$(wildcard $(dir)/*.c))
OBJ= $(patsubst %.c, %.o,$(SRC))

TESTFOLDER = tests
TESTFILES = $(wildcard $(TESTFOLDER)/*.c)


all: clean $(LIBNAME)

$(LIBNAME): $(OBJ)
	@$(AR) $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ $(LIBS)

test: clean $(LIBNAME)
	$(CC) $(FLAGS) $(TESTFILES) $(LIBNAME) -o test $(LDFLAGS) $(LIBS)
	./test

gcov_report: FLAGS+= --coverage -fprofile-arcs -ftest-coverage 
gcov_report: clean test
	$(LCOV) --capture -o test.info -d . $(BRANCHES)
	lcov --remove test.info '*/tests/*' --output-file test.info $(BRANCHES)
	$(GHTML) test.info  -o report $(BRANCHES)
	open report/index.html

clang-i:
	cp ../materials/build/scripts/.clang-format .clang-format
	clang-format -i $(shell find . -name '*.c' -or -name '*.h')

clang-n:
	clear
	cp ../materials/build/scripts/.clang-format .clang-format
	clang-format -n $(shell find . -name '*.c' -or -name '*.h')
	
valgrind-test:
	clear
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=definite,possible --quiet ./test

.PHONY: clean

clean:
	rm -f test .clang-format 1 $(LIBNAME) *.o */*.o *.gcda *.gcno */*.gcda */*.gcno
	rm -rf report test.info
	clear
