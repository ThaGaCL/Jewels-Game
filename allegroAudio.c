#include "allegroAudio.h"

ALLEGRO_AUDIO_STREAM* bg_music_1;


void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    bg_music_1 = al_load_audio_stream("assets/audio/bgsong1.ogg", 4, 1024);
    mustInit(bg_music_1, "al_load_sample bgsong1.ogg");
    al_set_audio_stream_playmode(bg_music_1, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(bg_music_1, al_get_default_mixer());


}

void audio_deinit()
{
    al_destroy_audio_stream(bg_music_1);
}