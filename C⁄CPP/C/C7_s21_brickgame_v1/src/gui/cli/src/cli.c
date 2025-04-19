#include "cli.h"
#include "../brick_game/tetris/include/tetris.h"
#include <ncurses.h>
#include <unistd.h>

void initGUI() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(100);
    curs_set(0);
}

void drawGame(const void *game_info_ptr) {
    const GameInfo_t *game_info = (const GameInfo_t *)game_info_ptr;
    clear();
    
    // Рисуем игровое поле
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            if (game_info->field[y][x] == 1) {
                mvprintw(y, x*2, "[]");
            } else if (game_info->field[y][x] == 2) {
                mvprintw(y, x*2, "::");
            }
        }
    }
    
    // Боковая панель
    mvprintw(2, 25, "Score: %d", game_info->score);
    mvprintw(4, 25, "High Score: %d", game_info->high_score);
    mvprintw(6, 25, "Level: %d", game_info->level);
    mvprintw(8, 25, "Speed: %d", game_info->speed);
    
    // Следующая фигура
    mvprintw(10, 25, "Next:");
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (game_info->next[y][x]) {
                mvprintw(12 + y, 25 + x*2, "[]");
            }
        }
    }
    
    // Состояние игры
    if (game_info->pause) {
        mvprintw(18, 25, "PAUSED");
    }
    
    refresh();
}

void handleInput() {
    int ch = getch();
    bool hold = false;
    
    switch (ch) {
        case 's': userInput(Start, hold); break;
        case 'p': userInput(Pause, hold); break;
        case 'q': userInput(Terminate, hold); break;
        case KEY_LEFT: userInput(Left, hold); break;
        case KEY_RIGHT: userInput(Right, hold); break;
        case KEY_DOWN: userInput(Down, hold); break;
        case KEY_UP: userInput(Action, hold); break;
    }
}

void closeGUI() {
    endwin();
}