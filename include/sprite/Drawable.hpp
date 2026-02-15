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
    /**
     * @enum data_components
     * @brief Enumeration of all drawable component types for entity data storage.
     * 
     * This enum defines the indices for accessing various properties of drawable entities
     * in a component-based architecture. Each component represents a different attribute
     * that can be stored and manipulated for game objects.
     * 
     * @var COMP_TEXTURE_ID - Texture identifier for the drawable entity
     * @var COMP_X - X-coordinate position
     * @var COMP_Y - Y-coordinate position
     * @var COMP_SOLID - Solidity flag (collision property)
     * @var COMP_LAYER - Rendering layer/depth ordering
     * @var COMP_GROUP - Group identifier for entity categorization
     * @var COMP_ANGLE - Rotation angle in degrees
     * @var COMP_SCALEX - Horizontal scale/zoom factor
     * @var COMP_SCALEY - Vertical scale/zoom factor
     * @var COMP_SPECIAL - First special property (custom use)
     * @var COMP_SPECIAL2 - Second special property (custom use)
     * @var COMPONENT_COUNT - Total number of components (used for array sizing)
     */
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
        COMP_TINT_HUE,
        COMP_TINT_SATURATION,
        COMP_TINT_BRIGHTNESS,
        COMP_SPECIAL, // 12

        COMPONENT_COUNT
    };

    typedef std::array<int, data_components::COMPONENT_COUNT> DrawableData;
#define DRAWABLE_DEFAULT_DATA {0, 0, 0, 0, 0, 0, 0, 100, 100, 0, 0, 0}

    
    /**
     * Sorted list of texture file names
     * 
     * defined in Drawable.cpp
     */
    static const char* TEXTURES[];

    /**
     * @enum textureIDs
     * @brief Enumeration of texture identifiers used for drawable objects in the 2D game.
     * 
     * This enum defines all available textures used for rendering various game elements
     * including blocks, terrain, structures, and decorative elements.
     * 
     * @var TEXTURE_BLOCK Basic block texture
     * @var TEXTURE_STONE Stone block texture
     * @var TEXTURE_GRASS Grass block texture
     * @var TEXTURE_WATER Water block texture
     * @var TEXTURE_PLANK Wooden plank texture
     * @var TEXTURE_PLANKW Wooden plank variant texture
     * @var TEXTURE_COBWEB Cobweb texture
     * @var TEXTURE_PLUM Plum texture
     * @var TEXTURE_FENCE_FULL Full fence texture
     * @var TEXTURE_DOOR Closed door texture
     * @var TEXTURE_DOOR_OPEN Open door texture
     * @var TEXTURE_ROOM Room background texture
     * @var TEXTURE_SHADE Shading texture
     * @var TEXTURE_BLOCK_CORNER Block corner texture
     * @var TEXTURE_BLOCK_TOP Block top surface texture
     * @var TEXTURE_BLOCK_SIDES Block side surface texture
     * @var TEXTURE_BLOCK_END Block end surface texture
     * @var TEXTURE_BLACK Black texture
     * @var TEXTURE_FENCE_LEFT Left-side fence texture
     * @var TEXTURE_FENCE_RIGHT Right-side fence texture
     * @var TEXTURE_FENCE_NO_CONN Fence without connection texture
     * @var TEXTURE_LINE_CORNER Line corner texture
     * @var TEXTURE_LINE_TOP Line top texture
     * @var TEXTURE_LINE_SIDES Line side texture
     * @var TEXTURE_LINE_END Line end texture
     * @var TEXTURE_FASADA Facade texture
     * @var TEXTURE_GRASSX Extended grass texture
     * @var GRASS_TEXTURE_COUNT Number of grass texture variations (16)
     * @var TEXTURE_DIRT0 First dirt texture variant
     * @var TEXTURE_DIRT1 Second dirt texture variant
     * @var TEXTURE_COBBLEX Cobblestone extended texture
     * @var COBBLE_TEXTURE_COUNT Number of cobblestone texture variations (8)
     * @var DRAWABLE_TEXTURE_COUNT Total count of all drawable textures
     */
    enum textureIDs {
        TEXTURE_BLOCK  	        = 0,
        TEXTURE_STONE  		    = 1,
        TEXTURE_GRASS  		    = 2,
        TEXTURE_WATER  		    = 3,
        TEXTURE_PLANK  		    = 4,
        TEXTURE_PLANKW 		    = 5,
        TEXTURE_COBWEB 		    = 6,
        TEXTURE_PLUM   		    = 7,
        TEXTURE_FENCE_FULL	    = 8,
        TEXTURE_DOOR   		    = 9,
        TEXTURE_DOOR_OPEN  	    = 10,
        TEXTURE_ROOM		    = 11,
        TEXTURE_SHADE		    = 12,
        TEXTURE_BLOCK_CORNER    = 13,
        TEXTURE_BLOCK_TOP	    = 14,
        TEXTURE_BLOCK_SIDES     = 15,
        TEXTURE_BLOCK_END       = 16,
        TEXTURE_BLACK           = 17,
        TEXTURE_FENCE_LEFT	    = 18,
        TEXTURE_FENCE_RIGHT	    = 19,
        TEXTURE_FENCE_NO_CONN   = 20,
        TEXTURE_LINE_CORNER     = 21,
        TEXTURE_LINE_TOP        = 22,
        TEXTURE_LINE_SIDES      = 23,
        TEXTURE_LINE_END        = 24,
        TEXTURE_FASADA          = 25,
        TEXTURE_GRASSX          = 26,
        GRASS_TEXTURE_COUNT     = 16,
        TEXTURE_DIRT0           = 42,
        TEXTURE_DIRT1           = 43,
        TEXTURE_COBBLEX         = 44,
        COBBLE_TEXTURE_COUNT    = 8,

        DRAWABLE_TEXTURE_COUNT  = TEXTURE_COBBLEX+COBBLE_TEXTURE_COUNT
    };
    
    static const int SOLID_IDs[];

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
};

#endif