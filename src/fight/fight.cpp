#include <fight/fight.hpp>
#include <algorithm>
#include <game/global.hpp>
#include <game/game.hpp>
#include <iostream>
#include <sstream>
#include <shake.hpp>
#include <audio.hpp>

#define THIS_ROOM global::get().rooms[fightRoomID]
#define player (Game::getGame()->player)

void Fight::update(double ms) {
    if (attacks.size()>0)
    for (int i=currentCommand; i<attacks[currentAttack].size(); i=++currentCommand) {
        const std::string& command = attacks[currentAttack][i];
        if (_timeSinceSleepCommand<_sleep) {
            _timeSinceSleepCommand+=ms;
            break;
        }
        runCommand(command);
    }
    if (currentCommand>=attacks[currentAttack].size()) currentCommand=0;


    std::erase_if(blasts, [](Blast& b) { return b.isFinished(); });
    std::erase_if(orbs, [](Orb& o) { return o.isFinished(); });

    for (Blast& blast : blasts)
        blast.update(ms);
    for (Orb& orb : orbs)
        orb.update(ms);
}


void Fight::draw() {
    for (Blast& b : blasts)
        b.draw(THIS_ROOM.getTranslate());
    // Draw orbs
    for (Orb& o : orbs)
        o.draw(THIS_ROOM.getTranslate());
}
void Fight::drawHitboxes() {
    // Blast hitboxes
    for (const Blast& b : blasts) {
        Game::drawRectf(b.getHitbox(), al_map_rgb(255,50,50), THIS_ROOM.getTranslate());
    }
    // Orb hitboxes
    for (const Orb& o : orbs) {
        Game::drawCircf(o.getHitbox(), al_map_rgb(255,50,50), THIS_ROOM.getTranslate());
    }
}





void Fight::runCommand(const std::string& line) {
    if (line[0]=='#') return;
    if (line[0]=='{') return;
    if (line[0]=='}') return;
    if (line.starts_with("attacks:")) return;

    // std::cout << line << std::endl;
    std::istringstream _l(line);
    std::string token;
    
    std::getline(_l, token, ' ');
    if (line.starts_with("room ")) {
        std::getline(_l, token, ' ');
        fightRoomID = std::stoi(token);
    } else if (line.starts_with("spawn ")) {
        std::getline(_l, token, ' ');
        playerSpawn.x = std::stof(token);
        std::getline(_l, token, ' ');
        playerSpawn.y = std::stof(token);
        player.setWorldPosition(playerSpawn);
    } else if (line.starts_with("print ")) {
        std::cout << line.substr(6) << std::endl;
    } else if (line.starts_with("sleep ")) {
        std::getline(_l, token, ' ');
        _sleep = std::stod(token);
        _timeSinceSleepCommand = 0.0;
    } else if (line.starts_with("shake ")) {
        std::getline(_l, token, ' ');
        float strength = std::stof(token);
        std::getline(_l, token, ' ');
        float freq = std::stof(token);
        std::getline(_l, token, ' ');
        float duration = std::stof(token);
        shake::set(strength,freq,duration);
    } else if (line.starts_with("stopmus")) {
        if (!std::getline(_l, token, ' ')) {
            audio::stopStream(); return;
        }
        audio::stopStream(std::stoi(token));
    } else if (line.starts_with("mus ")) {
        std::getline(_l, token, ' ');
        audio::Stream mus = (audio::Stream)std::stoi(token);
        if (!std::getline(_l,token,' ')) {
            audio::playStream(mus); return;
        }
        audio::playStream(mus,std::stoi(token));
    } else if (line.starts_with("snd ")) {
        std::getline(_l, token, ' ');
        audio::Sound snd = (audio::Sound)std::stoi(token);
        float prefs[] = {1.0f, 0.0f, 1.0f}; // gain, pan, speed
        int index = 0;
        while (std::getline(_l, token, ' ')) {
            prefs[index++] = std::stof(token);
            if (index>=3) break;
        }
        audio::playSound(snd, prefs[0],prefs[1],prefs[2]);
    } else if (line.starts_with("silence ")) {
        std::getline(_l, token, ' ');
        audio::Stream stm = (audio::Stream) std::stoi(token);
        if (!std::getline(_l, token, ' '))
            audio::silenceStream(stm);
        else
            audio::silenceStream(stm, std::stof(token));
    } else if (line.starts_with("fademus ")) {
        std::getline(_l, token, ' ');
        audio::Stream stm = (audio::Stream) std::stoi(token);
        std::getline(_l, token, ' ');
        float val = std::stof(token);
        if (!std::getline(_l, token, ' '))
            audio::fadeStream(stm,val);
        else
            audio::fadeStream(stm,1.0f, std::stof(token));
    }
}