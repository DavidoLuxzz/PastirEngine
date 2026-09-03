#include <fight/blast.hpp>
#include <allegro5/allegro_primitives.h>
#include <cmath>

#define SHADE_OFFSET 10.0f
#define IDLE_FRAMES 10

#define DIM_SHARPNESS 4.0f
#define BRIGHT_SHARPNESS 8.0f

Blast::Blast(BlasterType typ, float cy, float h, int dim, float inc) {
    btype = typ;
    center = cy; height = h;

    // animation things
    numShades = height/SHADE_OFFSET;
    increment = inc;
    decrement = 1./dim;

    incrementFrames = 1./inc;

    int cycleCount = -1;
    if (dim>0) cycleCount = incrementFrames + IDLE_FRAMES + dim;

    anim.init(0.0166667, cycleCount);
}

void Blast::update() {
    if (anim.update())
        tick(anim.frame);
}

#include <iostream>
void Blast::tick(int frame) {
    if (frame <= incrementFrames && visibility<0.99f) visibility+=increment;
    else if (frame > incrementFrames+IDLE_FRAMES) visibility -= decrement;
}

void Blast::draw(float2 translate) {
    
    float2 xx,yy;
    if (btype==HORIZONTAL) {
        xx.x = -2000.f; xx.y = 2000.f;
        yy.x = center  + translate.y;
        yy.y = center  + translate.y;
    } else { // VERTICAL
        yy.x = -2000.f; yy.y = 2000.f;
        xx.x = center  + translate.y;
        xx.y = center  + translate.y;
    }


    int shades = numShades*visibility;
    shades = numShades;

    for (int i=0; i<shades; i++) {
        al_draw_filled_rectangle(
            xx.x, yy.x,
            xx.y, yy.y,
            al_map_rgba(255,255,255, 
                (anim.frame > incrementFrames+IDLE_FRAMES)?
                64*dim(visibility, DIM_SHARPNESS-DIM_SHARPNESS*i/numShades) : // magic
                64*brght(visibility, BRIGHT_SHARPNESS+i*BRIGHT_SHARPNESS/2.0f))
        );
        float off = SHADE_OFFSET / 2;
        if (btype==HORIZONTAL) {
            yy.x -= off; yy.y += off;
        } else {
            xx.x -= off; xx.y += off;
        }
    }
}


bool Blast::isFinished() const {
    return anim.isFinished();
}

Rectf Blast::getHitbox() const {
    float h = height * brght(visibility, (anim.frame>incrementFrames)? 2.0f : BRIGHT_SHARPNESS);
    if (h < 10.f) return {{NAN,NAN},{0,0}};
    
    if (btype==HORIZONTAL) return {
        {-2000.f, center-h/2},
        { 4000.f, h}
    };
    return {
        {center-h/2, -2000.f},
        {h,           4000.f}
    };
}