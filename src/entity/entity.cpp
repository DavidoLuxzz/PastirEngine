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

    float2 accel = ppos-getPosition(); float accel_intenzitet = 0.05f;
    float2 F = accel - (normalized(v)*accel_intenzitet);
    accel += F;
    
    normalize(accel);
    accel *= accel_intenzitet;

    v += accel;
    constexpr static float max_velo = 3.0f;
    float c = hypotf(v.x,v.y);
    if (c>max_velo) {
        normalize(v);
        v *= max_velo;
    }

    setPosition(getPosition() + v);
}