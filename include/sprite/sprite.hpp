#pragma once
#ifndef __SPRITE_HPP
#define __SPRITE_HPP

#include <sprite/texture.hpp>
#include <bank.hpp>
#include <data_types.hpp>

class Sprite {
protected:
    // cannot have its own private texture
    // but instead can have a bank texture id :)
    bank::TextureInfo texInfo = {
        bank::bank_type::MULTITEX,0,-1,{{0,0},{16,16}}
    };

    float2 position = {0,0};
    float2 translate = {0,0};
    float scale = 1.0f;
public:
    Sprite() = default;
    ~Sprite() = default;

    using uint = unsigned int;
    void setTile(const Rectu&);
    void setTile(uint minx, uint miny, uint width, uint height);
    Rectu getTile() const;
    void setTileID(TextureID);
    TextureID getTileID() const;

    void setScale(float);
    float getScale() const;

    Rectf getHitbox() const;

    /**
     * Sets the position of the sprite.
     * Doesn't affect translation
     * @param x X coordinate
     * @param y Y coordinate
     */
    void setPosition(float x, float y);
    void setPosition(float2);
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


    void setCenter(float x, float y);

    /// @brief Like offset
    /// @param tx 
    /// @param ty 
    void setTranslate(float tx, float ty);
    void setTranslate(float2);
    float2 getTranslate() const;

    /// @brief This gets added to translate value
    /// @param dx 
    /// @param dy 
    void move(float dx, float dy);

    /**
     * Draws whole bitmap.
     * Doesn't matter what's the tileRect configured
     */
    void drawWhole();

    /**
     * Draws the bitmap region (tileRect).
     */
    void draw();


    void setTexture(const bank::TextureInfo&);
    bank::TextureInfo getTexture() const;
    /** Sets the texture's bank type.
     * @param _bank
     */
    void setTexturesBankType(bank::bank_type);
    /// @return Returns the bank where the sprite's texture is stored.
    bank::bank_type getTexturesBankType() const;
    /** Sets the texture's bank.
     *  TextureID won't change after changing bank
     * @param _bank
     */
    void setTexturesBankID(unsigned int _bank);
    /// @return Returns the bank where the sprite's texture is stored.
    unsigned int getTexturesBankID() const;
    /// @brief Speficy texture
    /// @param texture
    void setTextureID(TextureID texture);
    /// @brief Returns the currently used texture's bank ID @code{TextureID textureID}
    /// @return bank texture ID
    TextureID getTextureID() const;
};



#endif