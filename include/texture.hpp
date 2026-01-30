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

    /**
     * *Creates* new texture.
     */
    int create(int w, int h);
    /**
     * *Loads* texture from file with given flags
     */
    int load(const char* filename, int allegro_flags=0x0);
    /**
     * Frees this texture.
     */
    void destroy();

    ALLEGRO_BITMAP* getAllegroBitmap();
    /**
     * @returns OpenGL Texture ID (use for manual bindings ili tako nekako)
     */
    GLuint getOpenGLTexture() const;
};


#endif