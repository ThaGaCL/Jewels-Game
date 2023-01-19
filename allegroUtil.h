#ifndef ALLEGRO_UTIL_H
#define ALLEGRO_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


// Inicializa modulos e addons do allegro
void mustInit(bool test, const char *description);

// Inicializa o allegro 
void initAllegro();

#endif
