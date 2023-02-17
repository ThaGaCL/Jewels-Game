#ifndef ALLEGRO_SPRITES_H
#define ALLEGRO_SPRITES_H

#include "allegroUtil.h"


typedef struct SPRITES
{
    ALLEGRO_BITMAP* _sheet;

    // Sprites do jogador
    ALLEGRO_BITMAP* green;
    ALLEGRO_BITMAP* blue;
    ALLEGRO_BITMAP* red;
    ALLEGRO_BITMAP* yellow;
    ALLEGRO_BITMAP* purple;
    ALLEGRO_BITMAP* glitch;

} SPRITES;

extern SPRITES sprites;

// Pega os sprites da spritesheet
ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h);

// Inicializa o Bitmap dos sprites
void sprites_init();

// Libera o Bitmap dos sprites
void sprites_deinit();

#endif