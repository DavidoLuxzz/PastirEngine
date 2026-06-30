#include <sprite/StaticEntity.hpp>

StaticEntity::StaticEntity() {
    static constexpr bank::TextureInfo nikeTex = {
        .bankType = bank::TILESET,
        .bankID = bank::tileset::ENTITY0,
        .tileID = 0
    };
    setTexture(nikeTex);
    setScale(0.25f);
}