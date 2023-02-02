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

void disp_pre_draw(bool easteregg)
{
    int bg_r = 23;
    int bg_g = 23;
    int bg_b = 23;
    
    if(easteregg)
    {
        bg_r = 252;
        bg_g = 250;
        bg_b = 247;
    }

    al_set_target_bitmap(al_get_backbuffer(disp));
    al_clear_to_color(al_map_rgb(bg_r, bg_g, bg_b));
}

void disp_post_draw()
{
    al_set_target_backbuffer(disp);

    al_flip_display();
}