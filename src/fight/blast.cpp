#include <fight/blast.hpp>
#include <allegro5/allegro_primitives.h>

Blast::Blast(float cy, float h) {
    centerY = cy; height = h;
}

void Blast::update() {
    anim.update();
}

void Blast::draw() {
    al_draw_filled_rectangle(0.f, centerY-height/2, 2000.f, centerY+height/2, al_map_rgb(255,255,255));
}