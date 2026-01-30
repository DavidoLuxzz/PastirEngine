#include <sprite.hpp>


void Sprite::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

float2 Sprite::getPosition() const {
    return position;
}



void Sprite::setTextureID(TextureID tex) {
    textureID = tex;
}

TextureID Sprite::getTextureID() const {
    return textureID;
}