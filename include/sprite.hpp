#pragma once
#ifndef __SPRITE_HPP
#define __SPRITE_HPP

#include <texture.hpp>
#include <simd/simd.h>

class Sprite {
    using float2 = simd::float2;
private:
    Texture texture;
    float2 position;
public:
    Sprite() = default;
    ~Sprite() = default;

    /**
     * Sets the position of the sprite
     * @param x X coordinate
     * @param y Y coordinate
     */
    void setPosition(float x, float y);
    /// @brief Returns the current position @code{float2 position}
    /// @return position
    float2 getPosition() const;


    /// @brief Speficy texture
    /// @param texture
    void setTexture(const Texture&);
    /// @brief Returns the currently used texture @code{Texture texture}
    /// @return texture
    const Texture& getTexture() const;
};



#endif