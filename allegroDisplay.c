#include "allegroDisplay.h"

ALLEGRO_DISPLAY *disp;

void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    disp = al_create_display(DISP_W, DISP_H);
    mustInit(disp, "display");

    al_set_window_title(disp, "Jewels");


}


void disp_deinit()
{
    al_destroy_display(disp);
}

void disp_pre_draw()
{

}

void disp_post_draw()
{
    al_set_target_backbuffer(disp);

    al_flip_display();
}