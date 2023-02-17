#include "allegroAudio.h"

ALLEGRO_AUDIO_STREAM *bg_music_1;
ALLEGRO_SAMPLE *startup_sound;
ALLEGRO_SAMPLE *success_sound;
ALLEGRO_SAMPLE *fail_sound;
ALLEGRO_SAMPLE *levelup_sound;

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    bg_music_1 = al_load_audio_stream("assets/audio/bgsong1.ogg", 4, 1024);
    mustInit(bg_music_1, "al_load_sample bgsong1.ogg");
    al_set_audio_stream_playmode(bg_music_1, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(bg_music_1, al_get_default_mixer());
    al_set_audio_stream_gain(bg_music_1, 0.1);

    startup_sound = al_load_sample("assets/audio/startup.wav");
    mustInit(startup_sound, "al_load_sample startup.wav");

    success_sound = al_load_sample("assets/audio/success.wav");
    mustInit(success_sound, "al_load_sample success.wav");

    fail_sound = al_load_sample("assets/audio/fail.wav");
    mustInit(fail_sound, "al_load_sample fail.wav");

    levelup_sound = al_load_sample("assets/audio/levelup.wav");
    mustInit(levelup_sound, "al_load_sample levelup.wav");

}

void audio_deinit()
{
    al_destroy_audio_stream(bg_music_1);
    al_destroy_sample(startup_sound);
    al_destroy_sample(success_sound);
    al_destroy_sample(fail_sound);
    al_destroy_sample(levelup_sound);
}