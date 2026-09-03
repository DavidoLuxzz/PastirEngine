#pragma once
#ifndef __BLAST_HPP
#define __BLAST_HPP

#include <animation.hpp>
#include <data_types.hpp>

// horizontal blast
class Blast {
    Animation anim;
    float centerY;
    float height;
    int numShades;
    float visibility=0.0f;
    float increment, decrement;
    int incrementFrames;
public:
    Blast(float cy, float height, int idleFrame=-1, float increment=0.01f);
    void draw();
    void update();
    bool isFinished() const;

    void tick(int frame);
};


#endif