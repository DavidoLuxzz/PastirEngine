#include <sprite/Drawable.hpp>

const char* Drawable::TEXTURES[] = {
    "block","stone", "grass","water", "plank","plank_on_water", "cobweb","plum","fence_full",
    "door","door_open","room","shade","block_corner","block_top","block_sides","block_end",
    "black","fence_left","fence_right","fence_no_conn","line_corner","line_top","line_sides",
    "line_end", "fasada", "grass0", "grass1","grass2", "grass3","grass4", "grass5", "grass6",
    "grass7","grass8","grass9", "grass10","grass11","grass12", "grass13","grass14","grass15",
    "dirt0","dirt1", "cobble0","cobble1","cobble2", "cobble3","cobble4", "cobble5","cobble6",
    "cobble7"
};

const int Drawable::SOLID_IDs[] = {
    TEXTURE_BLOCK, TEXTURE_WATER, TEXTURE_PLUM, TEXTURE_FENCE_FULL,
    TEXTURE_DOOR, TEXTURE_BLOCK_CORNER, TEXTURE_BLOCK_TOP, TEXTURE_BLOCK_SIDES,
    TEXTURE_BLOCK_END, TEXTURE_BLACK, TEXTURE_FENCE_LEFT, TEXTURE_FENCE_RIGHT, 
    TEXTURE_FENCE_NO_CONN, TEXTURE_LINE_CORNER, TEXTURE_LINE_TOP, TEXTURE_LINE_SIDES,
    TEXTURE_LINE_END
};

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
#include <game.hpp>
void Drawable::drawData(const DrawableData& data, float2 translate) {
    ALLEGRO_BITMAP* bitmap = bank::tileset::getBank(0)
                                .getTexture()
                                .getAllegroBitmap();
    if (!bitmap) return;
    Rectu rect = bank::tileset::getBank(0).getTile(data[COMP_TEXTURE_ID]);

    float PIXEL_SCALE = Display::getPixelScale();

    // full translated position
    float2 pos = {  static_cast<float>(data[COMP_X])/DEFAULT_PIXEL_SCALE + translate.x,
                    static_cast<float>(data[COMP_Y])/DEFAULT_PIXEL_SCALE + translate.y  };
    float angle = degreesToRadians(static_cast<float>(data[COMP_ANGLE]));

    float2 scale = {static_cast<float>(data[COMP_SCALEX])/100.0f, static_cast<float>(data[COMP_SCALEY])/100.0f};
    float3 hsb ={   static_cast<float>(data[COMP_TINT_HUE])/180.0f,
                    0.5f+static_cast<float>(data[COMP_TINT_SATURATION])/100.0f,
                    1.5f+static_cast<float>(data[COMP_TINT_BRIGHTNESS])/200.0f
                };

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
                                        al_color_hsl(hsb.x, hsb.y, hsb.z),
                                        // al_map_rgb(100,100,100),
                                        imageCenter.x, imageCenter.y,
                                        pos.x, pos.y,
                                        scale.x, scale.y,
                                        angle,
                                        0);
    // al_draw_bitmap(bitmap, pos.x+translate.x, pos.y+translate.y, 0);
}