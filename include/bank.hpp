#pragma once
#ifndef __BANK_HPP
#define __BANK_HPP

#pragma region Texture Bank
#include <texture.hpp>

typedef int TextureID;

class TextureBank {
protected:
    int size, initialSize;
    Texture *contents;
public:
    TextureBank() = default;
    TextureBank(int initial_size);
    ~TextureBank() = default;

    /**
     * Init
     */
    int init(int initial_size);
    /**
     * Loads texture into bank
     * @return ID of the loaded texture
     */
    TextureID loadTexture(const char* filepath, int allegro_flags=0x0);
    /**
     * Loads texture in bank to speficied id
     * @return ID of the loaded texture
     *         (should be same as the specified id,
     *          otherwise consider it as an error)
     */
    TextureID loadTextureAt(TextureID id, const char* filepath, int allegro_flags=0x0);
    /**
     * Destroys specified texture.
     * That texture will NOT get removed from bank.
     * @param id the texture ID that will get destroyed
     */
    void destroy(TextureID);
    /// @brief destroys all textures (will NOT empty the bank)
    void destroyAll();
    /**
     * frees the texture heap array buffer.
     * You should call destroyAll() before this
     */
    void free();
};


#pragma endregion

#endif