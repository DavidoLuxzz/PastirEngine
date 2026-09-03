#include <fight/blast.hpp>
#include <allegro5/allegro_primitives.h>
#include <cmath>

#define SHADE_OFFSET 10.0f
#define IDLE_FRAMES 10

#define DIM_SHARPNESS 4.0f
#define BRIGHT_SHARPNESS 8.0f

Blast::Blast(float cy, float h, int dim, float inc) {
    centerY = cy; height = h;
    numShades = height/SHADE_OFFSET;
    increment = inc;
    decrement = 1./dim;

    incrementFrames = 1./inc;

    int cycleCount = -1;
    if (dim>0) cycleCount = incrementFrames + IDLE_FRAMES + dim;

    anim.init(16.6667/1000, cycleCount);
}

void Blast::update() {
    if (anim.update())
        tick(anim.frame);
}

float brght(float percent, float sharpness) {
    return powf(percent, sharpness);
    return (powf(sharpness, percent) - 1.0f) / (sharpness - 1.0f);
}
float dim(float percent, float sharpness) {
    // printf("dimming %f\n", 1.0f - powf(percent, sharpness));
    return 1.0f - powf(1.0f-percent, sharpness);
}

#include <iostream>
void Blast::tick(int frame) {
    if (frame <= incrementFrames && visibility<0.99f) visibility+=increment;
    else if (frame > incrementFrames+IDLE_FRAMES) visibility -= decrement;
}

void Blast::draw() {
    int shades = numShades*visibility;
    shades = numShades;
    for (int i=0; i<shades; i++) {
        float yoff = (i+1) * SHADE_OFFSET / 2;
        al_draw_filled_rectangle(
            0.f, centerY-yoff,
            2000.f, centerY+yoff,
            al_map_rgba(255,255,255, 
                (anim.frame > incrementFrames+IDLE_FRAMES)?
                64*dim(visibility, DIM_SHARPNESS-DIM_SHARPNESS*i/numShades) : // magic
                64*brght(visibility, BRIGHT_SHARPNESS+i*BRIGHT_SHARPNESS/2.0f))
        );
    }
}


bool Blast::isFinished() const {
    return anim.isFinished();
}