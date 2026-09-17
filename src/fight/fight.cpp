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
    if (line.size()<1) return;

    // std::cout << line << std::endl;
    std::istringstream _l(line);
    std::string token;

    std::vector<std::string> args;
    while (std::getline(_l, token, ' ')) {
        args.push_back(token);
        // std::cout << token << " | ";
    }
    // putchar(0xa);
    
    // std::getline(_l, token, ' ');
    if (line.starts_with("snd ")) {
        audio::Sound snd = (audio::Sound)std::stoi(args[1]);
        float prefs[] = {1.0f, 0.0f, 1.0f}; // gain, pan, speed
        for (int i=0; i<3; i++) {
            if (args.size()<(i+3)) break;
            prefs[i] = std::stof(args[2+i]);
            std::cout << args[2+i] << std::endl;
        }
        audio::playSound(snd, prefs[0],prefs[1],prefs[2]);
    } else if (line.starts_with("orb ")) {
        float x = std::stoi(args[1]);
        float y = std::stoi(args[2]);
        orbs.push_back(Orb(x,y,10.f));
    } else if (line.starts_with("blast")) {
        float xy = std::stoi(args[1]);
        float h = std::stoi(args[2]);

        if (line[5]=='v') blasts.push_back(Blast(Blast::VERTICAL, xy, h, 10));
        else if (line[5]=='h') blasts.push_back(Blast(Blast::HORIZONTAL, xy, h, 10));

    } else if (line.starts_with("orb ")) {
        float x = std::stoi(args[1]);
        float y = std::stoi(args[2]);
        orbs.push_back(Orb(x,y,10.f));
    } else if (line.starts_with("room ")) {
        fightRoomID = std::stoi(args[1]);
    } else if (line.starts_with("spawn ")) {
        playerSpawn.x = std::stof(args[1]);
        playerSpawn.y = std::stof(args[2]);
        player.setWorldPosition(playerSpawn);
    } else if (line.starts_with("print ")) {
        std::cout << line.substr(6) << std::endl;
    } else if (line.starts_with("sleep ")) {
        _sleep = std::stod(args[1]);
        _timeSinceSleepCommand = 0.0;
    } else if (line.starts_with("shake ")) {
        float strength = std::stof(args[1]);
        float freq = std::stof(args[2]);
        float duration = std::stof(args[3]);
        shake::set(strength,freq,duration);
    } else if (line.starts_with("stopmus")) {
        if (args.size()<2) {
            audio::stopStream(); return;
        }
        audio::stopStream(std::stoi(args[1]));
    } else if (line.starts_with("mus ")) {
        audio::Stream mus = (audio::Stream)std::stoi(args[1]);
        if (args.size()<3) {
            audio::playStream(mus); return;
        }
        audio::playStream(mus,std::stoi(args[2]));
    } else if (line.starts_with("silence ")) {
        audio::Stream stm = (audio::Stream) std::stoi(args[1]);
        if (args.size()<3)
            audio::silenceStream(stm);
        else
            audio::silenceStream(stm, std::stof(args[2]));
    } else if (line.starts_with("fademus ")) {
        audio::Stream stm = (audio::Stream) std::stoi(args[1]);
        float val = std::stof(args[2]);
        if (args.size()<4)
            audio::fadeStream(stm,val);
        else
            audio::fadeStream(stm,val, std::stof(args[3]));
    }
}