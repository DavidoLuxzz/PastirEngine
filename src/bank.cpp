#include <bank.hpp>
#include <iostream>
#include <data_types.hpp>
#include <components/utility.hpp>

// ## MULTI TEXTURE BANK ## //

#pragma region MultiTexture Bank

MultiTextureBank::MultiTextureBank(int initial_size) {
    init(initial_size);
}

int MultiTextureBank::init(int size) {
    initialSize = size;
    contents = new Texture[size];
    return contents==NULL;
}

int MultiTextureBank::loadTextures(const char *prefix, const char* (&textureFileNames)[], unsigned int start, unsigned int count, const char *suffix, int allegro_flags) {
    int err=0;
    for (unsigned int i=0; i<count; i++) {
        std::string full="";
        if (prefix) full += prefix;
        //std::cout << textureFileNames[start+i]  << std::endl;
        if (!textureFileNames[start+i]) {
            fprintf(stderr, "[TEXERR] Texture file name at index=%u ==NULL (skipping)\n", start+i);
            err = -1;
            continue;
        }
        //std::cout << textureFileNames[1]  << std::endl;
        full += std::string(textureFileNames[start+i]);
        //std::cout << textureFileNames[2]  << std::endl;
        if (suffix) full += std::string(suffix);
        // std::cout << "## " << full << " size:"<<size << std::endl;
        if (loadTexture(full.c_str(), allegro_flags) < 0) err=-1;
    }
    // std::cout << "bank error: " << err << std::endl;
    return err;
}

TextureID MultiTextureBank::loadTexture(const char* file, int al_flags) {
    if (size>=initialSize) {
        fprintf(stderr, "[BANK::ERROR] Max content size has been reached: %d\n", initialSize);
        return -2;
    }
    if (contents[size++].load(file,al_flags)) return -1;
    return size;
}

TextureID MultiTextureBank::loadTextureAt(TextureID id, const char* file, int al_flags) {
    if (id<0 || id>=initialSize) return -1;
    if (contents[id].getAllegroBitmap()) {
        printf("[BANK] Texture already exists at index=%d\n", id);
        return loadTexture(file, al_flags);
    }
    if (contents[id].load(file,al_flags)) return -1;
    return id;
}

void MultiTextureBank::destroy(TextureID id) {
    contents[id].destroy();
}
void MultiTextureBank::destroyAll() {
    for (int i=0; i<initialSize; i++) {
        contents[i].destroy();
    }
    size = 0;
}
void MultiTextureBank::free() {
    delete[] contents;
}


const Texture& MultiTextureBank::getTexture(TextureID id) const {
    return contents[id];
}
#pragma endregion


// ## TILESET BANK ## //
#pragma region Tileset Bank


int TilesetBank::loadTexture(const char* file, int al_flags) {
    if (texture.load(file,al_flags)) return -1;
    return 0;
}
    
int TilesetBank::loadTileRects(const char* tilerectsfile){
    tileRects = util::loadTiles(tilerectsfile);
    return 0;
}


const Texture& TilesetBank::getTexture() const {
    return texture;
}


Rectu TilesetBank::getTile(int drawableID) const {
    return tileRects[drawableID];
}
   
void TilesetBank::destroy() {
    texture.destroy();
}

#pragma endregion




#pragma region bank::multitex
// #namespace bank

namespace bank::multitex {
    MultiTextureBank* banks;
    unsigned int initialSize = 0;
} // namespace bank

using namespace bank;

void multitex::init(unsigned int num_banks) {
    initialSize = num_banks;
    banks = new MultiTextureBank[num_banks];
}
void multitex::destroyAll() {
    for (int i=0; i<initialSize; i++) {
        banks[i].destroyAll();
        banks[i].free();
    }
}
void multitex::free(){
    if (banks) {
        delete[] banks;
        banks = NULL;
        initialSize = 0;
    }
}
void multitex::makeGlobal(MultiTextureBank& bank, unsigned int id) {
    //std::cout << "Texture bank made global at " << id << std::endl;
    banks[id] = bank;
}
const MultiTextureBank& multitex::getBank(unsigned int id) {
    // static_assert(std::is_same_v<T, int> || std::is_same_v<T, float>, "Type must be a bank");
    return banks[id];
}

#pragma endregion







#pragma region bank::tileset
// #namespace bank

namespace bank::tileset {
    TilesetBank* banks;
    unsigned int initialSize = 0;
} // namespace bank

using namespace bank;

void tileset::init(unsigned int num_banks) {
    initialSize = num_banks;
    banks = new TilesetBank[num_banks];
}
void tileset::destroyAll() {
    for (int i=0; i<initialSize; i++) {
        banks[i].destroy();
    }
}
void tileset::destroy(unsigned int index) {
    banks[index].destroy();
}
void tileset::free(){
    if (banks) {
        delete[] banks;
        banks = NULL;
        initialSize = 0;
    }
}
void tileset::makeGlobal(TilesetBank& bank, unsigned int id) {
    //std::cout << "Texture bank made global at " << id << std::endl;
    banks[id].destroy();
    banks[id] = bank;
}
TilesetBank& tileset::getBank(unsigned int id) {
    // static_assert(std::is_same_v<T, int> || std::is_same_v<T, float>, "Type must be a bank");
    return banks[id];
}

#pragma endregion



const Texture& bank::getTexture(const bank::TextureInfo& tinfo) {
    if (tinfo.bankType == bank::bank_type::MULTITEX)
        return multitex::banks[tinfo.bankID].getTexture(tinfo.textureID);
    if (tinfo.bankType == bank_type::TILESET)
        return tileset::banks[tinfo.bankID].getTexture();
    // invalid bank, error it shall be: ->
    return tileset::banks[0].getTexture();
}


void bank::destroyAll() {
    tileset::destroyAll();
    tileset::free();
    multitex::destroyAll();
    multitex::free();
}