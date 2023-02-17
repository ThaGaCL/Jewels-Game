#ifndef ALLEGRO_AUDIO_H
#define ALLEGRO_AUDIO_H
#include "allegroUtil.h"

extern ALLEGRO_AUDIO_STREAM* bg_music_1;
extern ALLEGRO_SAMPLE* startup_sound;
extern ALLEGRO_SAMPLE* success_sound;
extern ALLEGRO_SAMPLE* fail_sound;
extern ALLEGRO_SAMPLE* levelup_sound;


void audio_init();

void audio_deinit();

#endif