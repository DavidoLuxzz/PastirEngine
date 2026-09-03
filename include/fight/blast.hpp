#pragma once
#ifndef __BLAST_HPP
#define __BLAST_HPP

#include <animation.hpp>
#include <data_types.hpp>

// horizontal blast
class Blast {
public:
    enum BlasterType {
        HORIZONTAL,
        VERTICAL
    };
private:
    Animation anim;
    float center;
    float height;
    int numShades;
    float visibility=0.0f;
    float increment, decrement;
    int incrementFrames;
    BlasterType btype;

public:

    

    Blast(BlasterType type, float cy, float height, int dimFrames=-1, float increment=0.01f);
    void draw(float2 translate={0.f,0.f}); // translate - room translate
    void update();
    bool isFinished() const;

    void tick(int frame);

    Rectf getHitbox() const;
};


#endif