#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

void initializeGame();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
void freeGameResources();

#endif // TETRIS_H