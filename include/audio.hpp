#pragma once
#ifndef __audio_hpp
#define __audio_hpp

struct ALLEGRO_SAMPLE_ID;

#define AUDIO_SAMPLE_COUNT 8 // koliko max audija moze da se cuje u isto vreme

namespace audio {

    enum Sound {
        VOICE01,

        SOUND_COUNT,
        SOUND_NONE
    };

    enum Stream {
        AUDIO_07,

        STREAM_COUNT,
        STREAM_NONE
    };

    /**
     * Initializes and loads all music and sounds.
     * @returns error code
     */
    int init();
    void destroy();

    /// @return ALLEGRO_SAMPLE_ID
    void playSound(Sound snd, float gain=1.0f, float pan=0.0f, float speed=1.0f, ALLEGRO_SAMPLE_ID *out_id=nullptr);
    void playStream(Stream strm, bool loop=true);

}

#endif