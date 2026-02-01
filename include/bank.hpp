#pragma once
#ifndef __BANK_HPP
#define __BANK_HPP

#pragma region Texture Bank
#include <sprite/texture.hpp>

typedef int TextureID;

class TextureBank {
protected:
    int size=0, initialSize;
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
     * 
     */
    int loadTextures(const char* prefix, const char* (&textureFileNames)[], unsigned int start, unsigned int count, const char* suffix, int allegro_flags=0x0);
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
     * Returns the Texture at specified ID
     * @returns textures[id]
     */
    const Texture& getTexture(TextureID id) const;
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



namespace bank {
    /**
     * Initializes the TextureBank bank with given bank count.
     */
    void init(unsigned int num_banks);
    /**
     * Destroys all banks in list.
     */
    void destroyAll();
    /**
     * Frees whole bank list. Should be now initializable again (ofc not recommended)
     */
    void free();
    /**
     * Makes bank global at given index. [copy] done with operator=
     * Bank will be accessible with getBank(index).
     */
    void makeGlobal(TextureBank& bank, unsigned int index);

    /**
     * @returns TextureBank at index
     */
    const TextureBank& getBank(unsigned int index);
} // namespace bank

#define BANK_MAP_DRAWABLE_TEXTUREBANK 0


#pragma endregion

#endif