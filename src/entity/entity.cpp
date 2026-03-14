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
void Entity::update(float ms) {
    setTranslate(game::getGame()->rooms[game::getGame()->roomID].getTranslate());
}