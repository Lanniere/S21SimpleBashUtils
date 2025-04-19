#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum {
    START_STATE,
    SPAWN_STATE,
    MOVING_STATE,
    SHIFTING_STATE,
    ATTACHING_STATE,
    GAME_OVER_STATE
} GameState;

void initGameState();
void updateGameState();
void freeGameState();
void handleStart();
void handlePause();
void handleTerminate();
void handleLeft();
void handleRight();
void handleDown();
void handleRotate();
int** getCurrentField();
int** getNextFigure();
int getCurrentScore();
int getHighScore();
int getCurrentLevel();
int getCurrentSpeed();
bool isGamePaused();

#endif // STATE_MACHINE_H