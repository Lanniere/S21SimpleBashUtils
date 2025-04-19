# Компилятор и флаги
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
LDFLAGS = -lncurses

# Имя исполняемого файла
TARGET = brickgame-tetris

# Директории
BUILD_DIR = build

# Исходные файлы
TETRIS_SRCS = brick_game/tetris/src/tetris.c \
              brick_game/tetris/src/figures.c \
              brick_game/tetris/src/game_logic.c \
              brick_game/tetris/src/state_machine.c

CLI_SRCS = gui/cli/src/cli.c \
           gui/cli/src/main.c

# Объектные файлы
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(TETRIS_SRCS) $(CLI_SRCS))

# Пути к заголовкам
INCLUDES = -Ibrick_game/tetris/include \
           -Igui/cli/include

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET)

# Сборка исполняемого файла
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $^ $(LDFLAGS) -o $@

# Правило для сборки объектных файлов
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)