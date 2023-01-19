#include "allegroUtil.h"

#ifndef ALLEGRO_DISPLAY_H 
#define ALLEGRO_DISPLAY_H

#define BUFFER_W 580
#define BUFFER_H 340

#define DISP_SCALE 2
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buffer;

// Inicializa o display
void disp_init();

// Desaloca o display
void disp_deinit();

// Limpa o buffer
void disp_pre_draw();

// Desenha o buffer na tela
void disp_post_draw();

#endif