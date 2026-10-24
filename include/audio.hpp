#pragma once
#ifndef __audio_hpp
#define __audio_hpp

struct ALLEGRO_SAMPLE_INSTANCE;
struct ALLEGRO_AUDIO_STREAM;

#define AUDIO_SAMPLE_COUNT 8 // koliko max audija moze da se cuje u isto vreme

namespace audio {

    enum Sound {
        VOICE01,
        STEP01,
        STEP02,
        GRASS,

        SOUND_COUNT,
        SOUND_NONE
    };

    enum Stream {
        AUDIO_07,
        PROJECT,
        PURE_VESSEL,

        STREAM_COUNT,
        STREAM_NONE
    };

    /**
     * Initializes and loads all music and sounds.
     * @returns error code
     */
    int init();
    void destroy();

    /**
     * Updates fades and such...
     */
    void update(double ms);

    /// @return ALLEGRO_SAMPLE_ID
    void playSound(Sound snd, float gain=1.0f, float pan=0.0f, float speed=1.0f, ALLEGRO_SAMPLE_INSTANCE *out_id=nullptr);
    void playStream(Stream strm, bool loop=true, float gain=1.0f, float pan=0.0f, float speed=1.0f);

    void stopStream(int stream=-1);
    void silenceStream(Stream stream, float millis=1000.f, bool stop=false);
    void fadeStream(Stream stream, float val, float millis=1000.f, bool stop=false);

    ALLEGRO_AUDIO_STREAM* getStream(Stream strm);
    bool isStreamPlaying(Stream strm);
    /**
     * Returns the gain stored by the audio engine.
     * Doesn't have to mean that al_get_audio_stream_gain(1) == audio::getStreamEngineGain(1) !!!
     */
    float getStreamEngineGain(Stream strm);
}

#endif