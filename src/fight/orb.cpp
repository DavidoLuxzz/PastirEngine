#include <fight/orb.hpp>
#include <allegro5/allegro_primitives.h>
#include <cmath>

#define SHADE_OFFSET 5.0f
#define IDLE_FRAMES 10

#define DIM_SHARPNESS 4.0f
#define BRIGHT_SHARPNESS 8.0f

Orb::Orb(float cx, float cy, float radius, int dim, float inc) {
    hitbox.center.x=cx;
    hitbox.center.y=cy;
    hitbox.radius = radius;

    // animation things
    numShades = radius/SHADE_OFFSET;
    increment = inc;
    decrement = 1./dim;

    incrementFrames = 1./inc;

    int cycleCount = -1;
    if (dim>0) cycleCount = incrementFrames + IDLE_FRAMES + dim;

    anim.init(0.0166667, cycleCount);
}

void Orb::update() {
    if (anim.update())
        tick(anim.frame);
}


#include <iostream>
void Orb::tick(int frame) {
    if (frame <= incrementFrames && visibility<0.99f) visibility+=increment;
    else if (frame > incrementFrames+IDLE_FRAMES) visibility -= decrement;
}

void Orb::draw(float2 translate) {

    for (int i=0; i<numShades; i++) {
        // todo
    }
}


bool Orb::isFinished() const {
    return anim.isFinished();
}

Circf Orb::getHitbox() const {
    return hitbox;
}