#include "allegroDisplay.h"
#include "allegroUtil.h"
#include "jewelsLib.h"
#include "allegroSprites.h"
#include "allegroMouse.h"
#include "allegroKeyboard.h"
#include "allegroAudio.h"

int main(){
    srand(time(0));
    mustInit(al_init(), "allegro");
    mustInit(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    mustInit(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    mustInit(queue, "queue");

    MATRIX** matrix = matrix_init(10);
    disp_init();

    mouse_init();

    audio_init();

    mustInit(al_init_image_addon(), "image");
    sprites_init();

    hud_init();

    mustInit(al_init_primitives_addon(), "primitives");

    mustInit(al_install_audio(), "audio");
    mustInit(al_init_acodec_addon(), "audio codecs");
    mustInit(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    keyboard_init();

    int pos_x, pos_y;
    frames = 0;
    score = 0;

    bool menu = false;
    bool done = false;
    bool help = false;
    bool redraw = true;
    bool click = false;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while(1)
    {
        al_wait_for_event(queue, &event);
        
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:


                if(key[ALLEGRO_KEY_ESCAPE]){
                    menu = !menu;
                }

                if(key[ALLEGRO_KEY_F1]||key[ALLEGRO_KEY_H])
                    help = true;


                redraw = true;
                frames++;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                pos_x = event.mouse.x;
                pos_y = event.mouse.y;    
                
                break;
            
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                pos_x = event.mouse.x;
                pos_y = event.mouse.y;

                click = true;
    
        }

        if(done)
            break;

        keyboard_update(&event);

        if((mouse_on_jewel(matrix, pos_x, pos_y))&&(click)){
            printf("click\n");
            click = false;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(23,23,23));
            if(help){
                help_draw();
                help = false;
            }
            else if(menu){
                menu_draw();
            }
            else{
                hud_draw(pos_x, pos_y);
                matrix_draw(matrix);
                // al_draw_filled_rectangle(pos_x - 15, pos_y - 15, pos_x + 15, pos_y + 15, al_map_rgb(255, 0, 255));
            }
            disp_post_draw();
            redraw = false;
        }
    }

    mouse_deinit();
    sprites_deinit();
    hud_deinit();
    audio_deinit();
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

     return 0;

}