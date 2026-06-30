#pragma once
#ifndef __static_entity_hpp
#define __static_entity_hpp

#include <sprite/sprite.hpp>
#include <level/Triggers.hpp>

class StaticEntity : public Sprite {
private:
    /* data */
public:
    StaticEntity();
    Trigger trigger;
};


#endif