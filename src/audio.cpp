#include <audio.hpp>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <asset_manager.hpp>
#include <colors.h>

namespace audio {

    constexpr const char* STREAMS[] = {
        "audio/Audio07.wav",
        "audio/project.wav",
        "audio/PureVessel.wav",
        "audio/gangnam.wav"
    };
    constexpr const char* SOUNDS[] = {
        "audio/snd/voice1.wav",
        "audio/snd/step1.wav",
        "audio/snd/step2.wav",
        "audio/snd/grass.ogg"
    };

    ALLEGRO_SAMPLE* sounds[SOUND_COUNT];
    ALLEGRO_AUDIO_STREAM* streams[STREAM_COUNT];


    float gains[STREAM_COUNT] = {0.f};
    float oldGains[STREAM_COUNT] = {0.f};
    float deltaGains[STREAM_COUNT] = {0.f};
    float timers[STREAM_COUNT] = {0};
    float durations[STREAM_COUNT] = {0};
    bool stopWhenSilenced[STREAM_COUNT] = {false};

} // namespace audio

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
        al_attach_audio_stream_to_mixer(stream, al_get_default_mixer());
        al_set_audio_stream_playing(stream, false);
        al_set_audio_stream_gain(stream, 0.f);
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
        oldGains[i] = oldGains[0];
        deltaGains[i] = deltaGains[0];
        timers[i] = timers[0];
        durations[i] = durations[0];
        stopWhenSilenced[i] = stopWhenSilenced[0];
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
        if (timers[i]<durations[i]) {
            if ((timers[i]+ms)>=durations[i]) {
                gains[i] = oldGains[i] + deltaGains[i];
                al_set_audio_stream_gain(streams[i], gains[i]);
                // printf("Gain: %.2f\nTimer=%.1f, Duration=%.1f\n", gains[i], timers[i], durations[i]);
                if (stopWhenSilenced[i]) {
                    if (gains[i]<0.001f) stopStream(i);
                    stopWhenSilenced[i] = false;
                }
                // printf("Zavrsio\n");
                timers[i]+=ms;
                continue;
            }
            gains[i] = oldGains[i] + deltaGains[i]*timers[i]/durations[i];
            al_set_audio_stream_gain(streams[i],gains[i]);
            // printf("Gain: %.2f\nTimer=%.1f, Duration=%.1f\n", gains[i], timers[i], durations[i]);
            timers[i]+=ms;
        }
    }
}

void audio::playSound(Sound snd, float gain, float pan, float speed, ALLEGRO_SAMPLE_INSTANCE *out_id) {
    if (snd<0 || snd>=SOUND_COUNT) {
        printf("%s[WARNING] audio::playSound(5) called with sound out of bounds: %d%s\n",
            TERMINAL_COLOR_YELLOW_BOLD, snd, TERMINAL_COLOR_RESET);
        return;
    }
    ALLEGRO_SAMPLE_INSTANCE* instance = al_create_sample_instance(sounds[snd]);
    al_set_sample_instance_gain(instance, gain);
    al_set_sample_instance_pan(instance, pan);
    al_set_sample_instance_speed(instance, speed);
    al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
    al_play_sample_instance(instance);

    // printf("Played sound %s\n", SOUNDS[snd]);

    // or just...
    //al_play_sample(sounds[snd], gain, pan, speed, ALLEGRO_PLAYMODE_ONCE, out_id);
}
void audio::playStream(Stream strm, bool loop, float gain, float pan, float speed) {
    if (strm<0 || strm>=STREAM_COUNT) {
        printf("%s[WARNING] audio::playStream(5) called with stream out of bounds: %d%s\n",
            TERMINAL_COLOR_YELLOW_BOLD, strm, TERMINAL_COLOR_RESET);
        return;
    }
    // al_attach_audio_stream_to_mixer(streams[strm], al_get_default_mixer());
    al_set_audio_stream_playmode(streams[strm], loop? ALLEGRO_PLAYMODE_LOOP:ALLEGRO_PLAYMODE_ONCE);
    al_set_audio_stream_gain(streams[strm], gain);
    al_set_audio_stream_pan(streams[strm], pan);
    al_set_audio_stream_speed(streams[strm], speed);
    al_set_audio_stream_playing(streams[strm], true);

    gains[strm] = gain;
    oldGains[strm] = gain;
    timers[strm] = 0;
    durations[strm] = 0;
    deltaGains[strm] = 0;
}

void audio::stopStream(int stream) {
    if (stream>=STREAM_COUNT) return; // koga boli uvo
    if (stream<0) {
        for (int i=0; i<STREAM_COUNT; i++)
            al_set_audio_stream_playing(streams[i], false);
    } else
        al_set_audio_stream_playing(streams[stream], false);
}

void audio::silenceStream(audio::Stream stream, float millis, bool stop) {
    fadeStream(stream, 0.f, millis, stop);
}

void audio::fadeStream(audio::Stream stream, float val, float millis, bool stop) {
    if (stream<0 || stream>=STREAM_COUNT) {
        printf("%s[WARNING] audio::fadeStream(3) called with stream out of bounds: %d%s\n",
            TERMINAL_COLOR_YELLOW_BOLD, stream, TERMINAL_COLOR_RESET);
        return;
    }

    if (millis<=1.f){ // instant
        al_set_audio_stream_gain(streams[stream], val);
        if (stop && val<0.001f) stopStream(stream);
        else if (val>0.001f) al_set_audio_stream_playing(streams[stream], true);
    }
    // gains[stream] = al_get_audio_stream_gain(streams[stream]);
    durations[stream] = millis;
    deltaGains[stream] = val-gains[stream];
    oldGains[stream] = gains[stream];
    // printf("dg: %.2f\n", deltaGains[stream]);
    timers[stream] = 0.f;
    stopWhenSilenced[stream] = stop;
    if (val>0) al_set_audio_stream_playing(streams[stream], true);
}


ALLEGRO_AUDIO_STREAM* audio::getStream(Stream s) {
    return streams[s];
}

bool audio::isStreamPlaying(Stream s) {
    return al_get_audio_stream_playing(streams[s]) && al_get_audio_stream_attached(streams[s]);
}

float audio::getStreamEngineGain(Stream s) {
    return gains[s];
}