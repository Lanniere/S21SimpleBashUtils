CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
LDFLAGS = -lgtest

TEMPLATES = $(wildcard */*/*.h) $(wildcard */*/*.tpp) $(wildcard */*.h) $(wildcard */*.tpp) $(wildcard *.h)

SRC = $(wildcard tests/*.cc)

all: test

test: clean
	@$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)
	@./$@

clean:
	@rm -rf test
clang-i:
	clang-format -i -style=google $(TEMPLATES) $(SRC)