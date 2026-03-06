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
namespace audio {
void setup_driver() {
    int driver;
    system->getDriver(&driver);
    char drv_name[64];
    FMOD_GUID drv_guid;
    int drv_sysrate;
    FMOD_SPEAKERMODE drv_speakermode;
    int drv_spkmode_channels;
    system->getDriverInfo(driver, drv_name, 64, &drv_guid, &drv_sysrate, &drv_speakermode, &drv_spkmode_channels);

    printf("[FMOD] Driver: %s [%d]. System Rate=%d;  Speaker Mode=%s;  SpeakerMode Channels=%d\n", drv_name,driver,drv_sysrate,getSpeakerModeName(drv_speakermode),drv_spkmode_channels);

    latest_result = system->setSoftwareFormat(drv_sysrate, drv_speakermode, 0);
    if (latest_result != FMOD_OK) {
        printf("[FMOD] Software format error. (%s)\n", FMOD_ErrorString(latest_result));
    }
}
}

int audio::init(){
    // Create main system object
    FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING);
    latest_result = FMOD::System_Create(&system);
    if (latest_result != FMOD_OK) {
        printf("[FMOD] Init error. (%s)\n", FMOD_ErrorString(latest_result));
        return -1;
    }

    // Setup speaker mode
    setup_driver();
    // Initialize FMOD
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
const char* audio::getSpeakerModeName(FMOD_SPEAKERMODE spkmd) {
    static const char* const names[] = {
        "DEFAULT",
        "RAW",
        "MONO",
        "STEREO",
        "QUAD",
        "SURROUND",
        "5POINT1",
        "7POINT1",
        "7POINT1POINT4"
    };
    return names[spkmd];
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
    latest_result = system->createStream(assman::getasset(filename).c_str(), FMOD_2D, NULL, &sound);
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