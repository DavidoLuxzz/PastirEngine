#include <entity/entity.hpp>

void Entity::init(unsigned int bank) {
    texInfo = bank::TextureInfo{
        .bankID = bank,
        .bankType = bank::TILESET,
        .tileID = 0
    };
}

void Entity::draw() {
    Sprite::draw();
}
#include <game.hpp>
#include <cmath>
void Entity::update(float ms) {
    setTranslate(game::getGame()->rooms[game::getGame()->roomID].getTranslate());
    float2 ppos = game::getGame()->player.getWorldPosition();

    float2 delta = ppos-getPosition();
    float c = hypotf(ppos.x-getPositionX(), ppos.y-getPositionY()); // distance do playera
    if (c<0.2f) return;
    delta.x /= c;
    delta.y /= c;
    setPosition(getPosition() + delta * 0.1f);
}