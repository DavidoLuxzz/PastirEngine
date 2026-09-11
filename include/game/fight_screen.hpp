#pragma once
#ifndef __FIGHT_SCREEN_HPP
#define __FIGHT_SCREEN_HPP

#include <fight/blast.hpp>
#include <fight/orb.hpp>
#include <vector>
#include <fight/fight.hpp>

class FightScreen {
public:
    Fight fight;

    void handleEvents();
    void update(double ms);
    void draw();


    void game_move(float dx, float dy, float ms); // move with collision
    // might as well end this live stream (kasikom i viljuskom,... pro inglish ;)
};


#endif