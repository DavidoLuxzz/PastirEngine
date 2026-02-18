#pragma once
#ifndef __BANK_HPP
#define __BANK_HPP

#pragma region MultiTexture Bank
#include <sprite/texture.hpp>

typedef int TextureID;

/**
 * Bank that contains multiple textures.
 * Not their tile rects tho.
 * If you have one texture and want to store their tile positions,
 * then consider using TilesetBank instead.
 */
class MultiTextureBank {
protected:
    int size=0, initialSize;
    Texture *contents;
public:
    MultiTextureBank() = default;
    MultiTextureBank(int initial_size);
    ~MultiTextureBank() = default;

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
#pragma endregion

#pragma region Tileset Bank

#include <vector>
#include <data_types.hpp>
/**
 * Bank that contains one texture with multiple tile rects.
 */
class TilesetBank {
protected:
    Texture texture;
    std::vector<Rectu> tileRects;
public:
    TilesetBank() = default;
    ~TilesetBank() = default;

    // constexpr TilesetBank &operator=(const TilesetBank &);

    /**
     * Loads texture into bank
     * @return err code
     */
    int loadTexture(const char* filepath, int allegro_flags=0x0);
    /**
     * Loads the tile rects. Stored in certain file
     * @return err code
     */
    int loadTileRects(const char* tilerectsfile);
    /**
     * Adds tile rect to the list
     */
    void registerTile(const Rectu);
    /**
     * Returns the Texture at specified ID
     * @returns textures[id]
     */
    const Texture& getTexture() const;
    /**
     * Returns the tile rect for specified drawable.
     * @returns tile rect for drawable
     */
    Rectu getTile(int drawableID) const;
    /**
     * Destroys specified texture.
     * That texture will NOT get removed from bank.
     * @param id the texture ID that will get destroyed
     */
    void destroy();
};
#pragma endregion

#pragma region namespace bank

/// TODO: Staviti sve drawable texture u jedan tileset. Sve player texture u jedan tileset. I onda ce da postoji samo jedna banka
namespace bank {
    namespace multitex {
        /**
         * Initializes the MultiTextureBank bank with given bank count.
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
        void makeGlobal(MultiTextureBank& bank, unsigned int index);

        /**
         * @returns TextureBank at index
         */
        const MultiTextureBank& getBank(unsigned int index);
    }
    namespace tileset {
        enum tileset_banks {
            MAP_DRAWABLES,
            PLAYER,
            DIALOG_BOX,

            NUM_KNOWN_BANKS
        };
        /**
         * Initializes the TextureBank bank with given bank count.
         */
        void init(unsigned int num_banks);
        /**
         * Destroys all banks in list.
         */
        void destroyAll();
        void destroy(unsigned int index);
        /**
         * Frees whole bank list. Should be now initializable again (ofc not recommended)
         */
        void free();
        /**
         * Makes bank global at given index. [copy] done with operator=
         * Bank will be accessible with getBank(index).
         * 
         * (Old bank gets overwritten and destroyed.)
         */
        void makeGlobal(TilesetBank& bank, unsigned int index);

        /**
         * @returns TilesetBank at index
         */
        TilesetBank& getBank(unsigned int index);
    }


    enum bank_type {
        MULTITEX,
        TILESET
    };


    /**
     * Describes the texture.
     *  - in which bank it is
     *  - texture id
     *  - ...
     */
    struct TextureInfo {
        // bank (first parameter)
        bank_type bankType;
        unsigned int bankID;
        // texture
        union { // second parameter
            TextureID textureID; // used in multitex
            TextureID tileID; // used in tilesets
        };
        // third (optional) parameter
        // only used in alone textures
        Rectu tileRect;
    };


    
    const Texture& getTexture(const TextureInfo&);



    void destroyAll();

} // namespace bank


#pragma endregion

#endif