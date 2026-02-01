#pragma once
#ifndef __SPRITE_HPP
#define __SPRITE_HPP

#include <sprite/texture.hpp>
#include <bank.hpp>
#include <data_types.hpp>

class Sprite {
private:
    // cannot have its own private texture
    // but instead can have a bank texture id :)
    TextureID textureID = -1;
    float2 position = {0,0};
    float2 translate = {0,0};
public:
    Sprite() = default;
    ~Sprite() = default;

    /**
     * Sets the position of the sprite.
     * Doesn't affect translation
     * @param x X coordinate
     * @param y Y coordinate
     */
    void setPosition(float x, float y);
    /// @brief Returns the current position @code{float2 position}
    /// Doesn't come with translation.
    /// @return position
    float2 getPosition() const;
    /**
     * @return getPosition() + getTranslate()
     */
    float2 getFullPosition() const;
    float getX() const;
    float getY() const;

    /// @brief Like offset
    /// @param tx 
    /// @param ty 
    void setTranslate(float tx, float ty);
    float2 getTranslate() const;

    /// @brief This gets added to translate value
    /// @param dx 
    /// @param dy 
    void move(float dx, float dy);

    /**
     * Draw
     */
    void draw();


    /// @brief Speficy texture
    /// @param texture
    void setTextureID(TextureID texture);
    /// @brief Returns the currently used texture's bank ID @code{TextureID textureID}
    /// @return bank texture ID
    TextureID getTextureID() const;
};



#endif