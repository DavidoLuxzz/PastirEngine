#include <sprite/sprite.hpp>


void Sprite::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

float2 Sprite::getPosition() const {
    return position;
}
float Sprite::getX() const {
    return position.x;
}
float Sprite::getY() const {
    return position.y;
}

float2 Sprite::getFullPosition() const {
    return getPosition() + getTranslate();
}

void Sprite::setTranslate(float tx, float ty) {
    translate.x = tx;
    translate.y = ty;
}
float2 Sprite::getTranslate() const {
    return translate;
}

void Sprite::move(float dx, float dy) {
    translate.x += dx;
    translate.y += dy;
}

void Sprite::setTexturesBankType(bank::bank_type type) {
    texInfo.bankType = type;
}
bank::bank_type Sprite::getTexturesBankType() const {
    return texInfo.bankType;
}
void Sprite::setTexturesBankID(unsigned int bnk) {
    texInfo.bankID = bnk;
}
unsigned int Sprite::getTexturesBankID() const {
    return texInfo.bankID;
}

void Sprite::setTextureID(TextureID tex) {
    texInfo.textureID = tex;
}

TextureID Sprite::getTextureID() const {
    return texInfo.textureID;
}

void Sprite::setTile(const Rectu& rect) {
    texInfo.tileRect = rect;
}
void Sprite::setTile(uint mx, uint my, uint w, uint h) {
    texInfo.tileRect.min.x = mx;
    texInfo.tileRect.min.y = my;
    texInfo.tileRect.size.x = w;
    texInfo.tileRect.size.y = h;
}
Rectu Sprite::getTile() const {
    return texInfo.tileRect;
}
void Sprite::setTileID(TextureID id) {
    texInfo.tileID = id;
}
TextureID Sprite::getTileID() const {
    return texInfo.tileID;
}


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
void Sprite::drawWhole(){
    ALLEGRO_BITMAP* bitmap = bank::getTexture(texInfo).getAllegroBitmap();
    if (!bitmap) return;
    // al_draw_tinted_scaled_rotated_bitmap(bitmap, al_map_rgba(100,100,100, 100), cx, cy, dx, dy, xscale, yscale, angle,  flags);
    al_draw_bitmap(bitmap, position.x+translate.x, position.y+translate.y, 0);
}

void Sprite::draw() {
    ALLEGRO_BITMAP* bitmap = bank::getTexture(texInfo).getAllegroBitmap();
    if (!bitmap) return;
    al_draw_bitmap_region(bitmap,
        (float)texInfo.tileRect.min.x, (float)texInfo.tileRect.min.y,
        (float)texInfo.tileRect.size.x, (float)texInfo.tileRect.size.y,
        position.x+translate.x, position.y+translate.y,
        0
    );
}