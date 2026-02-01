#include <sprite/texture.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <logger.hpp>

Texture::Texture(const char* fnm, int flgs) {
    load(fnm,flgs);
}

int Texture::create(int w, int h) {
    _bitmap = al_create_bitmap(w,h);
    return _bitmap==NULL; // 1 = error, 0 = success
}
int Texture::load(const char* filename, int flags) {
    // printf(" # Loading texture: %s [%s]\n", filename, (flags&ALLEGRO_VIDEO_BITMAP)? "video" : "memory");
    _bitmap = al_load_bitmap_flags(filename, flags);
    if (!_bitmap) {
        fprintf(stderr, "%sCould not load texture: %s\n", LOGGER_ERROR_PREFIX, filename);
        return -1;
    }
    return _bitmap==NULL;
}
void Texture::destroy() {
    al_destroy_bitmap(_bitmap);
}

ALLEGRO_BITMAP* Texture::getAllegroBitmap() const {
    return _bitmap;
}

GLuint Texture::getOpenGLTexture() const {
    return al_get_opengl_texture(_bitmap);
}