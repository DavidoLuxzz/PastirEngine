#include <audio.hpp>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <asset_manager.hpp>

namespace audio {
    ALLEGRO_MIXER* mixer;
    ALLEGRO_VOICE* voice;

    ALLEGRO_SAMPLE* sounds[SOUND_COUNT];
    ALLEGRO_AUDIO_STREAM* streams[STREAM_COUNT];
} // namespace audio

#define LOAD_SOUND(snd_enum,filename) audio::sounds[snd_enum] = al_load_sample(assman::getasset("audio/snd/" filename).c_str())
#define LOAD_STREAM(strm_enum,filename) audio::streams[strm_enum] = al_load_audio_stream(assman::getasset("audio/" filename).c_str(), 4, 2048)

void __audio_loadSounds() {
    // if (!(LOAD_SOUND(audio::VOICE01,"voice1.wav"))) fprintf(stderr, "[AUDIO] Could not load voice1.wav\n");
    ALLEGRO_SAMPLE* sample = al_load_sample(assman::getasset("audio/snd/voice1.wav").c_str());
    if (!sample) printf("[AUDIO] Sample fail\n");
    audio::sounds[audio::Sound::VOICE01] = sample;
}
void __audio_loadStreams() {
    // if (!(LOAD_STREAM(audio::AUDIO_07,"project.mp3"))) fprintf(stderr, "[AUDIO] Could not load stream\n");
    ALLEGRO_AUDIO_STREAM* stream = al_load_audio_stream(assman::getasset("audio/Audio07.wav").c_str(), 4, 1024);
    if (!stream) printf("[AUDIO] Stream fail\n");
    audio::streams[audio::Stream::AUDIO_07] = stream;
    printf("ERRNO: %d\n", al_get_errno());
}

int audio::init() {
    if (!al_reserve_samples(AUDIO_SAMPLE_COUNT)) {
        fprintf(stderr, "[AUDIO] Failed to reserve samples\n");
        return -1;
    }
    // voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    // if (!voice) {
    //     fprintf(stderr, "[AUDIO] Could not create default voice\n");
    //     return -1;
    // }
    // mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    // if (!mixer) {
    //     fprintf(stderr, "[AUDIO] Could not create default mixer\n");
    //     al_destroy_voice(voice);
    //     return -1;
    // }
    // al_attach_mixer_to_voice(mixer, voice);

    for (int i=0; i<al_get_num_audio_output_devices(); i++)
        printf("Audio device: %s\n", al_get_audio_device_name(al_get_audio_output_device(i)));

    __audio_loadSounds();
    __audio_loadStreams();
    return 0;
}
void audio::destroy() {
    return; // remove
    al_detach_mixer(mixer);
    al_detach_voice(voice);
    al_destroy_mixer(mixer);
    al_destroy_voice(voice);
}

void audio::playSound(Sound snd) {
    al_play_sample(sounds[snd], 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void audio::playStream(Stream strm) {
    al_attach_audio_stream_to_mixer(streams[strm], al_get_default_mixer());
    al_set_audio_stream_playing(streams[strm], true);
}