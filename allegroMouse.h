#ifndef ALLEGRO_MOUSE_H
#define ALLEGRO_MOUSE_H

#include "allegroUtil.h"
#include "allegroDisplay.h"
#include "jewelsLib.h"

void mouse_init();
int mouse_on_jewel(MATRIX** m, int x, int y);
void mouse_deinit();

#endif