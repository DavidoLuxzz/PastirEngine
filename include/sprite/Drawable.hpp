#pragma once
#ifndef __DRAWABLE_HPP
#define __DRAWABLE_HPP

#include <sprite/sprite.hpp>
#include <array>

/**
 * @class Drawable
 * Drawables are all the visible map components (tiles, i ona cuda)
 * like and subRscribe, make sur to hit dat bel
 */
class Drawable : public Sprite {
protected:
public:    

    enum data_components {
        COMP_TEXTURE_ID, // 0
        COMP_X,
        COMP_Y,
        COMP_SOLID,
        COMP_LAYER,
        COMP_GROUP,
        COMP_ANGLE,
        COMP_SCALEX,
        COMP_SCALEY,
        COMP_TYPE,
        COMP_WIDTH,
        COMP_HEIGHT,
        COMP_SPECIAL, // 12

        COMPONENT_COUNT
    };

    enum drawable_types {
        /**
         * Obican tip.
         */
        TYPE_NONE,
        /**
         * Hitboxovi nisu namenjeni da se vide => tekstura im nije bitna.
         * Namenjeni su samo da pomognu, da ne bi morao novi tip da pravim i slicno.
         * Samo kod ovog tipa se koriste COMP_WIDTH i COMP_HEIGHT.
         */
        TYPE_HITBOX,

        NUM_DRAWABLE_TYPES
    };

    typedef std::array<int, data_components::COMPONENT_COUNT> DrawableData;
#define DRAWABLE_DEFAULT_DATA {0, 0, 0, 0, 0, 0, 0, 100, 100, 0, 0, 0}


    DrawableData data;

    Drawable() = default;
    Drawable(TextureID texture, float x=0.0f, float y=0.0f);
    Drawable(DrawableData& data);

    void init(TextureID texture, float x=0.0f, float y=0.0f);
    void init(DrawableData& data);

    /**
     * Prebaci x i y u game koordinate
     * @brief <comp>/DEFAULT_PIXEL_SCALE.  64 -> 16.0f
     * @return game koordinate
     */
    static float2 worldCoordinates(int x, int y);
    static Rectf createHitbox(const DrawableData& data, float2 translate={0,0});

    /// @brief calls drawData(data);
    void draw();

    static void drawData(const DrawableData& data, float2 translate={0,0});

    /// returns bottom y-coordinate
    static float getWorldFeetY(const DrawableData& data);
};

#endif