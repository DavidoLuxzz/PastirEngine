#pragma once
#ifndef __ENTITY_HPP
#define __ENTITY_HPP

#include <sprite/sprite.hpp>

class Entity : public Sprite {
    // AI, Trigger
    float2 v{0.0f,0.0f};
public:
    void init(unsigned int tilesetBankID=bank::tileset::ENTITY0);

    void draw();
    void update(float ms);
};


#endif