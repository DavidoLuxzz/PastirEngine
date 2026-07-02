#pragma once
#ifndef __audio_hpp
#define __audio_hpp


#define AUDIO_SAMPLE_COUNT 8 // koliko max audija moze da se cuje u isto vreme

namespace audio {

    enum Sound {
        VOICE01,

        SOUND_COUNT
    };

    enum Stream {
        AUDIO_07,

        STREAM_COUNT
    };

    /**
     * Initializes and loads all music and sounds.
     * @returns error code
     */
    int init();
    void destroy();

    void playSound(Sound snd);
    void playStream(Stream strm);

}

#endif