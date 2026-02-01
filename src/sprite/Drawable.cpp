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
}