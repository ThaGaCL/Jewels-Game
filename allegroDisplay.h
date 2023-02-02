#include "allegroUtil.h"

#ifndef ALLEGRO_DISPLAY_H 
#define ALLEGRO_DISPLAY_H

#define DISP_W 720
#define DISP_H 400

extern ALLEGRO_DISPLAY* disp;

// Inicializa o display
void disp_init();

// Desaloca o display
void disp_deinit();

// Limpa o buffer
void disp_pre_draw(bool easteregg);

// Desenha o buffer na tela
void disp_post_draw();



#endif