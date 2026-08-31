#pragma once
#ifndef __FIGHT_SCREEN_HPP
#define __FIGHT_SCREEN_HPP

#include <fight/blast.hpp>
#include <vector>

class FightScreen {
    std::vector<Blast> blasts;
public:
    int roomID = 1;

    void handleEvents();
    void update(float);
    void draw();


    void game_move(float dx, float dy); // move with collision
    // might as well end this live stream (kasikom i viljuskom,... pro inglish ;)
};


#endif