#include "tetris.h"
#include "state_machine.h"
#include "game_logic.h"
#include "figures.h"
#include <stdlib.h>

static GameInfo_t game_info;
static bool initialized = false;

void initializeGame() {
    if (!initialized) {
        initGameState();
        loadHighScore();
        initialized = true;
    }
}

void userInput(UserAction_t action, bool hold) {
    if (hold) return;
    
    switch (action) {
        case Start: handleStart(); break;
        case Pause: handlePause(); break;
        case Terminate: handleTerminate(); break;
        case Left: handleLeft(); break;
        case Right: handleRight(); break;
        case Down: handleDown(); break;
        case Up: break; // Не используется
        case Action: handleRotate(); break;
    }
}

GameInfo_t updateCurrentState() {
    updateGameState();
    
    game_info.field = getCurrentField();
    game_info.next = getNextFigure();
    game_info.score = getCurrentScore();
    game_info.high_score = getHighScore();
    game_info.level = getCurrentLevel();
    game_info.speed = getCurrentSpeed();
    game_info.pause = isGamePaused();
    
    return game_info;
}

void freeGameResources() {
    freeGameState();
    initialized = false;
}