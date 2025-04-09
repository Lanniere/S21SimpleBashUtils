CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

PROJECT_NAME = s21_cat

all: $(PROJECT_NAME)

$(PROJECT_NAME):
	$(CC) $(CFLAGS) $(PROJECT_NAME).c -o $(PROJECT_NAME)
	
test1: clean $(PROJECT_NAME)
	bash tests.sh

test2: clean $(PROJECT_NAME)
	bash test_leaks.sh

clean:
	rm -rf $(PROJECT_NAME) s21_cat.log