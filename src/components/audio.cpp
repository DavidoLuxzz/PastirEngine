#include <components/audio.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <asset_manager.hpp>
#include <filesystem>
#include <iostream>
#include <allegro5/error.h>

ALLEGRO_AUDIO_STREAM* __audio_stream;

int audio::init() {
    al_reserve_samples(4);
    std::string fpath = assman::getasset("audio/project.mp3");
    printf("Audio file path = %s\n", fpath.c_str());
    if (!std::filesystem::exists(fpath)) std::cout << "nema ga\n";
    __audio_stream = al_load_audio_stream(fpath.c_str(), 4, 4);
    int err = al_get_errno();
    printf("Audio stream at %p [errno=%d]\n", __audio_stream, err);
    al_attach_audio_stream_to_mixer(__audio_stream, al_get_default_mixer());
    return __audio_stream==NULL;
}
void audio::play() {
    al_set_audio_stream_playing(__audio_stream, true);
}
void audio::stop() {
    al_set_audio_stream_playing(__audio_stream, false);
}