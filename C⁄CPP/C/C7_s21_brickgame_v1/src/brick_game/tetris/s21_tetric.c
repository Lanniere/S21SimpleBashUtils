#include "tetris_internal.h"
#include "shapes_figure.h"

static GameState current_state;

void initGameState(){

    /*Инициализация игрового поля*/
    current_state.field = malloc(FIELD_ROWS * sizeof(int*));

    for (int i = 0; i < FIELD_ROWS; i++) {
        current_state.field[i] = calloc(FIELD_COLS, sizeof(int));
    }
    
    /*Заполение остальных данных игры*/
    current_state.score = 0;
    current_state.level = 0;
    current_state.speed = 500;
    current_state.pause = false;
    current_state.state = STATE_MENU;

    current_state.x = FIELD_COLS / 2 - 2;
    current_state.y = 0;

    current_state.current_piece = randomGenerationShape();
    current_state.next_piece = randomGenerationShape();
}

/*Генерация первой фигуры*/
Tetramino randomGenerationShape(){
    Tetramino t;
    t.type = rand() % TETRAMINO_FIGURES;
    t.rotate = 0;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            t.shape[i][j] = TETRAMINO_SHAPES[t.type][i][j];
        }
    }
    return t;
}

// Обработка пользовательского ввода
void userInput(UserAction_t action, bool hold){
    if(current_state.state == STATE_MENU || current_state.state == STATE_PLAYING) {
        if(action == Start){
            initGameState();
            current_state.state = STATE_PLAYING;
        }
    }
    else if (current_state.state == STATE_PLAYING){
        if(action == Pause){
            current_state.pause = !current_state.pause;
        }
    }
    if(!current_state.pause){
        switch(action){
            case Left:
                current_state.x++;
                break;
            case Right:
                current_state.x--;
                break;
            case Down:
                current_state.y++;
                break;
            case Action:
                /*функция вращения фигуры*/
                break;
            default:
                break;
        }
    }
}
