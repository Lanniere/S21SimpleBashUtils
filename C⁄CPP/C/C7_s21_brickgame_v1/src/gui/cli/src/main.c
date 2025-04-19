#include "../include/cli.h"
#include "../../brick_game/tetris/include/tetris.h"
#include <unistd.h>

int main() {
    initializeGame();
    initGUI();
    
    while (1) {
        handleInput();
        GameInfo_t game_info = updateCurrentState();
        drawGame(&game_info);
        
        if (game_info.pause == 1) {
            usleep(500000);
        } else {
            usleep(game_info.speed * 1000);
        }
    }
    
    closeGUI();
    freeGameResources();
    return 0;
}
