#include <audio.hpp>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <asset_manager.hpp>

namespace audio {

    constexpr const char* STREAMS[] = {
        "audio/Audio07.wav",
        "audio/project.wav",
        "audio/PureVessel.wav"
    };
    constexpr const char* SOUNDS[] = {
        "audio/snd/voice1.wav"
    };

    ALLEGRO_SAMPLE* sounds[SOUND_COUNT];
    ALLEGRO_AUDIO_STREAM* streams[STREAM_COUNT];


    struct Preference {
        float gain,pan,speed;
    };

    struct PrefDurations {
        float T_gain, T_pan, T_speed;
    };
    struct PrefTimer {
        float t_gain, t_pan, t_speed;
    };
    struct DeltaPreference {
        float dGain, dPan, dSpeed;
    };

    float gains[STREAM_COUNT] = {1.f};
    float targetGains[STREAM_COUNT] = {1.f};
    float timers[STREAM_COUNT] = {0};
    float durations[STREAM_COUNT] = {0};

} // namespace audio

#define LOAD_SOUND(snd_enum,filename) audio::sounds[snd_enum] = al_load_sample(assman::getasset("audio/snd/" filename).c_str())
#define LOAD_STREAM(strm_enum,filename) audio::streams[strm_enum] = al_load_audio_stream(assman::getasset("audio/" filename).c_str(), 4, 2048)

void __audio_loadSounds() {
    for (int i=0; i<audio::Sound::SOUND_COUNT; i++) {
        ALLEGRO_SAMPLE* sample = al_load_sample(assman::getasset(audio::SOUNDS[i]).c_str());
        if (!sample) printf("[AUDIO] Sound fail: %s\n", audio::SOUNDS[i]);
        audio::sounds[i] = sample;
    }
}
void __audio_loadStreams() {
    for (int i=0; i<audio::Stream::STREAM_COUNT; i++) {
        
        ALLEGRO_AUDIO_STREAM* stream = al_load_audio_stream(assman::getasset(audio::STREAMS[i]).c_str(), 4, 1024);
        if (!stream) printf("[AUDIO] Stream fail: %s\n", audio::STREAMS[i]);
        audio::streams[i] = stream;
    }
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

    for (int i=1; i<STREAM_COUNT; i++){
        gains[i] = gains[0];
        targetGains[i] = targetGains[0];
        timers[i] = timers[0];
        durations[i] = durations[0];
    }

    for (int i=0; i<al_get_num_audio_output_devices(); i++)
        printf("Audio device: %s\n", al_get_audio_device_name(al_get_audio_output_device(i)));

    __audio_loadSounds();
    __audio_loadStreams();
    return 0;
}
void audio::destroy() {
    for (int i=0; i<Sound::SOUND_COUNT; i++)
        al_destroy_sample(sounds[i]);
    for (int i=0; i<Stream::STREAM_COUNT; i++)
        al_destroy_audio_stream(streams[i]);
}

void audio::update(double ms) {
    for (int i=0; i<STREAM_COUNT; i++) {
        // ... todo neki dan
        // silence fade
    }
}

void audio::playSound(Sound snd, float gain, float pan, float speed, ALLEGRO_SAMPLE_ID *out_id) {
    // ALLEGRO_SAMPLE_INSTANCE* instance = al_create_sample_instance(sounds[snd]);
    // al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
    // al_play_sample_instance(instance);

    // or just...
    al_play_sample(sounds[snd], gain, pan, speed, ALLEGRO_PLAYMODE_ONCE, out_id);
}
void audio::playStream(Stream strm, bool loop, float gain, float pan, float speed) {
    al_attach_audio_stream_to_mixer(streams[strm], al_get_default_mixer());
    al_set_audio_stream_playmode(streams[strm], loop? ALLEGRO_PLAYMODE_LOOP:ALLEGRO_PLAYMODE_ONCE);
    al_set_audio_stream_gain(streams[strm], gain);
    al_set_audio_stream_pan(streams[strm], pan);
    al_set_audio_stream_speed(streams[strm], speed);
    al_set_audio_stream_playing(streams[strm], true);

    gains[strm] = gain;
}

void audio::stopStream(int stream) {
    if (stream<0) {
        for (int i=0; i<STREAM_COUNT; i++)
            al_set_audio_stream_playing(streams[i], false);
    } else
        al_set_audio_stream_playing(streams[stream], false);
}

void audio::silenceStream(audio::Stream stream) {

}