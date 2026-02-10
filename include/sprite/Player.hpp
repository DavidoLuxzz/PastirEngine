#pragma once
#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <sprite/sprite.hpp>
#include <sprite/texture.hpp>
#include <animation.hpp>

class Player : public Sprite {
private:
    unsigned int currentFrame = 0;
    // int currentDirection = DIR_UP;
    Animation animation;
public:
    Player();
    void _animTick(int frame);
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
    void setTileByDirection(directions);

    void useNikes(bool);

    void draw();
};

#endif