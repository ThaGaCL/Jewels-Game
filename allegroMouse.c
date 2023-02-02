#include "allegroMouse.h"

void mouse_init()
{
    mustInit(al_install_mouse(), "mouse");
    mustInit(al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT), "mouse cursor");
}

int mouse_on_jewel(MATRIX** m, int* pos, int x, int y)
{
    // Checa se o mouse esta em cima de algum jewel
    int valid = 0;
    for(int i = 0; i < MATRIX_SIZE && !valid; i++)
    {
        for(int j = 0; j < MATRIX_SIZE && !valid; j++)
        {
            if((x >= m[i][j].x) && (x <= m[i][j].x + 35) && (y >= m[i][j].y) && (y <= m[i][j].y + 35))
            {
                m[i][j].select[0] = 1;
                pos[0] = i;
                pos[1] = j;
		valid = 1;
            }
            else
            {
                m[i][j].select[0] = 0;
	    }      
        }
    } 
    if (!valid)
    {	     
                pos[0] = -1;
                pos[1] = -1;
		return 0;
    }
    else
      return 1;
}

void matrix_swap(MATRIX** m, int i, int j){
    
}


void mouse_deinit()     
{
    al_uninstall_mouse();
}
