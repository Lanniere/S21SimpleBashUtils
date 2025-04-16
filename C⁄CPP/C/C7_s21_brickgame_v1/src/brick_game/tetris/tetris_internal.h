#include "../../include/s21_tetris.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int shape [4][4];   // матрица фигуры
    int type;           // тип фигуры
    int rotate;         // поворот фигуры
}Tetramino;

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER
}FSMState;

typedef struct {
    int **field;                                 // поле
    int x, y;                                    // координаты
    int score;                                   // текущий счёт
    int high_score;                              // рекорд
    int level;                                   // текущий уровень
    int speed;                                   // скорость
    Tetramino current_piece;                     // текущая фигура
    Tetramino next_piece;                        // след фигура
    FSMState state;                              // состояние игры
    bool pause;                                  // пауза
}GameState;

Tetramino randomGenerationShape();
void initGameState();
