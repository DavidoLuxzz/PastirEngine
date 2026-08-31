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
public:
    Blast(float cy, float height);
    void draw();
    void update();
};


#endif