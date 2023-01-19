#include "allegroSprites.h"

SPRITES sprites;

const int ALIEN_W[] = {14,13,45};
const int ALIEN_H[] = {9,10,27};


// Inicializa o Bitmap dos sprites
void sprites_init()
{
    sprites.green = al_load_bitmap("assets/sprites/real.png");
    mustInit(sprites.green, "spritesheet");
    sprites.blue = al_load_bitmap("assets/sprites/hashtag.png");
    mustInit(sprites.blue, "spritesheet");
    sprites.red = al_load_bitmap("assets/sprites/arroba.png");
    mustInit(sprites.red, "spritesheet");
    sprites.yellow = al_load_bitmap("assets/sprites/copy.png");
    mustInit(sprites.yellow, "spritesheet");
    sprites.purple = al_load_bitmap("assets/sprites/sdiferenciado.png");
    mustInit(sprites.purple, "spritesheet");

}  

// Libera o Bitmap dos sprites
void sprites_deinit()
{
    al_destroy_bitmap(sprites._sheet);
    al_destroy_bitmap(sprites.green);
    al_destroy_bitmap(sprites.blue);
    al_destroy_bitmap(sprites.red);
    al_destroy_bitmap(sprites.yellow);
    al_destroy_bitmap(sprites.purple);


}