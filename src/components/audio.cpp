//
//  audio.cpp
//  audio engine (using FMOD)
//
//  Created by Luka on 18.1.25..
//

// ##### FMOD ##### //
#include <components/audio.hpp>
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>
#include <iostream>
#include <asset_manager.hpp>
#include <vector>

#define AUDIO_CHANNELS 512
#define SOUND_BUFFERS 512

namespace audio {
FMOD_RESULT latest_result;
FMOD::System *system = NULL;
FMOD::Sound* sounds[SOUND_BUFFERS];
bool sounds_free_bitmap[SOUND_BUFFERS]; // 1 - allocated,  0 - free
}

bool audio::isSoundSlotFree(int slot){
    return sounds_free_bitmap[slot];
}
void audio::freeSound(int slot){
    sounds[slot]->release();
    sounds_free_bitmap[slot] = false;
}
int audio::findFreeSoundSlot(){
    for (int i=0; i<SOUND_BUFFERS; i++){
        if (sounds_free_bitmap[i]==0) return i;
    }
    return -1;
}
int audio::occupySoundSlot(int slot, FMOD::Sound *sound){
    if (sounds_free_bitmap[slot]) return -1;
    sounds_free_bitmap[slot] = 1;
    sounds[slot] = sound;
    return 0;
}

int audio::getError(){
    return latest_result;
}

const char *audio::getErrorString(FMOD_RESULT res){
    return FMOD_ErrorString(res);
}

int audio::init(){
    // Create main system object
    FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING);
    latest_result = FMOD::System_Create(&system);
    if (latest_result != FMOD_OK) {
        printf("[FMOD] Init error. (%s)\n", FMOD_ErrorString(latest_result));
        return -1;
    }
    // Initialize FMOD
    latest_result = system->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
    latest_result = system->init(AUDIO_CHANNELS, FMOD_INIT_NORMAL, 0);
    if (latest_result != FMOD_OK) {
        printf("[FMOD] Init error. (%s)\n", FMOD_ErrorString(latest_result));
        return -1;
    }
    
    memset(sounds_free_bitmap, 0, SOUND_BUFFERS);
    
    printf("[FMOD] All gud =b\n");
    
    return 0;
}
void audio::update(){ system->update(); }

void audio::getDriverInfo(char *out_name, int name_len, int *out_opt_driverid, int *out_opt_sysrate){
    // Display audio driver data
    int driverid;
    system->getDriver(&driverid);
    system->getDriverInfo(driverid, out_name, name_len, NULL, out_opt_sysrate, NULL, NULL);
    *out_opt_driverid = driverid;
}
int audio::loadAudio(const char* filename, int *sound_id){
    // Check if space for new sound
    int slot = findFreeSoundSlot();
    if (slot < 0){
        std::cerr << "[FMOD] No space for new audio.\n";
        return -1;
    }
    // Sound
    FMOD::Sound *sound;
    latest_result = system->createStream(assman::getasset(filename).c_str(), FMOD_3D, NULL, &sound);
    if (latest_result != FMOD_OK){
        fprintf(stderr, "[FMOD] Error creating sound (%s)\n", FMOD_ErrorString(latest_result));
        return -1;
    }
    occupySoundSlot(slot, sound);
    *sound_id = slot;
    return 0;
}

audio::Channel audio::prepareAudio(int sound_id){
    if (not sounds_free_bitmap[sound_id]){
        std::cerr << "[FMOD] Error preparing audio. Sound is free\n";
        return 0;
    }
    FMOD::Channel *channel;
    FMOD::Sound *sound = sounds[sound_id];
    latest_result = system->playSound(sound, NULL, true, &channel);
    if (latest_result != FMOD_OK){
        fprintf(stderr, "[FMOD] Failed to prepare sound (%s)\n", FMOD_ErrorString(latest_result));
        return -1;
    }
    Channel out_channel(channel);
    out_channel.sound_id = sound_id;
    return out_channel;
}

void audio::temp(){
    // Setting up example reverb
    FMOD::Reverb3D *revb;
    system->createReverb3D(&revb);
    FMOD_REVERB_PROPERTIES props = FMOD_PRESET_CAVE;
    revb->setProperties(&props);
    
    FMOD_VECTOR pos = { -10.0f, 0.0f, 0.0f };
    float mindist = 0.0f;
    float maxdist = 100.0f;
    revb->set3DAttributes(&pos, mindist, maxdist);
    
    while (true){
        system->update();
    }
}

FMOD::Channel *audio::getChannel(int index){
    FMOD::Channel *chan;
    system->getChannel(index, &chan);
    return chan;
}

void audio::destroy(){
    // Release sounds
    for (int i=0; i<SOUND_BUFFERS; i++)
        if (sounds_free_bitmap[i]) sounds[i]->release();
    // Release main FMOD system
    system->release();
    system->close();
}







// #### CLASS CHANNEL #### //
audio::Channel::Channel(){} // private

void audio::Channel::init(int index){
    system->getChannel(index, &channel);
    id = index;
}
void audio::Channel::init(FMOD::Channel *chann){
    channel = chann;
    chann->getIndex(&id);
}

audio::Channel::Channel(int index){
    init(index);
}
audio::Channel::Channel(FMOD::Channel *chann){
    init(chann);
}

void audio::Channel::setPlaying(bool t){
    channel->setPaused(not t);
}

bool audio::Channel::isPlaying(){
    bool t;
    channel->isPlaying(&t);
    return t;
}

FMOD::Channel *audio::Channel::getFMODChannel(){
    return channel;
}

void audio::Channel::setSourcePosition(float x, float y, float z){
    FMOD_VECTOR a_vec_pos;
    a_vec_pos.x = x;
    a_vec_pos.y = y;
    a_vec_pos.z = z;
    channel->set3DAttributes(&a_vec_pos, NULL);
}