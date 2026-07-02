#pragma once
#ifndef __audio_hpp
#define __audio_hpp

namespace audio {

    enum Audio {
        AUDIO_07,
        VOICE01,

        AUDIO_COUNT
    };

    void init();
    void loadAll();


    void destroy();



}

#endif