#include "allegroUtil.h"

void mustInit(bool test, const char *description){
    if(test) return;
    
    printf("Falha ao inicializar %s\n", description);
    exit(1);
}

void initAllegro(){
    mustInit(al_init(), "allegro");
    mustInit(al_init_font_addon(), "font");
    mustInit(al_init_primitives_addon(), "primitives");
    mustInit(al_install_audio(), "audio");
    mustInit(al_init_acodec_addon(), "acodec");
    mustInit(al_init_image_addon(), "image");
}