CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC = \
	brick_game/tetris/s21_tetric.c \
	brick_game/tetris/main.c \
	brick_game/tetris/shapes_figure.c

OBJ = $(SRC:.c=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
