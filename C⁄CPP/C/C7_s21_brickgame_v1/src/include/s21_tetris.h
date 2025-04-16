#ifndef TETRIS_H
#define TETRIS_H

#define FIELD_ROWS 20
#define FIELD_COLS 10

#include <stdbool.h>

/*кнопки в консоли*/
typedef enum {
    Start,      // Начать игру
    Pause,      // Пауза/продолжить
    Terminate,  // Завершить
    Left,       // Влево
    Right,      // Вправо
    Up,         // Пока не использую
    Down,       // Вниз
    Action      // Вращение
} UserAction_t;

/*Это — основа взаимодействия. Внутри интерфейса будет вызываться updateCurrentState() → возвращается структура GameInfo_t, содержащая:*/
typedef struct {
    int **field;  // 20 строк x 10 колонок (поле)
    int **next;     // следующая фигура
    int score;          // текущий счёт
    int high_score;     // рекорд
    int level;          // текущий уровень
    int speed;          // текущая скорость падения
    int pause;          // 1 = пауза, 0 = игра идёт
} GameInfo_t;

// Обработка пользовательского ввода
void userInput(UserAction_t action, bool hold);

// Получение текущего состояния игры
GameInfo_t updateCurrentState();

#endif // TETRIS_H