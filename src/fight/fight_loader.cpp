#include <fight/fight_loader.hpp>
#include <fight/fight.hpp>
#include <asset_manager.hpp>
#include <filesystem>
#include <colors.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace fight_loader {
    
    Fight fight;

} // namespace fight_loader

int __fight_loader_load(const std::string& filepath) {
    std::ifstream file(filepath);
    bool _at = false;

    Fight::Attack attack;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line[0]=='{') {_at = true; attack.clear(); continue;}
        if (line[0]=='}') {_at = false; fight_loader::fight.attacks.push_back(attack); continue;}
        if (!_at) fight_loader::fight.runCommand(line);

        if (_at) {
            if (line[0]=='#') continue;
            attack.push_back(line);
        }
    }

    file.close();

    return 0;
}

int fight_loader::load(unsigned int fightID) {
    std::string filepath = assman::getasset("fights/fight"+std::to_string(fightID) + ".pff");
    if (!std::filesystem::exists(filepath)) {
        fprintf(stderr, "<%sFIGHTLOADER%s> Fight %u doesn't exists. path=%s\n",TERMINAL_COLOR_RED_BOLD,TERMINAL_COLOR_RESET, fightID, filepath.c_str());
        return -1;
    }
    // printf("<LVLLOADER> Loading room %u path=%s\n", roomID, filepath.c_str());
    return __fight_loader_load(filepath);
}



void fight_loader::swapData(Fight& f) {
    f.blasts.swap(fight.blasts);
    f.orbs.swap(fight.orbs);
    f.music.swap(fight.music);
    f.sounds.swap(fight.sounds);
    f.playerSpawn = fight.playerSpawn;
    f.fightRoomID = fight.fightRoomID;
    f.attacks.swap(fight.attacks);
}