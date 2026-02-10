#include <sprite/Player.hpp>
#include <allegro5/allegro.h>
#include <components/display.hpp>
#include <cmath>

void Player::move(float dx, float dy) {
    this->Sprite::move(dx,dy);
    orientate(dx,dy);
}

void Player::orientate(float _dx, float _dy) {
    
}

void Player::draw() {
    ALLEGRO_BITMAP* bitmap = bank::getTexture(texInfo).getAllegroBitmap();
    if (!bitmap) return;
    Rectu rect = bank::tileset::getBank(texInfo.bankID).getTile(0);

    Display::useCustomScale(2.0f,2.0f);

    al_draw_bitmap_region(bitmap,
        (float)rect.min.x,(float)rect.min.y,
        (float)rect.size.x,(float)rect.size.y,
        position.x+translate.x,position.y+translate.y,
        0
    );

    Display::useScale();
}