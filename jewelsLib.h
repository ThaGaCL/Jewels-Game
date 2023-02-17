#ifndef ASTEROIDS_LIB_H
#define ASTEROIDS_LIB_H

#include "allegroUtil.h"
#include "allegroSprites.h"
#include "allegroAudio.h"
#include "allegroKeyboard.h"
#include "allegroDisplay.h"
#include "allegroMouse.h"
#include "libscore.h"

#define MATRIX_SIZE 10


extern long frames;
extern long score;
extern long score_display;
extern long level;

typedef enum Jtype
{
    GREEN,
    BLUE,
    RED,
    YELLOW,
    PURPLE,
    TYPE_NULL,
    GLITCH,
} Jtype;

typedef struct MATRIX
{
    int x, y;
    Jtype type;
    int select[2];    /* data */
}MATRIX;


// Inicializa as peças do jogo
MATRIX** matrix_init(int size);

// Libera a memoria alocada para a matriz
void matrix_deinit(MATRIX** m, int size);

// Desenha a matriz
void matrix_draw(MATRIX** matrix);

void hud_init();

void hud_deinit();

// Desenha o HUD
void hud_draw(int x, int y, bool easteregg);

// Desenha a tela de ajuda
void help_draw(bool easteregg);

// Desenha a tela de menu
void menu_draw(bool easteregg);

// Desenha a tela de ranking
void rank_draw(bool easteregg);

// Troca as jewels de posição
void swap_jewels(MATRIX** matrix, int* pos1, int* pos2);

// Loop principal do jogo
void main_game_loop(MATRIX** matrix, int* pos1, int* pos2, int pos_x, int pos_y);

// Verifica se a jewel selecionada é valida
int mouse_on_jewel(MATRIX** m, int* pos, int x, int y);

// Substitui as jewels que foram destruidas
void replace_jewels_row(MATRIX** m, int i, int j);

// Procura por combinações de 3 jewels na matriz
int is_combo(MATRIX **m);

#endif
