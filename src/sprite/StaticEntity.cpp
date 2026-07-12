#include <sprite/StaticEntity.hpp>
#include <iostream>

StaticEntity::StaticEntity() {
    static constexpr bank::TextureInfo nikeTex = {
        .bankType = bank::TILESET,
        .bankID = bank::tileset::ENTITY0,
        .tileID = 0
    };
    setTexture(nikeTex);
    setScale(0.25f);
}

StaticEntity::StaticEntity(const EntityData& _data) {
    setPosition(_data[COMP_X]/4.0f, _data[COMP_Y]/4.0f);
    const bank::TextureInfo nikeTex = {
        .bankType = bank::TILESET,
        .bankID = bank::tileset::ENTITY0,
        .tileID = _data[COMP_TEXTURE]
    };
    setTexture(nikeTex);
}

Rectf StaticEntity::getHitbox() const {
    float2 size = {(float) texInfo.tileRect.size.x,(float) texInfo.tileRect.size.y};
    if (texInfo.bankType == bank::TILESET){
        size.x = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.x;
        size.y = bank::tileset::getBank(texInfo.bankID).getTile(texInfo.tileID).size.y;
    }
    Rectf hitbox = {
        getPosition(), size * scale
    };
    return hitbox;
}


#include <components/display.hpp>
#include <game/game.hpp>

void StaticEntity::drawData(const EntityData& data, float2 translate) {
    ALLEGRO_BITMAP* bitmap = bank::tileset::getBank(bank::tileset::ENTITY0)
                                .getTexture()
                                .getAllegroBitmap();
    if (!bitmap) return;
    Rectu rect = bank::tileset::getBank(bank::tileset::ENTITY0).getTile(data[COMP_TEXTURE]);

    float PIXEL_SCALE = Display::getPixelScale();

    // full translated position
    float2 pos = {  static_cast<float>(data[COMP_X])/DEFAULT_PIXEL_SCALE + translate.x,
                    static_cast<float>(data[COMP_Y])/DEFAULT_PIXEL_SCALE + translate.y  };
    // float angle = degreesToRadians(static_cast<float>(data[COMP_ANGLE]));
    static constexpr float angle = 0.0f;

    //std::cout << "Ent Pos: " << pos.x << ", " << pos.y << std::endl;

    float2 scale = {static_cast<float>(data[COMP_SCALEX])/100.0f, static_cast<float>(data[COMP_SCALEY])/100.0f};
    // scale.x = 1.0f;
    // scale.y = 1.0f;
    // float3 hsb ={   static_cast<float>(data[COMP_TINT_HUE])/180.0f,
                //     0.5f+static_cast<float>(data[COMP_TINT_SATURATION])/100.0f,
                //     1.5f+static_cast<float>(data[COMP_TINT_BRIGHTNESS])/200.0f
                // };

    float __winw = (float) al_get_display_width (al_get_current_display());
    float __winh = (float) al_get_display_height(al_get_current_display());
    float __imgw = (float) al_get_bitmap_width (bitmap);
    float __imgh = (float) al_get_bitmap_height(bitmap);
    // clipping
    if (pos.x < -__imgw*scale.x || pos.y < -__imgh*scale.y) return; // clip (won't be visible on screen anyway)
    if (pos.x*PIXEL_SCALE >= __winw || pos.y*PIXEL_SCALE >= __winh) return; // clip (won't be visible on screen anyway)
    
    // final draw with calculated parameters
    al_draw_scaled_bitmap(
        bitmap,
        (float) rect.min.x, (float) rect.min.y,
        (float) rect.size.x, (float) rect.size.y,
        pos.x, pos.y,
        ((float)rect.size.x)*scale.x, ((float)rect.size.y)*scale.y,
        0
    );
}

Rectf StaticEntity::createHitbox(const EntityData& data, float2 translate) {
    Rectu tile = bank::tileset::getBank(bank::tileset::ENTITY0).getTile(data[COMP_TEXTURE]);
    // Drawable::worldCoordinates(2) radi za sve: position/DEFAULT_PIXEL_SCALE
    float2 coords = Drawable::worldCoordinates(data[COMP_X],data[COMP_Y]);
    float scalex = data[COMP_SCALEX]/100.0f, scaley = data[COMP_SCALEY]/100.0f;
    Rectf hitbox = {
        {coords.x+translate.x, coords.y+translate.y + tile.size.y*scaley /2},
        {tile.size.x*scalex, tile.size.y*scaley * 2/4}
    };
    return hitbox;
}

float StaticEntity::getFeetY(const EntityData& data) {
    return data[COMP_Y]/DEFAULT_PIXEL_SCALE + bank::tileset::getBank(bank::tileset::ENTITY0).getTile(data[COMP_TEXTURE]).size.y * data[COMP_SCALEY] / 100.0f;
}