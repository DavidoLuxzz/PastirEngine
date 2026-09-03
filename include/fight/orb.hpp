#pragma once
#ifndef __FIGHT_ORB_HPP
#define __FIGHT_ORB_HPP

#include <animation.hpp>
#include <data_types.hpp>

class Orb {
    Animation anim;
    Circf shape;

    float2 velocity={0.f,0.f};

    int numShades;
    float visibility=0.0f;
    float increment, decrement;
    int incrementFrames;
public:

    Orb(float cx, float cy, float radius, int dimFrames=-1, float increment=0.01f);
    void draw(float2 translate={0.f,0.f});
    void update();
    bool isFinished() const;

    void tick(int frame);

    Circf getHitbox() const;
};



#endif