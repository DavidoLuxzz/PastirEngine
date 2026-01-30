#pragma once
#ifndef __SPRITE_HPP
#define __SPRITE_HPP

#include <texture.hpp>
#include <bank.hpp>
#include <data_types.hpp>

class Sprite {
private:
    // cannot have its own private texture
    // but instead can have a bank texture id :)
    TextureID textureID;
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
    void setTextureID(TextureID texture);
    /// @brief Returns the currently used texture's bank ID @code{TextureID textureID}
    /// @return bank texture ID
    TextureID getTextureID() const;
};



#endif