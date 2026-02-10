#include <sprite/Player.hpp>
#include <allegro5/allegro.h>
#include <components/display.hpp>
#include <cmath>

Player::Player() {
    texInfo.tileID = 0;
    animation.init(0.2);
}

void Player::_animTick(int frame) {
    currentFrame = frame%4;
}

void Player::move(float dx, float dy) {
    // this->Sprite::move(dx,dy);
    orientate(dx,dy);
}

void Player::orientate(float _dx, float _dy) {
    if (_dy>0.0f) setTileByDirection(DIR_DOWN);
    else if (_dy<0.0f) setTileByDirection(DIR_UP);
    else if (_dx>0.0f) setTileByDirection(DIR_RIGHT);
    else if (_dx<0.0f) setTileByDirection(DIR_LEFT);
    animation.update();
    currentFrame = animation.frame%4;
}

void Player::setTileByDirection(directions dir) {
    texInfo.tileID = dir;
}

void Player::draw() {
    ALLEGRO_BITMAP* bitmap = bank::getTexture(texInfo).getAllegroBitmap();
    if (!bitmap) return;
    Rectu rect = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID);
    rect.min.x += currentFrame*32;

    Display::useCustomScale(2.0f,2.0f);

    al_draw_bitmap_region(bitmap,
        (float)rect.min.x,(float)rect.min.y,
        (float)rect.size.x,(float)rect.size.y,
        position.x+translate.x,position.y+translate.y,
        0
    );

    Display::useScale();
}