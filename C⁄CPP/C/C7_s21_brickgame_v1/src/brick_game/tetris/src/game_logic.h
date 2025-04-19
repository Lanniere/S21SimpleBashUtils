#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>
static int high_score = 0;

bool checkCollision(int field[20][10], int figure[4][4], int x, int y);
int checkLines(int field[20][10]);
void updateScore(int lines_cleared);
void saveHighScore();
void loadHighScore();

#endif // GAME_LOGIC_H