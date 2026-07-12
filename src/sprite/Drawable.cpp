#include <sprite/Drawable.hpp>
#include <game/game.hpp>

Drawable::Drawable(TextureID texture, float x, float y) {
    init(texture, x, y);
}
void Drawable::init(TextureID tex, float x, float y) {
    setTextureID(tex);
    setPosition(x,y);
    data[COMP_TEXTURE_ID] = tex;
    data[COMP_X] = (int) round(x);
    data[COMP_Y] = (int) round(y);
}

Drawable::Drawable(DrawableData& data) {
    init(data);
}

void Drawable::init(DrawableData& _data) {
    data = _data;
}

float2 Drawable::worldCoordinates(int x, int y) {
    return {x/DEFAULT_PIXEL_SCALE, y/DEFAULT_PIXEL_SCALE};
}

Rectf Drawable::createHitbox(const DrawableData& data, float2 translate) {
    float2 coords = Drawable::worldCoordinates(data[COMP_X],data[COMP_Y]);
    if (data[COMP_TYPE] == TYPE_HITBOX) {
        Rectf hitbox = {
            {coords.x+translate.x, coords.y+translate.y},
            {data[COMP_WIDTH] * data[COMP_SCALEX]/100.0f, data[COMP_HEIGHT] * data[COMP_SCALEY]/100.0f}
        };
        //printf("Hitbox w,h: %.1f %.1f\n", hitbox);
        return hitbox;
    }
    Rectu tile = bank::tileset::getBank(bank::tileset::MAP_DRAWABLES).getTile(data[COMP_TEXTURE_ID]);
    Rectf hitbox = {
        {coords.x+translate.x, coords.y+translate.y},
        {tile.size.x * data[COMP_SCALEX]/100.0f, tile.size.y * data[COMP_SCALEY]/100.0f}
    };
    return hitbox;
}

float Drawable::getWorldFeetY(const DrawableData& data) {
    return data[COMP_Y]/DEFAULT_PIXEL_SCALE + bank::tileset::getBank(bank::tileset::MAP_DRAWABLES).getTile(data[COMP_TEXTURE_ID]).size.y * data[COMP_SCALEY] / 100.0f;
}

void Drawable::draw() {
    Drawable::drawData(data, translate);
}

#include <cmath>
float degreesToRadians(float degrees) {
    return degrees * M_PI / 180.0;
}
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <components/display.hpp>
void Drawable::drawData(const DrawableData& data, float2 translate) {
    ALLEGRO_BITMAP* bitmap = bank::tileset::getBank(bank::tileset::MAP_DRAWABLES)
                                .getTexture()
                                .getAllegroBitmap();
    if (!bitmap) return;
    Rectu rect = bank::tileset::getBank(bank::tileset::MAP_DRAWABLES).getTile(data[COMP_TEXTURE_ID]);

    float PIXEL_SCALE = Display::getPixelScale();

    // full translated position
    float2 pos = {  static_cast<float>(data[COMP_X])/DEFAULT_PIXEL_SCALE + translate.x,
                    static_cast<float>(data[COMP_Y])/DEFAULT_PIXEL_SCALE + translate.y  };
    float angle = degreesToRadians(static_cast<float>(data[COMP_ANGLE]));

    float2 scale = {static_cast<float>(data[COMP_SCALEX])/100.0f, static_cast<float>(data[COMP_SCALEY])/100.0f};

    float __winw = (float) al_get_display_width (al_get_current_display());
    float __winh = (float) al_get_display_height(al_get_current_display());
    float __imgw = (float) al_get_bitmap_width (bitmap);
    float __imgh = (float) al_get_bitmap_height(bitmap);
    // clipping
    if (pos.x < -__imgw*scale.x || pos.y < -__imgh*scale.y) return; // clip (won't be visible on screen anyway)
    if (pos.x*PIXEL_SCALE >= __winw || pos.y*PIXEL_SCALE >= __winh) return; // clip (won't be visible on screen anyway)

    static const float2 imageCenter = {0.0f, 0.0f};
    al_draw_tinted_scaled_rotated_bitmap_region(bitmap,
                                        (float)rect.min.x,(float)rect.min.y,(float)rect.size.x,(float)rect.size.y,
                                        al_map_rgb(255,255,255),
                                        imageCenter.x, imageCenter.y,
                                        pos.x, pos.y,
                                        scale.x, scale.y,
                                        angle,
                                        0);
    // al_draw_bitmap(bitmap, pos.x+translate.x, pos.y+translate.y, 0);
}