#pragma once
#ifndef __TEXTURE_HPP
#define __TEXTURE_HPP

#include <allegro5/bitmap.h>
// #include <allegro5/allegro_opengl.h>

/**
 *  Texture a; a.load(...);
 *  Texture b = a;
 * In this case a and b have the same bitmap pointer. Beware
 */
class Texture {
private:
    ALLEGRO_BITMAP* _bitmap;
public:
    Texture() = default;
    ~Texture() = default;
    // UNDO remove copy constructor (allegro bitmap pointer should not be copied) - UNDO

    /// @brief Calls load(filepath, allegro_flags)
    Texture(const char* filepath, int allegro_flags=0x0);

    /**
     * *Creates* new texture.
     */
    int create(int w, int h);
    /**
     * *Loads* texture from file with given flags
     */
    int load(const char* filepath, int allegro_flags=0x0);
    /**
     * Frees this texture.
     */
    void destroy();
    
    int getWidth() const;
    int getHeight() const;

    /// @returns @code{ALLEGRO_BITMAP* _bitmap}
    ALLEGRO_BITMAP* getAllegroBitmap() const;
};



#endif