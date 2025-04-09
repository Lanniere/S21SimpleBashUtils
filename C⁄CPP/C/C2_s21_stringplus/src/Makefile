CC = gcc
CCFLAGS = -Wall -Wextra -Wextra -std=c11
LDFLAGS = -lcheck -lsubunit -lm
RM = rm -rf
BRANCHES = --rc lcov_branch_coverage=1


# Используйте LCOV для генерации отчетов
LCOV = $(shell which lcov || echo ~/.local/bin/lcov)
GHTML = $(shell which genhtml || echo ~/.local/bin/genhtml)

# Имя библиотеки
LIB_NAME = s21_string.a
# Имя тестового файла
TESTS_NAME = s21_string_test
# Имя тестового файла с тестами покрытия кода LCOV
TESTS_LCOV_NAME = s21_string_tests_gcov

# Файлы и директории функций библиотек
DIR = s21_string/
HEADER_NAME = s21_string.h
SOURCES = $(shell find $(DIR) -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

# Файлы и директории тестов
TEST_DIR = tests/
TEST_HEADER_NAME := s21_tests.h
TEST_SRC = $(shell find $(TEST_DIR) -name "*.c")
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all test gcov_report s21_string.a

all: $(LIB_NAME)

$(LIB_NAME): $(OBJECTS)
	ar rc $@ $^
	ranlib $@

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

test: clean $(TESTS_NAME)
	./$(TESTS_NAME)

$(TESTS_NAME): $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CCFLAGS) $^ -L. -L/usr/local/lib -L/usr/include -l:$(LIB_NAME) -o $@ $(LDFLAGS)

gcov_report: clean
	$(CC) $(CCFLAGS) --coverage $(TEST_SRC) $(SOURCES) $(LDFLAGS) -o $(TESTS_LCOV_NAME)
	./$(TESTS_LCOV_NAME)
	$(LCOV) -t "$(TESTS_LCOV_NAME)" -o test.info -c -d . $(BRANCHES)
	$(LCOV) --remove test.info '*/tests/*' --output-file test.info $(BRANCHES)
	$(GHTML) -o report test.info $(BRANCHES)
	open report/index.html

clean: clean_lcov clean_report
	$(RM) $(TESTS_NAME)
	$(RM) $(LIB_NAME)
	$(RM) $(OBJECTS)
	$(RM) $(TEST_OBJ)

clean_report:
	$(RM) report

clean_lcov:
	$(RM) $(TESTS_LCOV_NAME)
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) test.info

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(DIR)*.c *.h
	clang-format -n $(TEST_DIR)*.c $(TEST_DIR)*.h
	$(RM) .clang-format

val: clean $(TESTS_NAME)
	valgrind --tool=memcheck --leak-check=yes --quiet ./$(TESTS_NAME)
