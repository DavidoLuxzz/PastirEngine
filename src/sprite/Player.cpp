#include <sprite/Player.hpp>
#include <allegro5/allegro.h>
#include <components/display.hpp>
#include <cmath>

Player::Player() {
    texInfo.tileID = 0;
    animation.init(0.2);
}

void Player::move(float dx, float dy) {
    this->Sprite::move(dx,dy);
    // orientate(dx,dy);
}

float Player::getSpeed() const {
    return speed*speedmul;
}
void Player::setSpeedMul(float v) {
    speedmul = v;
}

void Player::useNikes(bool t) {
    usingNikes = t;
}

void Player::orientate(float _dx, float _dy) {
    if (_dy>0.0f) setTileByDirection(DIR_DOWN);
    else if (_dy<0.0f) setTileByDirection(DIR_UP);
    else if (_dx>0.0f) setTileByDirection(DIR_RIGHT);
    else if (_dx<0.0f) setTileByDirection(DIR_LEFT);
    animation.update();
}

void Player::setTileByDirection(directions dir) {
    texInfo.tileID = dir;
}
void Player::draw() {
    ALLEGRO_BITMAP* bitmap = bank::getTexture(texInfo).getAllegroBitmap();
    if (!bitmap) return;
    Rectu rect = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID);
    rect.min.x += (animation.frame%4)*rect.size.x;
    if (usingNikes) rect.min.y += rect.size.y*2;

    al_draw_tinted_scaled_rotated_bitmap_region(bitmap,
                                        (float)rect.min.x,(float)rect.min.y,
                                        (float)rect.size.x,(float)rect.size.y,
                                        al_map_rgb_f(1.0f,1.0f,1.0f),
                                        // al_map_rgb(100,100,100),
                                        0.0f, 0.0f,
                                        position.x+translate.x, position.y+translate.y,
                                        scale, scale,
                                        0.0f,
                                        0);
}