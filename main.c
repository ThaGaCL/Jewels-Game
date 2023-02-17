#include "allegroDisplay.h"
#include "allegroUtil.h"
#include "jewelsLib.h"
#include "allegroSprites.h"
#include "allegroMouse.h"
#include "allegroKeyboard.h"
#include "allegroAudio.h"

int main()
{
    srand(time(0));

    // Inicializa o Allegro e seus addons
    mustInit(al_init(), "allegro");
    mustInit(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    mustInit(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    mustInit(queue, "queue");

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

    // Inicializa a matriz/tabuleiro
    MATRIX **matrix = matrix_init(10);

    int pos_x, pos_y; // Posicao do mouse
    int pos1[2], pos2[2]; // Posicao dos blocos selecionados

    frames = 0;
    score = 0;

    bool easteregg = false;
    bool menu = true;
    bool done = false;
    bool help = false;
    bool redraw = true;
    bool rank = false;
    bool click = false;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:

            // Verifica qual tela será exibida com base no que for pressionado no teclado
            if (key[ALLEGRO_KEY_ESCAPE])
                menu = true;

            if (menu && key[ALLEGRO_KEY_S])
            {
                done = true;
            }
            else if (menu && key[ALLEGRO_KEY_A])
            {
                help = true;
            }
            else if (menu && key[ALLEGRO_KEY_R])
            {
                rank = true;
                menu = false;
            }

            if (help && key[ALLEGRO_KEY_V])
            {
                help = false;
            }

            if (rank && key[ALLEGRO_KEY_V])
            {
                rank = false;
                menu = true;
            }

            if (key[ALLEGRO_KEY_J])
            {
                menu = false;
            }

            if (key[ALLEGRO_KEY_F1] || key[ALLEGRO_KEY_H])
                help = true;

            // A tecla E ativa o Easter Egg 
            if (key[ALLEGRO_KEY_E])
                easteregg = !easteregg;

            redraw = true;
            frames++;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            // Atualiza a posicao do mouse
            pos_x = event.mouse.x;
            pos_y = event.mouse.y;

            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            // Atualiza a posicao do mouse
            pos_x = event.mouse.x;
            pos_y = event.mouse.y;
            
            // Avisa que o mouse foi pressionado
            click = true;
        }

        if (done)
            break;

        keyboard_update(&event);

        // Verifica se existe um combo na matriz
        is_combo(matrix);


        // Se o mouse foi pressionado, roda o loop principal do jogo
        if (click)
        {
            main_game_loop(matrix, pos1, pos2, pos_x, pos_y);
            click = false;
        }

        if (easteregg)
        {
            printf("Segmentation fault (core dumped)\n");
            score += 2000 * level;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            disp_pre_draw(easteregg);
            if (help)
            {
                help_draw(easteregg);
            }
            else if (menu)
            {
                menu_draw(easteregg);
            }
            else if (rank)
            {
                rank_draw(easteregg);
            }
            else
            {
                hud_draw(pos_x, pos_y, easteregg);
                if ((easteregg) && (frames % 2 == 0))
                    matrix_draw(matrix);
                else if (!easteregg)
                    matrix_draw(matrix);
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
