#include "allegroUtil.h"

#ifndef ALLEGRO_KEYBOARD_H
#define ALLEGRO_KEYBOARD_H

#define KEY_SEEN 1
#define KEY_RELEASED 2

extern unsigned char key[ALLEGRO_KEY_MAX];
// Aloca a memoria para todas as teclas
void keyboard_init();

// Atualiza o teclado
void keyboard_update(ALLEGRO_EVENT* event);


#endif