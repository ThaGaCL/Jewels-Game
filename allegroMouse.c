#include "allegroMouse.h"

void mouse_init()
{
    mustInit(al_install_mouse(), "mouse");
    mustInit(al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT), "mouse cursor");
}


void mouse_deinit()     
{
    al_uninstall_mouse();
}
