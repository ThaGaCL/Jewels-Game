#include "allegroMouse.h"

void mouse_init()
{
    mustInit(al_install_mouse(), "mouse");
    mustInit(al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT), "mouse cursor");
}

int mouse_on_jewel(MATRIX** m, ALLEGRO_EVENT event, int x, int y    )
{
    for(int i = 0; i < MATRIX_SIZE; i++)
    {
        for(int j = 0; j < MATRIX_SIZE; j++)
        {
            if(m[i][j].x <= x && x<= m[i][j].x + 64)
            {
                if(m[i][j].y <= y && y <= m[i][j].y + 64)
                {
                    m[i][j].select[0] = 1;
                    return 1;
                }
                else
                {
                    m[i][j].select[0] = 0;
                    return 0;
                }
            }
        }
    }
    return 0;
}

void mouse_deinit()
{
    al_uninstall_mouse();
}