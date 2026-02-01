#pragma once
#ifndef __TEXTURE_HPP
#define __TEXTURE_HPP

#include <allegro5/bitmap.h>
#include <allegro5/allegro_opengl.h>

class Texture {
private:
    ALLEGRO_BITMAP* _bitmap;
public:
    Texture() = default;
    ~Texture() = default;
    // remove copy constructor (allegro bitmap pointer should not be copied)
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

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

    /// @returns @code{ALLEGRO_BITMAP* _bitmap}
    ALLEGRO_BITMAP* getAllegroBitmap() const;
    /**
     * @returns OpenGL Texture ID (use for manual bindings ili tako nekako)
     */
    GLuint getOpenGLTexture() const;
};


#endif