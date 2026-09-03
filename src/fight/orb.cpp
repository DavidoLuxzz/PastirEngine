#include <fight/orb.hpp>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <game/game.hpp>

#define MAX_VELOCITY 15.f

#define IDLE_FRAMES 10

#define DIM_SHARPNESS 4.0f
#define BRIGHT_SHARPNESS 8.0f

Orb::Orb(float cx, float cy, float radius, int dim, float inc) {
    shape.center.x=cx;
    shape.center.y=cy;
    shape.radius = radius;

    // animation things
    numShades = 10;
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

void Orb::tick(int frame) {
    if (frame <= incrementFrames && visibility<0.99f) visibility+=increment;
    // else if (frame > incrementFrames+IDLE_FRAMES) visibility -= decrement;

    Player& player = Game::getGame()->player;

    float2 dir = player.getWorldCenter()-shape.center;
    normalize(dir);

    velocity += dir;
    if (hypotf(velocity.x,velocity.y)>MAX_VELOCITY){
        normalize(velocity);
        velocity*=MAX_VELOCITY;
    }

    shape.center += velocity;
}

void Orb::draw(float2 translate) {
    
    for (int i=0; i<numShades; i++) {
        float R = shape.radius * (i+1)/numShades;
        al_draw_filled_circle(
            shape.center.x,shape.center.y,
            shape.radius*cosf((float)i/numShades),
            al_map_rgba(0,0,0,40*visibility)
        );
    }
}


bool Orb::isFinished() const {
    return anim.isFinished();
}

Circf Orb::getHitbox() const {
    Circf hitbox = shape;
    hitbox.radius *= 0.8f;
    hitbox.center.y += hitbox.radius*0.15f;
    return hitbox;
}