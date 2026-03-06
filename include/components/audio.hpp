//
//  audio.hpp
//  audio engine (gltutorial)
//
//  Created by Luka on 19.1.25..
//
#pragma once
#ifndef audio_hpp
#define audio_hpp

#include <FMOD/fmod.hpp>

namespace audio {

bool isSoundSlotFree(int slot);
void freeSound(int slot);
int findFreeSoundSlot();
int occupySoundSlot(int slot, FMOD::Sound *sound);


class Channel {
private:
    FMOD::Channel *channel;
public:
    // variables
    int id;
    int sound_id;
    // constructors
    Channel(); // does nothing
    Channel(int id);
    Channel(FMOD::Channel *channel);
    // functions
    void init(int id);
    void init(FMOD::Channel *channel);
    void setPlaying(bool t);
    bool isPlaying();
    FMOD::Channel *getFMODChannel();
};

int init();
void update();
void destroy();
int getError();
const char *getErrorString(FMOD_RESULT);
void getDriverInfo(char *out_name, int name_len, int *out_opt_driverID, int *out_opt_systemRate);
const char* getSpeakerModeName(FMOD_SPEAKERMODE);
int loadAudio(const char* filename, int *out_sound_id);
Channel prepareAudio(int sound_id);
FMOD::Channel *getChannel(int index);


} // namespace audio

#endif /* audio_hpp */