#pragma once
#ifndef __ENEMY_HPP
#define __ENEMY_HPP

#include <sprite/sprite.hpp>
#include <animation.hpp>
#include <vector>

/**
 * Klasa za enemies.
 * Treba da sadrzi animacije uglavnom.
 *  - 
 */
class Enemy {
    Sprite sprite;
    std::vector<Animation> animacije;
public:

    void update(double ms);

    void draw();

};


#endif