#include "state_machine.h"
#include "figures.h"
#include "game_logic.h"
#include <stdlib.h>
#include <time.h>

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

static GameState current_state = START_STATE;
static int game_field[FIELD_HEIGHT][FIELD_WIDTH] = {0};
static int next_figure[4][4] = {0};
static int current_figure[4][4] = {0};
static int current_x = 0, current_y = 0;
static bool paused = false;
static bool game_over = false;

void initGameState() {
    srand(time(NULL));
    memset(game_field, 0, sizeof(game_field));
    getRandomFigure(next_figure);
    current_state = START_STATE;
    paused = false;
    game_over = false;
}

void updateGameState() {
    if (paused || game_over) return;
    
    switch (current_state) {
        case SPAWN_STATE:
            memcpy(current_figure, next_figure, sizeof(current_figure));
            getRandomFigure(next_figure);
            current_x = FIELD_WIDTH / 2 - 2;
            current_y = -1;
            
            if (checkCollision(game_field, current_figure, current_x, current_y)) {
                current_state = GAME_OVER_STATE;
            } else {
                current_state = MOVING_STATE;
            }
            break;
            
        case SHIFTING_STATE:
            current_y++;
            if (checkCollision(game_field, current_figure, current_x, current_y)) {
                current_state = ATTACHING_STATE;
            } else {
                current_state = MOVING_STATE;
            }
            break;
            
        case ATTACHING_STATE:
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (current_figure[i][j]) {
                        int y = current_y + i;
                        int x = current_x + j;
                        if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
                            game_field[y][x] = 1;
                        }
                    }
                }
            }
            
            int lines_cleared = checkLines(game_field);
            if (lines_cleared > 0) {
                updateScore(lines_cleared);
            }
            
            current_state = SPAWN_STATE;
            break;
            
        default:
            break;
    }
}

void freeGameState() {
    // Освобождаем ресурсы, если они были выделены
}

void handleStart() {
    if (current_state == START_STATE || current_state == GAME_OVER_STATE) {
        initGameState();
        current_state = SPAWN_STATE;
    } else if (current_state == MOVING_STATE || current_state == SHIFTING_STATE) {
        paused = !paused;
    }
}

void handlePause() {
    if (current_state == MOVING_STATE || current_state == SHIFTING_STATE) {
        paused = !paused;
    }
}

void handleTerminate() {
    game_over = true;
    current_state = GAME_OVER_STATE;
}

void handleLeft() {
    if (current_state == MOVING_STATE && !paused) {
        if (!checkCollision(game_field, current_figure, current_x - 1, current_y)) {
            current_x--;
        }
    }
}

void handleRight() {
    if (current_state == MOVING_STATE && !paused) {
        if (!checkCollision(game_field, current_figure, current_x + 1, current_y)) {
            current_x++;
        }
    }
}

void handleDown() {
    if (current_state == MOVING_STATE && !paused) {
        current_state = SHIFTING_STATE;
    }
}

void handleRotate() {
    if (current_state == MOVING_STATE && !paused) {
        int temp[4][4];
        memcpy(temp, current_figure, sizeof(temp));
        rotateFigure(temp);
        
        if (!checkCollision(game_field, temp, current_x, current_y)) {
            memcpy(current_figure, temp, sizeof(current_figure));
        }
    }
}

int** getCurrentField() {
    static int field_copy[FIELD_HEIGHT][FIELD_WIDTH];
    memcpy(field_copy, game_field, sizeof(field_copy));
    
    if (current_state == MOVING_STATE || current_state == SHIFTING_STATE) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (current_figure[i][j]) {
                    int y = current_y + i;
                    int x = current_x + j;
                    if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
                        field_copy[y][x] = 2; // 2 для текущей фигуры
                    }
                }
            }
        }
    }
    
    return (int**)field_copy;
}

int** getNextFigure() {
    return (int**)next_figure;
}

int getCurrentScore() {
    // Реализация должна возвращать текущий счет из game_logic.c
    return 0;
}

int getHighScore() {
    return high_score;
}

int getCurrentLevel() {
    // Реализация должна возвращать текущий уровень из game_logic.c
    return 0;
}

int getCurrentSpeed() {
    // Реализация должна возвращать текущую скорость
    return 1000 - (getCurrentLevel() * 100);
}

bool isGamePaused() {
    return paused;
}