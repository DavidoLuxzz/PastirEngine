#include <sprite.hpp>

using float2 = simd::float2;



void Sprite::setPosition(float x, float y) {
    position[0] = x;
    position[1] = y;
}

float2 Sprite::getPosition() const {
    return position;
}



void Sprite::setTexture(const Texture& tex) {
    texture = tex;
}

const Texture& Sprite::getTexture() const {
    return texture;
}