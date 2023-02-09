#ifndef ASTEROIDS_LIB_H
#define ASTEROIDS_LIB_H

#include "allegroUtil.h"
#include "allegroSprites.h"
#include "allegroAudio.h"
#include "allegroKeyboard.h"
#include "allegroDisplay.h"
#include "allegroMouse.h"

#define MATRIX_SIZE 10


extern long frames;
extern long score;
extern long score_display;

typedef enum Jtype
{
    GREEN,
    BLUE,
    RED,
    YELLOW,
    PURPLE,
    TYPE_NULL,
} Jtype;

typedef struct MATRIX
{
    int x, y;
    Jtype type;
    int select[2];    /* data */
}MATRIX;



// Gera um Int aleatorio entre a e b
int between(int min, int max);

// Gera um Float aleatorio entre a e b
float betweenF(float min, float max);


MATRIX** matrix_init(int size);

void matrix_deinit(MATRIX** m, int size);

void matrix_draw(MATRIX** matrix);

void hud_init();

void hud_deinit();

void hud_update();

void hud_draw(int x, int y, bool easteregg);

void help_draw(bool easteregg);

void menu_draw(bool easteregg);

void rank_draw(bool easteregg);

void swap_jewels(MATRIX** matrix, int* pos1, int* pos2);

void main_game_loop(MATRIX** matrix, int* pos1, int* pos2, int pos_x, int pos_y);

int mouse_on_jewel(MATRIX** m, int* pos, int x, int y);

void matrix_swap(MATRIX** m, int i, int j);


#endif
