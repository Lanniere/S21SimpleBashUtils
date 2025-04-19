#include "game_logic.h"
#include <string.h>
#include <stdio.h>

bool checkCollision(int field[20][10], int figure[4][4], int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (figure[i][j]) {
                int fieldX = x + j;
                int fieldY = y + i;
                if (fieldX < 0 || fieldX >= 10 || fieldY >= 20 || 
                    (fieldY >= 0 && field[fieldY][fieldX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

int checkLines(int field[20][10]) {
    int lines_cleared = 0;
    for (int y = 19; y >= 0; y--) {
        bool line_full = true;
        for (int x = 0; x < 10; x++) {
            if (!field[y][x]) {
                line_full = false;
                break;
            }
        }
        
        if (line_full) {
            lines_cleared++;
            for (int ny = y; ny > 0; ny--) {
                memcpy(field[ny], field[ny-1], sizeof(int)*10);
            }
            memset(field[0], 0, sizeof(int)*10);
            y++;
        }
    }
    return lines_cleared;
}

void updateScore(int lines_cleared) {
    static const int SCORE_TABLE[] = {0, 100, 300, 700, 1500};
    static int current_score = 0;
    static int level_up_counter = 0;
    static int current_level = 0;
    
    if (lines_cleared >= 1 && lines_cleared <= 4) {
        current_score += SCORE_TABLE[lines_cleared] * (current_level + 1);
        
        if (current_score > high_score) {
            high_score = current_score;
            saveHighScore();
        }
        
        level_up_counter += lines_cleared;
        if (level_up_counter >= 6 && current_level < 10) {
            current_level++;
            level_up_counter = 0;
        }
    }
}

void saveHighScore() {
    FILE *file = fopen("assets/highscore.dat", "wb");
    if (file) {
        fwrite(&high_score, sizeof(int), 1, file);
        fclose(file);
    }
}

void loadHighScore() {
    FILE *file = fopen("assets/highscore.dat", "rb");
    if (file) {
        fread(&high_score, sizeof(int), 1, file);
        fclose(file);
    }
}