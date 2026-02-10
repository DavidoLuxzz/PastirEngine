#pragma once
#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <sprite/sprite.hpp>
#include <sprite/texture.hpp>

class Player : public Sprite {
public:
    enum directions {
        DIR_UP,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT,
        NUM_ANIMATION_FRAMES // stoji ovde eto jbg posto ce dobiti value 4, pa da sacuvam prostora
    };

    void move(float dx, float dy);
    /**
     * Changes players texture tile according to the current direction.
     */
    void orientate(float dx, float dy);

    void useNikes(bool);

    void draw();
};

#endif